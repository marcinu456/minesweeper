// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MineSweeperGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MINESWEEPER_API AMineSweeperGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TotalPoints = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class AGridActor* GridActor;

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
