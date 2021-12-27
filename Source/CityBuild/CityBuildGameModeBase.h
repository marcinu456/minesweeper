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
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Points)
		int32 TotalPoints = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Points)
		int32 Building = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Points)
		int32 RedBuilding = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Points)
		int32 YellowBuilding = 25;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Points)
		int32 WhiteBuilding = 35;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Points)
		int32 PurpleBuilding = 40;
};
