// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (ensure(PlayerTank))
	{
		//TODO Move Towards Player, check radius is in cm
		MoveToActor(PlayerTank, AcceptanceRadius);

		//Aim towards Player
		FVector HitLocation = PlayerTank->GetActorLocation();

		TankAimingComponent->AimAt(HitLocation);

		TankAimingComponent->Fire();

		//ControlledTank->Fire();

		//Fire if ready
	}
}