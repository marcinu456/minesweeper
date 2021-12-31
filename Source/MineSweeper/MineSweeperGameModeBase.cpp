// Copyright Epic Games, Inc. All Rights Reserved.


#include "MineSweeperGameModeBase.h"

void AMineSweeperGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMineSweeperGameModeBase::SetGridActor(AGridActor* _GridActor)
{
	GridActor = _GridActor;
}
