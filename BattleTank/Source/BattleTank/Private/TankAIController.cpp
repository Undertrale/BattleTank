// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

/// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	/// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); /// TODO check radius is in cm
	/// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->Fire(); /// TODO limit firing rate
}