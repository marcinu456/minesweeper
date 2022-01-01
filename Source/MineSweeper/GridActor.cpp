// Fill out your copyright notice in the Description page of Project Settings.


#include "GridActor.h"

#include "CellActor.h"
#include "MineSweeperGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGridActor::AGridActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridActor::BeginPlay()
{
	Super::BeginPlay();

	AMineSweeperGameModeBase* GameMode = Cast< AMineSweeperGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->GridActor = this;

}

void AGridActor::SetupGrid(const int32 _Width, const int32 _Height, const int32 _Mines)
{

	for (auto& Cell : CellActors)
	{
		Cell->Destroy();
	}

	CellActors.Empty();
	CellMines.Empty();

	Width = _Width;
	Height = _Height;
	Mines = _Mines;
	bSetupMines = false;


	TArray<UStaticMeshComponent*> Components;
	CellActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	const FVector BoxExtent = Components[0]->GetStaticMesh()->GetBounds().BoxExtent;
	const FVector Scale = Components[0]->GetRelativeTransform().GetScale3D();

	ensure(Components.Num() > 0);

	const float EffectiveBoxExtentY = BoxExtent.Y * Scale.Y + Offset;
	const float EffectiveBoxExtentX = BoxExtent.X * Scale.X + Offset;
	const float YStep = EffectiveBoxExtentY * 2;
	const float XStep = EffectiveBoxExtentX * 2;
	const float BoardWidth = EffectiveBoxExtentY * 2 * Width;
	const float BoardHeight = EffectiveBoxExtentX * 2 * Height;

	const FVector Origin = GetActorLocation();
	const FVector TopLeft(Origin.X + BoardHeight / 2 - EffectiveBoxExtentX, Origin.Y - BoardWidth / 2 + EffectiveBoxExtentY, Origin.Z);

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			const FVector Loc(TopLeft.X - i * XStep, TopLeft.Y + j * YStep, Origin.Z);
			ACellActor* const SpawnedActorRef = GetWorld()->SpawnActor<ACellActor>(CellActor, Loc, GetActorRotation());
			SpawnedActorRef->SetCellPlace(j, i);
			SpawnedActorRef->SetCellValue(0);
			SpawnedActorRef->SetGridActorManager(this);
			CellActors.Add(SpawnedActorRef);
		}
	}
	HowManyToGo = Height * Width;
	HowManyFlags = Mines;
}




// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGridActor::RandomPosition(const int32 FirstPosX, const int32 FirstPosY)
{
	int32 PosX, PosY;
	int32 MinesToPlace = Mines;

	//UE_LOG(LogTemp, Warning, TEXT("RandomPosition PosX=%d, PosY=%d"), FirstPosX, FirstPosY);


	while (MinesToPlace > 0)
	{
		PosX = FMath::RandRange(0, Width - 1);
		PosY = FMath::RandRange(0, Height - 1);

		if (PosX == FirstPosX && PosY == FirstPosY)
		{
			UE_LOG(LogTemp, Warning, TEXT("RandomPosition PosX=%d, PosY=%d"), FirstPosX, FirstPosY);

			continue;
		}

		if (CellActors[PosY * Width + PosX]->GetCellValue() != 9)
		{
			PlaceMines(PosX, PosY);
			MinesToPlace--;
		}
	}
}

bool AGridActor::PlaceMines(const int32 PosX, const int32 PosY)
{
	if (CellActors[PosY * Width + PosX]->GetCellValue() != 9)
	{
		CellActors[PosY * Width + PosX]->SetCellValue(9);
		CellMines.Add(CellActors[PosY * Width + PosX]);
		//CellActors[PosY * Width + PosX]->SetCellColorMine();



		for (int k = -1; k < 2; k++)
			for (int l = -1; l < 2; l++)
			{
				if ((PosX + l) < 0 || (PosY + k) < 0)
				{
					continue;
				}

				if ((PosX + l) > Width - 1 || (PosY + k) > Height - 1)
				{
					continue;
				}

				if (CellActors[(PosY + k) * Width + PosX + l]->GetCellValue() == 9)
				{
					continue;
				}

				CellActors[(PosY + k) * Width + PosX + l]->SetCellValue(CellActors[(PosY + k) * Width + PosX + l]->GetCellValue() + 1);
				//CellActors[(PosY + k) * Width + PosX + l]->SetCellColor();

			}
	}

	return true;
}

void AGridActor::GameOver(const int32 Points)
{
	for (auto& Cell : CellMines)
	{
		Cell->SetCellColorMine();
	}

	AMineSweeperGameModeBase* GameMode = Cast< AMineSweeperGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->TotalPoints += Points * 10;
	GameMode->GameOver();
}


void AGridActor::ShowGrid(const int32 PosX, const int32 PosY)
{
	if (PosX < 0 || PosX>Width - 1) 
	{
		return;
	}

	if (PosY < 0 || PosY>Height - 1)
	{
		return;
	}

	if (CellActors[PosY * Width + PosX]->GetCellVisible() == true || CellActors[PosY * Width + PosX]->GetCellFlag() == true)
	{
		return;
	}

	if (CellActors[PosY * Width + PosX]->GetCellValue() != 9 && CellActors[PosY * Width + PosX]->GetCellVisible() == false)
	{
		CellActors[PosY * Width + PosX]->SetCellVisible(true);
		HowManyToGo--;
		if (HowManyToGo == Mines)
		{
			GameOver(Mines);
		}

	}

	if (CellActors[PosY * Width + PosX]->GetCellValue() != 0)
	{
		return;
	}

	ShowGrid(PosX - 1, PosY - 1);
	ShowGrid(PosX - 1, PosY);
	ShowGrid(PosX - 1, PosY + 1);
	ShowGrid(PosX + 1, PosY - 1);
	ShowGrid(PosX + 1, PosY);
	ShowGrid(PosX + 1, PosY + 1);
	ShowGrid(PosX, PosY - 1);
	ShowGrid(PosX, PosY);
	ShowGrid(PosX, PosY + 1);
}

