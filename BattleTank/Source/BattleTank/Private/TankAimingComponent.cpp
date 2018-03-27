// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) {
	Barrel = BarrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation,float launchSpeed) {

	if (!Barrel) {
		return;
	}

	FVector outLaunchVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the outLaunchVelocity 
	if (UGameplayStatics::SuggestProjectileVelocity
	    (
		this,
		outLaunchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
		)
	)
	{
		FVector aimDirection = outLaunchVelocity.GetSafeNormal();
		FString tankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"),*tankName, *aimDirection.ToString());
	}
}

