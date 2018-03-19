// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController has BeginPlay"));

	ATank* myTank = GetControlledTank();
	if (myTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("There is not a Tank added to TankPlayerController"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("My tank was %s found."),*myTank->GetName());
	}
}

// Called every frame
void  ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetControlledTank()) {
		return;
	}

	FVector outHitLocation; // OUT Parameter

	if (GetSightRayHitLocation(outHitLocation)) {

		//TODO Tell controlled tank to aim at this point 
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *outHitLocation.ToString());
	}
}

//Get World location through crosshair, true if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const {

	//Finding the crosshair position in pixel coordinates
	int32 viewPortSizeX, viewPortSizeY;
	GetViewportSize(viewPortSizeX, viewPortSizeY);
	auto screenLocation = FVector2D(viewPortSizeX * crossHairXLocation, viewPortSizeY * crossHairYLocation);
	//"De-project" the screen position of the crosshair to a world direction
	//line-trace (raycast) along that look direction, and see what we hit (up to max range)


	return true;
}


