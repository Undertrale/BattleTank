// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" /// Must be the last include

/// Forward Declaration
class ATank;


UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	ATank* GetControlledTank() const;

	/// Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();

	/// Return an OUT parameter, true id hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5; /// TODO, remove magic nr
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333; /// TODO, remove magic nr. Here we hard-coded the pos of our crosshair

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
