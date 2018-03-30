// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TankAIController has BeginPlay"));

	ATank* playerTank = GetPlayerTank();
	if (playerTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("TankAIController can't find player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found player : %s"), *playerTank->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {

	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerPawn) { return nullptr;}
	return Cast<ATank>(playerPawn);
}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {

		//TODO Move towards the player

		//Aim Towards the player

		FVector playerTankLocation = GetPlayerTank()->GetTransform().GetLocation();
		GetControlledTank()->AimAt(playerTankLocation);

		//Fire if its ready 
	}
}

