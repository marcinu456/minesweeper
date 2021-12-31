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
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), BlueprintReadWrite, Category = "Points")
		int32 TotalPoints = 0;


	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), BlueprintReadWrite, Category = "Points")
		bool GameOver = false;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), BlueprintReadWrite, Category = "Points")
		class AGridActor* GridActor;

	void SetGridActor(AGridActor* _GridActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
