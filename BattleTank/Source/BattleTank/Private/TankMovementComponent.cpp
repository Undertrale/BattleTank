// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


/** path following: request new velocity */
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	/// No need to call Super as we're replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow =	FVector::DotProduct(TankForward, AIForwardIntention);
	/// Send this info to the IntendMoveFwr method:
	IntendMoveForward(ForwardThrow);
	/// Make the AI rotate towards the player:
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	/// Send this info to IntendTurnRight():
	IntendTurnRight(RightThrow);
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	/// TODO prevent double-speed due to dual control use
	
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
	///UE_LOG(LogTemp, Warning, TEXT("Intend move backward throw: %f"), Throw);
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	/// TODO prevent double-speed due to dual control use
}