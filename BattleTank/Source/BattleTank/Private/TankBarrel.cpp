// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move the barrel the right amount this frame
	// Given a max elevation speed, and the time frame
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	
	auto ClampedElevation = FMath::Clamp(RawNewElevation, MinElevationInDegrees, MaxElevationInDegrees);


	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}