// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine.h"


void UTankTurret::RotateTurret(float relativeSpeed) {

	auto relativeSpeedClamp = FMath::Clamp<float>(relativeSpeed, -1, 1);
	auto rotationChange = relativeSpeedClamp * maxDregreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + rotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}

