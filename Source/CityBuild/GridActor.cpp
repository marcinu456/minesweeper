// Fill out your copyright notice in the Description page of Project Settings.


#include "GridActor.h"

// Sets default values
AGridActor::AGridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FScriptDelegate OnClickedDelegate;
	OnClickedDelegate.BindUFunction(this, "Clicked");
	OnClicked.Add(OnClickedDelegate);

	bSetupMines = false;
}

// Called when the game starts or when spawned
void AGridActor::BeginPlay()
{
	Super::BeginPlay();

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
	const FVector TopLeft(Origin.X + BoardHeight / 2 - EffectiveBoxExtentX, Origin.Y - BoardWidth / 2 + EffectiveBoxExtentY, Origin.Z );

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			const FVector Loc(TopLeft.X - i * XStep, TopLeft.Y + j * YStep, Origin.Z );
			ACellActor* const SpawnedActorRef = GetWorld()->SpawnActor<ACellActor>(CellActor, Loc, GetActorRotation());
			SpawnedActorRef->SetCellPlace(j, i);
			SpawnedActorRef->SetCellValue(0);
			SpawnedActorRef->SetGridActorManager(this);
			CellActors.Add(SpawnedActorRef);
		}
	}

}

// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGridActor::Clicked()
{

	for(auto& Cell:CellActors)
	{
		//if(Cell->GetOccupied())
		{
			int32 i;
			int32 j;
			Cell->GetCellPlace(i, j);
		}
	}
}


void AGridActor::RandomPosition(int32& FirstPosX, int32& FirstPosY)
{
	int32 PosX, PosY;
	int32 MinesToPlace = Mines;



	while (MinesToPlace > 0)
	{
		PosX = FMath::RandRange(0, Width-1);
		PosY = FMath::RandRange(0, Height-1);
		
		if (CellActors[PosX * Height + PosY]->GetCellValue() != 9 && (FirstPosX!= PosX && FirstPosY!=PosY))
		{
			PlaceMines(PosX, PosY);
			MinesToPlace--;
		}
	}
}

bool AGridActor::PlaceMines(int32 PosX, int32 PosY)
{
	if (CellActors[PosX * Height + PosY]->GetCellValue() != 9)
	{
		CellActors[PosX * Height + PosY]->SetCellValue(9); //ustawiamy mine
		CellActors[PosX * Height + PosY]->SetCellColorMine();



		for (int k = -1; k < 2; k++)
			for (int l = -1; l < 2; l++)
			{
				if ((PosX + l) < 0 || (PosY + k) < 0) continue; //wyjdz bo krawedz
				if ((PosX + l) > Width - 1 || (PosY + k) > Height - 1) continue; //wyjdz bo krawedz


				if (CellActors[(PosX + l) * Height + PosY + k]->GetCellValue() == 9) continue; //wyjdz bo mina
				int32 TempValue = CellActors[(PosX + l) * Height + PosY + k]->GetCellValue();
				CellActors[(PosX + l) * Height + PosY + k]->SetCellValue(TempValue + 1);
				CellActors[(PosX + l) * Height + PosY + k]->SetCellColor();

			}
	}

	return true;
}


void AGridActor::ShowGrid(int32 PosX, int32 PosY)
{
	if (PosX < 0 || PosX>Width - 1) return; // poza tablic¹ wyjœcie
	if (PosY < 0 || PosY>Height - 1) return; // poza tablic¹ wyjœcie
	if (CellActors[PosY * Width + PosX]->GetCellVisible() == true || CellActors[PosY * Width + PosX]->GetCellFlag() == true) return;  // ju¿ odkryte wyjœcie

	if (CellActors[PosY * Width + PosX]->GetCellValue() != 9 && CellActors[PosY * Width + PosX]->GetCellVisible() == false)
		CellActors[PosY * Width + PosX]->SetCellVisible(true);   // odkryj!

	if (CellActors[PosY * Width + PosX]->GetCellValue() != 0) return; // wartoœæ > 0 wyjœcie

	//wywo³anie funkcji dla ka¿dego s¹siada
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
//TODO napraw odkrywanie planszy
//TODO odkrywanie planszy, menu trudnoœci, umieszczanie min po pierwszym kliknieciu