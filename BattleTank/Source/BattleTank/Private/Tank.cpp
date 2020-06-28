// Copyright Peter Q Nguyen
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);

	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	UE_LOG(LogTemp, Warning, TEXT("DamagePoints %i"), DamagePoints);

	UE_LOG(LogTemp, Warning, TEXT("DamageToApply %i"), DamageToApply);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		//dead tank
	}
	return DamageToApply;
}


float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}