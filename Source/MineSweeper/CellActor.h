// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MineSweeperGameModeBase.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "CellActor.generated.h"

class AGridActor;

UCLASS()
class MINESWEEPER_API ACellActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACellActor();


	void GetCellPlace(int32& x, int32& y) {
		x = CellX;
		y = CellY;
	}

	void SetCellPlace(const int32 x, const int32 y) {
		CellX = x;
		CellY = y;
	}

	int32 GetCellValue()
	{
		return CellValue;
	}

	void SetCellValue(const int32 _CellValue) {

		CellValue = _CellValue;
		SetValueToWidget();
	}

	bool GetCellVisible()
	{
		return bCellVisible;
	}

	void SetCellVisible(const bool _CellVisible) {
		bCellVisible = _CellVisible;

		if (bCellVisible)
		{
			StaticMeshComponent->SetMaterial(0, VisibleColorOfCell);
			EndCursorOverMaterial = VisibleColorOfCell;
			AMineSweeperGameModeBase* GameMode = Cast<AMineSweeperGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			GameMode->TotalPoints++;
		}
		else
		{
			StaticMeshComponent->SetMaterial(0, GreenColorOfCell);
			EndCursorOverMaterial = GreenColorOfCell;
		}



	}

	void SetCellColor() {
		StaticMeshComponent->SetMaterial(0, DebugColorOfCell);
		EndCursorOverMaterial = DebugColorOfCell;
	}

	void SetCellColorMine() {
		StaticMeshComponent->SetMaterial(0, MineColorOfCell);
		EndCursorOverMaterial = MineColorOfCell;
	}

	void SetGridActorManager(AGridActor* _GridActorManager) {
		GridActorManager = _GridActorManager;
	}

	bool GetCellFlag()
	{
		return bCellFlag;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	FORCEINLINE class UStaticMeshComponent* GetStaticMesh() const { return StaticMeshComponent; }
protected:

	UFUNCTION(BlueprintImplementableEvent, meta = (AllowPrivateAccess = "true", Category = "Cell Setup"))
		void SetValueToWidget();

private:
	UFUNCTION()
		void Clicked(UPrimitiveComponent* touchedComponent, FKey buttonPressed);
	UFUNCTION()
		void BeginCursorOver();
	UFUNCTION()
		void EndCursorOver();

	void SetFlag();

	int32 CellX;
	int32 CellY;


	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* ClickedMaterial;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* BeginCursorOverMaterial;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* EndCursorOverMaterial;


	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* GreenColorOfCell;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* VisibleColorOfCell;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* MineColorOfCell;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* FlagColorOfCell;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* DebugColorOfCell;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true", Category = "Cell Setup"))
		int32 CellValue;

	bool bCellVisible;

	bool bCellFlag;

	UPROPERTY()
		class AGridActor* GridActorManager;

};