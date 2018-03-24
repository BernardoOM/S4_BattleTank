// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"//Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	void AimTowardsCrosshair();
	//return an OUT Parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& outHitLocation) const;
	UPROPERTY(EditAnywhere)
	float crossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float crossHairYLocation = 0.33333f;
	UPROPERTY(EditAnywhere)
	float lineTraceRange = 1000000;

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;
};
