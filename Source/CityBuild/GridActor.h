// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CellActor.h"
#include "GameFramework/Actor.h"
#include "GridActor.generated.h"

UCLASS()
class CITYBUILD_API AGridActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	TArray<ACellActor*> CellActors; //row-major

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

	void ShowGrid(int32 x, int32 y);


	void SetupMines(int32& FirstPosX, int32& FirstPosY)
	{
		if(!bSetupMines)
		{
			RandomPosition(FirstPosX, FirstPosY);
			bSetupMines = true;
		}
	}

private:
	UFUNCTION()
		void Clicked();


	void RandomPosition(int32& FirstPosX, int32& FirstPosY);

	
	bool PlaceMines(int32 poz_x, int32 poz_y);

	bool bSetupMines;
};
