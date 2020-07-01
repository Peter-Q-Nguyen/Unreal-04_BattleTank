// Copyright Peter Q Nguyen


#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint"));
	SetRootComponent(PhysicsConstraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(PhysicsConstraint);



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

void ASprungWheel::SetupConstraint()
{
	UPrimitiveComponent* BodyComponent = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyComponent) return;
	
	PhysicsConstraint->SetConstrainedComponents
	(
		BodyComponent,
		NAME_None,
		Wheel,
		NAME_None
	);
}

