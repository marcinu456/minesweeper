// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CellActor.generated.h"

class AGridActor;
UCLASS()
class CITYBUILD_API ACellActor : public AActor
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
	}

	bool GetCellVisible()
	{
		return CellVisible;
	}

	void SetCellVisible(bool _CellVisible) {
		CellVisible = _CellVisible;
	}

	void SetCellColor() {
		StaticMeshComponent->SetMaterial(0, BlueColorOfCell);
		EndCursorOverMaterial = BlueColorOfCell;
	}

	void SetCellColorMine() {
		StaticMeshComponent->SetMaterial(0, GreyColorOfCell);
		EndCursorOverMaterial = GreyColorOfCell;
		UE_LOG(LogTemp, Warning, TEXT("Mine PosX=%d, PosY=%d"), CellX, CellY);

	}

	void SetGridActorManager(AGridActor* _GridActorManager) {
		GridActorManager = _GridActorManager;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	FORCEINLINE class UStaticMeshComponent* GetStaticMesh() const { return StaticMeshComponent; }
private:
	UFUNCTION()
		void Clicked();
	UFUNCTION()
		void BeginCursorOver();
	UFUNCTION()
		void EndCursorOver();

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

	int32 CellValue;

	bool CellVisible;

	UPROPERTY()
	class AGridActor* GridActorManager;

};
