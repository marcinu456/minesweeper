// Copyright Epic Games, Inc. All Rights Reserved.


#include "CityBuildGameModeBase.h"

void ACityBuildGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACityBuildGameModeBase::SetGridActor(AGridActor* _GridActor)
{
	GridActor = _GridActor;
}
