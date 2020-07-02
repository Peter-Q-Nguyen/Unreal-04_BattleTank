// Copyright Peter Q Nguyen

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;
/**
 * Tank Track is used to set maximum driving force, and apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input2")
	void SetThrottle(float Throttle);
	
	// Max force per track in newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000; // Assume 40 ton tank and 1g acceleration

private:
	UTankTrack();

	TArray<class ASprungWheel*> GetWheels() const;

	void DriveTrack(float CurrentThrottle);
};
