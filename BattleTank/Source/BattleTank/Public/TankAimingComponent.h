// Copyright Peter Q Nguyen

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

//forward declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

//Holds barrel properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	EFiringState GetFiringState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetAmmoRemaining() const;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	bool IsBarrelMoving();
	bool IsOutOfAmmo();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 CurrentAmmo = 20;



	double LastFireTime = 0;

	FVector TargetAimDirection;
};
