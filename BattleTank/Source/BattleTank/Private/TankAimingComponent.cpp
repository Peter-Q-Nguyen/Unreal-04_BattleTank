// Copyright Peter Q Nguyen

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	TargetAimDirection = FVector(0);
}
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Super::TickComponent(DeltaTime,TickType,ThisTickFunction);
	//GetWorld()->GetTimeSeconds() // also works

	if (IsOutOfAmmo())
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}

}

void UTankAimingComponent::Fire()
{

	if (FiringState != EFiringState::Reloading && FiringState != EFiringState::OutOfAmmo)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		//Spawn a projectile
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

		CurrentAmmo--;

	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
		return false;

	auto CurrentForward = Barrel->GetForwardVector();
	return !TargetAimDirection.Equals(CurrentForward, 0.05);
}

bool UTankAimingComponent::IsOutOfAmmo()
{
	if (CurrentAmmo == 0)
		return true;
	else
		return false;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	auto OurTankName = GetOwner()->GetName();

	//auto BarrelLocation = Barrel->GetComponentLocation();

	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());

	if (!ensure(Barrel)) { return; }

	FVector OutTossVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate launch velocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutTossVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0,
		0.0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		//CollisionResponseParams,
		//ActorsToIgnore,
		//false
	);

	auto Time = GetWorld()->GetTimeSeconds();

	if (bHaveAimSolution)
	{
		TargetAimDirection = OutTossVelocity.GetSafeNormal();
		MoveBarrelTowards(TargetAimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret))
		return;
	//Work out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
		Turret->RotateTurret(DeltaRotator.Yaw);
	else
		Turret->RotateTurret(-DeltaRotator.Yaw);

	Barrel->Elevate(DeltaRotator.Pitch);

}

int32 UTankAimingComponent::GetAmmoRemaining() const
{
	return CurrentAmmo;
}