// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CityBuildGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILD_API ACityBuildGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), BlueprintReadWrite, Category = "Points")
		int32 TotalPoints = 0;

public:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), BlueprintReadWrite, Category = "Points")
		bool GameOver = false;


};
