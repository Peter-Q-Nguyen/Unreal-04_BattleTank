// Copyright Peter Q Nguyen

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//How close can the AI tank get to the player
	float AcceptanceRadius = 3000;

};
