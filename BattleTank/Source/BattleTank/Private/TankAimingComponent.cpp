// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	auto OurTankName = GetOwner()->GetName();

	auto BarrelLocation = Barrel->GetComponentLocation();

	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());

	if (!Barrel) { return; }

	FVector OutTossVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate launch velocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutTossVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		//false,
		//0.0,
		//0.0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		//CollisionResponseParams,
		//ActorsToIgnore,
		//false
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutTossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s"), *OurTankName, *OutTossVelocity.GetSafeNormal().ToString());

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Work out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(5); // TODO remove magic number


}