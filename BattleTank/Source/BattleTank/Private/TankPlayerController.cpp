// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"


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
		GetControlledTank()->AimAt(outHitLocation);
	}
}

//Get World location through crosshair, true if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const {

	//Finding the crosshair position in pixel coordinates
	int32 viewPortSizeX, viewPortSizeY;
	GetViewportSize(viewPortSizeX, viewPortSizeY);
	auto screenLocation = FVector2D(viewPortSizeX * crossHairXLocation, viewPortSizeY * crossHairYLocation);
	//"De-project" the screen position of the crosshair to a world direction
	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection)) {
		//line-trace (raycast) along that lookDirection, and see what we hit (up to max range)
		GetLookVectorHitLocation(lookDirection,outHitLocation);
		return true;
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const {
	FVector cameraWorldLocation;
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection,FVector& hitLocation) const {
	FHitResult hitResult;
	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + (lookDirection * lineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Visibility)
	   ) 
	{
		hitLocation = hitResult.Location;
		return true;
	}
	hitLocation = FVector(0);
	return false;
}


