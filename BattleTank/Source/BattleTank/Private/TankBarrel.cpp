// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine.h"

void UTankBarrel::Elevate(float relativeSpeed) {
	
	//Move this barrel the right amount this frame
	//Given a Max Elevation speed, and the frame time
    auto relativeSpeedClamp = FMath::Clamp<float>(relativeSpeed, -1, 1);
	auto elevationChange = relativeSpeedClamp * maxDregreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
	auto clampElevation = FMath::Clamp(rawNewElevation, minElevationDegrees, maxElevationDegrees);
	SetRelativeRotation(FRotator(clampElevation, 0, 0));
}

