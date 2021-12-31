// Fill out your copyright notice in the Description page of Project Settings.


#include "MineSweeperPlayerController.h"

AMineSweeperPlayerController::AMineSweeperPlayerController()
{
	SetShowMouseCursor(true);
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchOverEvents = true;
	ClickEventKeys.Add(EKeys::RightMouseButton);
}
