// Copyright Peter Q Nguyen

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.00;


	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

	//start the tank moving the barrel so a shot would hit where the crosshair intersects with the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const ;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

};
