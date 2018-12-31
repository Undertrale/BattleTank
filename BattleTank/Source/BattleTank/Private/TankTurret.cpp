// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Math/UnrealMathUtility.h"

void UTankTurret::Rotate(float RelativeSpeed) ///TODO Changed back to RelSpd again
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1); /// Added
	auto RotationChange = RelativeSpeed * MaxDegreesPerSeconds * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));

}