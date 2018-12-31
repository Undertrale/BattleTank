// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" /// Paste new includes above!

/// Forward Declarations
class UTankBarrel;
class UTankTurret; ///TODO
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)	/// TODO
	void SetTurretReference(UTankTurret* TurretToSet); /// TODO

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
///public:
	// Sets default values for this pawn's properties
	ATank();

///protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000.; 
};
