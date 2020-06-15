// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{


	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;


}
void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//auto Name = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s Move Velocity: %s"), *Name, *MoveVelocity.ToString());

	UE_LOG(LogTemp, Warning, TEXT(" Move Velocity: %s"), *MoveVelocity.ToString());
}
