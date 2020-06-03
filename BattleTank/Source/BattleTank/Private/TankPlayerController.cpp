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

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Something Hit at %s"), *HitLocation.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing Hit"));
	}
}


// Get world location if linetrace through crosshair
// IF oy hits the landscape tell controlled tank to aim at the point
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation,
		ViewportSizeY * CrossHairYLocation);

	FVector WorldDirection;

	if (GetLookDirection(ScreenLocation, WorldDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("WorldDirection %s"), *WorldDirection.ToString());
	}
	//UE_LOG(LogTemp, Warning, TEXT("TestA %i"), ViewportSizeX);
	//UE_LOG(LogTemp, Warning, TEXT("TestB %i"), ViewportSizeY);
	//UE_LOG(LogTemp, Warning, TEXT("TestC %f"), CrossHairXLocation);
	//UE_LOG(LogTemp, Warning, TEXT("TestD %f"), CrossHairYLocation);
	// Deproject the screen position of the crosshair to a world direction
	// line trace along that look direction and see what we hit (up to a max range)


	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D& ScreenLocation, FVector &LookDirection) const
{
	FVector WorldLocation; //To be discarded


	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}