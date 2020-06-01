// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller is possessing tank - %s"), *ControlledTank->GetName());
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("Tick %i"), DeltaTime);
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	// Get world location if linetrace through crosshair
	// IF oy hits the landscape tell controlled tank to aim at the point

}