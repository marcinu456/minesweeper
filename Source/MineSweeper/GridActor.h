// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridActor.generated.h"

class ACellActor;
UCLASS()
class MINESWEEPER_API AGridActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridActor();

	UFUNCTION(BlueprintCallable)
	int32 GetHowManyFlags()
	{
		return HowManyFlags;
	}
	void SetHowManyFlags(const int32 _HowManyFlags)
	{
		HowManyFlags = _HowManyFlags;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void UpdateGrid(const int32 PosX, const int32 PosY)
	{
		if (!bSetupMines)
		{
			RandomPosition(PosX, PosY);
			bSetupMines = true;
		}
		ShowGrid(PosX, PosY);
	}

	UFUNCTION(BlueprintCallable)
		void SetupGrid(const int32 Width, const int32 Height, const int32 Mines);

	void GameOver(const int32 Points = 0);


private:

	void ShowGrid(const int32 PosX, const int32 PosY);


	UPROPERTY()
		TArray<ACellActor*> CellActors; //row-major

	UPROPERTY()
		TArray<ACellActor*> CellMines; //row-major

	/** Width of grid in number of cells. */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", AllowPrivateAccess = "true", Category = "Grid Setup"))
		int32 Width = 50;
	/** Height of grid in number of cells. */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", AllowPrivateAccess = "true", Category = "Grid Setup"))
		int32 Height = 50;
	/** Class for cell. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Grid Setup"))
		int32 Mines = 10;

	/** Offset between cells. */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", AllowPrivateAccess = "true", Category = "Grid Setup"))
		float Offset = 15.0;
	/** Class for cell. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Grid Setup"))
		TSubclassOf<ACellActor> CellActor;


private:


	void RandomPosition(const int32 FirstPosX, const int32 FirstPosY);


	bool PlaceMines(const int32 PosX, const int32 PosY);


	bool bSetupMines;

	int32 HowManyToGo;

	int32 HowManyFlags;
};
