// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(PlayerTank))
	{
		//TODO Move Towards Player, check radius is in cm
		MoveToActor(PlayerTank, AcceptanceRadius);

		//Aim towards Player
		FVector HitLocation = PlayerTank->GetActorLocation();

		ControlledTank->AimAt(HitLocation);

		ControlledTank->Fire();

		//Fire if ready
	}
}