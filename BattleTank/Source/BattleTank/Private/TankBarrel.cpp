// Copyright Peter Q Nguyen


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move the barrel the right amount this frame
	// Given a max elevation speed, and the time frame
	auto ElevationChange = FMath::Clamp(RelativeSpeed,-1.0f,1.0f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
	
	auto ClampedElevation = FMath::Clamp(RawNewElevation, MinElevationInDegrees, MaxElevationInDegrees);


	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}