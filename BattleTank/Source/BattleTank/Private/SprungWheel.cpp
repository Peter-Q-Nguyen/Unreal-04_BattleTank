// Copyright Peter Q Nguyen


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SpringConstraint"));
	SetRootComponent(SpringConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(SpringConstraint);

	Wheel2 = CreateDefaultSubobject<USphereComponent>(FName("Wheel2"));
	Wheel2->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);

	//USphereComponent* Wheel = nullptr;

	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//	USphereComponent* Axle = nullptr;

	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//	UPhysicsConstraintComponent* SpringConstraint = nullptr;

	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	if (GetAttachParentActor())
	{
		SetupConstraint();
		UE_LOG(LogTemp, Warning, TEXT("constrained!"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Null"));
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	Wheel2->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}

void ASprungWheel::SetupConstraint()
{
	UPrimitiveComponent* BodyComponent = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyComponent) return;
	
	SpringConstraint->SetConstrainedComponents
	(
		BodyComponent,
		NAME_None,
		Axle,
		NAME_None
	);

	AxleWheelConstraint->SetConstrainedComponents
	(
		Axle,
		NAME_None,
		Wheel2,
		NAME_None
	);
}

