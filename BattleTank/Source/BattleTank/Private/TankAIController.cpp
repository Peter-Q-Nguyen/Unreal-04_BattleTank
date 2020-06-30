// Copyright Peter Q Nguyen

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h" // so we can implement onDeath

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);

	}
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

		//if aiming or locked, fire
		if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
			TankAimingComponent->Fire();
	}
}

void ATankAIController::OnTankDeath()
{
	//UE_LOG(LogTemp, Warning, TEXT("AIDeath"));
	auto ControlledTank = GetPawn();
	if (!ControlledTank) { return;}
	ControlledTank->DetachFromControllerPendingDestroy();
}
