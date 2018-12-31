// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h" /// Needs to be the first header!
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h" // TODO


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}


void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)	/// TODO 
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }	/// TODO

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace /// This parameter must be present to prevent bug
	);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto RotationDirection = OutLaunchVelocity.GetSafeNormal(); /// TODO safeguard!!
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection); 
		///MoveTurretTowards(RotationDirection);	///TODO Removed! No need for doubling the amount of code

		///auto Time = GetWorld()->GetTimeSeconds();
		///UE_LOG(LogTemp, Warning, TEXT("%f Aim solution found"), Time);
	}
		else
		{
			///auto Time = GetWorld()->GetTimeSeconds();
			///UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);
		}
	/// If no solution found do nothing
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	/// Work out difference btw current barrel rotation, and AimDir
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch); /// L149; Altering from magic nr to DeltaRotator.Pitch, resulted in losing the Barrel on BP!!
	Turret->Rotate(DeltaRotator.Yaw); /// Same problem as above
}

/*
///Removed = no need to double amount of the same code!

void UTankAimingComponent::MoveTurretTowards(FVector RotationDirection)	///TODO Removed = no need to double amount of the same code!
{
	/// Work out difference btw current barrel rotation, and AimDir
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto RotAsRotator = RotationDirection.Rotation();
	auto DeltaRotator = RotAsRotator - TurretRotator;
	
	Turret->Rotate(DeltaRotator.Yaw); /// L149; Altering from magic nr to DeltaRotator.Pitch, resulted in losing the Barrel on BP!!
}
	*/