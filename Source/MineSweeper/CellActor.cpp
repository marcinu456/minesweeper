// Fill out your copyright notice in the Description page of Project Settings.


#include "CellActor.h"

#include "GridActor.h"
#include "MineSweeperGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACellActor::ACellActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CellRootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CellMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	FScriptDelegate OnClickedDelegate;
	FScriptDelegate OnBeginCursorOverDelegate;
	FScriptDelegate OnEndCursorOverDelegate;
	OnClickedDelegate.BindUFunction(this, "Clicked");
	OnBeginCursorOverDelegate.BindUFunction(this, "BeginCursorOver");
	OnEndCursorOverDelegate.BindUFunction(this, "EndCursorOver");
	OnClicked.AddUnique(OnClickedDelegate);
	OnBeginCursorOver.Add(OnBeginCursorOverDelegate);
	OnEndCursorOver.Add(OnEndCursorOverDelegate);

	//OnClicked.AddUnique()


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Game/Materials/Shape_Sphere.Shape_Sphere"));
	if (SphereMeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(SphereMeshAsset.Object);
	}

	bCellVisible = false;
	bCellFlag = false;
}

// Called when the game starts or when spawned
void ACellActor::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->SetMaterial(0, GreenColorOfCell);
	//CellValue = 0;
	EndCursorOverMaterial = GreenColorOfCell;


}

// Called every frame
void ACellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACellActor::Clicked(UPrimitiveComponent* touchedComponent, FKey buttonPressed)
{
	if (buttonPressed == EKeys::LeftMouseButton && !bCellFlag) {

		if (CellValue == 9)
		{
			StaticMeshComponent->SetMaterial(0, MineColorOfCell);
			AMineSweeperGameModeBase* GameMode = Cast< AMineSweeperGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			GameMode->GameOver = true;

		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT(" Clicked PosX=%d, PosY=%d"), CellX, CellY);

			GridActorManager->SetupMines(CellX, CellY);

			GridActorManager->ShowGrid(CellX, CellY);

			StaticMeshComponent->SetMaterial(0, VisibleColorOfCell);
			EndCursorOverMaterial = VisibleColorOfCell;
		}



	}
	else if (buttonPressed == EKeys::RightMouseButton && !bCellVisible)
	{
		SetFlag();
	}
}


void ACellActor::BeginCursorOver()
{
	StaticMeshComponent->SetMaterial(0, BeginCursorOverMaterial);
}

void ACellActor::EndCursorOver()
{

	//if (!Occupied) {
	StaticMeshComponent->SetMaterial(0, EndCursorOverMaterial);
	//}
	//else {
	//	StaticMeshComponent->SetMaterial(0, BlueColorOfCell);
	//}

}

void ACellActor::SetFlag()
{
	if (bCellFlag && GridActorManager->GetHowManyFlags() >= 0)
	{
		bCellFlag = false;
		if (!bCellVisible)
		{
			StaticMeshComponent->SetMaterial(0, GreenColorOfCell);
			EndCursorOverMaterial = GreenColorOfCell;
		}
		else
		{
			StaticMeshComponent->SetMaterial(0, VisibleColorOfCell);
			EndCursorOverMaterial = VisibleColorOfCell;
		}

		GridActorManager->SetHowManyFlags(GridActorManager->GetHowManyFlags() + 1);
	}
	else if (!bCellFlag && GridActorManager->GetHowManyFlags() > 0)
	{
		bCellFlag = true;

		StaticMeshComponent->SetMaterial(0, FlagColorOfCell);
		EndCursorOverMaterial = FlagColorOfCell;

		GridActorManager->SetHowManyFlags(GridActorManager->GetHowManyFlags() - 1);

	}

}



