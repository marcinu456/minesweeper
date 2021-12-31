// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	void SetCellPlace(int32 x, int32 y) {
		CellX = x;
		CellY = y;
	}

	int32 GetCellValue()
	{
		return CellValue;
	}

	void SetCellValue(int32 _CellValue) {

		CellValue = _CellValue;
		SetValueToWidget();
	}

	bool GetCellVisible()
	{
		//UE_LOG(LogTemp, Warning, TEXT("GetCellVisible PosX=%d, PosY=%d"), CellX, CellY);

		return bCellVisible;
	}

	void SetCellVisible(bool _CellVisible) {
		bCellVisible = _CellVisible;
		//UE_LOG(LogTemp, Warning, TEXT("SetCellVisible PosX=%d, PosY=%d"), CellX, CellY);
		StaticMeshComponent->SetMaterial(0, RedColorOfCell);
		EndCursorOverMaterial = RedColorOfCell;
	}

	void SetCellColor() {
		StaticMeshComponent->SetMaterial(0, BlueColorOfCell);
		EndCursorOverMaterial = BlueColorOfCell;
	}

	void SetCellColorMine() {
		StaticMeshComponent->SetMaterial(0, GreyColorOfCell);
		EndCursorOverMaterial = GreyColorOfCell;
		//UE_LOG(LogTemp, Warning, TEXT("Mine PosX=%d, PosY=%d"), CellX, CellY);

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

	/** Material for when the cell is alive. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* ClickedMaterial;
	/** Material for when player hovers over the cell in edit mode. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* BeginCursorOverMaterial;
	/** Material for when the cell is not alive in edit mode. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* EndCursorOverMaterial;
	/** Material for when the cell is not alive in edit mode. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* GreenColorOfCell;
	/** Material for when the cell is not alive in edit mode. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* GreyColorOfCell;
	/** Material for when the cell is not alive in edit mode. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* BlueColorOfCell;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* RedColorOfCell;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* FlagColorOfCell;
	//UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
	UMaterialInterface* LastColorOfCell;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true", Category = "Cell Setup"))
		int32 CellValue;

	bool bCellVisible;

	bool bCellFlag;

	UPROPERTY()
		class AGridActor* GridActorManager;

};