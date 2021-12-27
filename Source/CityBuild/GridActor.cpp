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
			SpawnedActorRef->SetCellPlace(i, j);
			SpawnedActorRef->SetCellValue(0);
			SpawnedActorRef->SetCellVisible(false);
			CellActors.Add(SpawnedActorRef);
		}
	}

	RandomPosition();
}

// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if(first)
	//{
		Clicked();
	//}
	//else
	//{
		//WaitForFirst();
	//}
}

void AGridActor::WaitForFirst()
{
	for (auto& Cell : CellActors)
	{
		//if (Cell->GetOccupied())
		{
			for (auto& Cello : CellActors)
			{
				//Cello->SetPlacable(false);
			}
			first = true;
			int32 i;
			int32 j;
			Cell->GetCellPlace(i, j);
			SetAliveNeighbors(i, j);
			break;
		}
	}
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
			SetAliveNeighbors(i, j);
		}
	}
}

int AGridActor::CountAliveNeighbors(const int32 i, const int32 j) {
	int NumAliveNeighbors = 0;
	for (int k = -1; k <= 1; k++) {
		for (int l = -1; l <= 1; l++) {
			if (!(l == 0 && k == 0)) {
				const int effective_i = i + k;
				const int effective_j = j + l;
				if ((effective_i >= 0 && effective_i < Height) && (effective_j >= 0 && effective_j < Width)) {
					//if (CellActors[effective_j + effective_i * Width]->GetPlacable()) {
						NumAliveNeighbors++;
					//}
				}
			}
		}
	}
	return NumAliveNeighbors;
}

void AGridActor::SetAliveNeighbors(const int32 i, const int32 j)
{
	for (int32 k = -1; k <= 1; k++) {
		for (int32 l = -1; l <= 1; l++) {
			if (!(l == 0 && k == 0)) {
				const int32 effective_i = i + k;
				const int32 effective_j = j + l;
				if ((effective_i >= 0 && effective_i < Height) && (effective_j >= 0 && effective_j < Width)) {
					//CellActors[effective_j + effective_i * Width]->SetPlacable(true);

				}
			}
		}
	}
}

void AGridActor::RandomPosition()
{
	int poz_x, poz_y;
	int ilosc = 10;



	while (ilosc > 0)
	{
		poz_x = FMath::RandRange(0, Width-1);
		poz_y = FMath::RandRange(0, Height-1);
		
		if (CellActors[poz_y * Width + poz_x]->GetCellValue() != 9)
		{
			PlaceMines(poz_x, poz_y);
			ilosc--;
		}
	}
}

bool AGridActor::PlaceMines(int32 poz_x, int32 poz_y)
{
	if (CellActors[poz_y * Width + poz_x]->GetCellValue() != 9)
	{
		CellActors[poz_y * Width + poz_x]->SetCellValue(9); //ustawiamy mine
		CellActors[poz_y * Width + poz_x]->SetCellColorMine();



		for (int k = -1; k < 2; k++)
			for (int l = -1; l < 2; l++)
			{
				if ((poz_x + l) < 0 || (poz_y + k) < 0) continue; //wyjdz bo krawedz
				if ((poz_x + l) > 9 || (poz_y + k) > 9) continue; //wyjdz bo krawedz


				if (CellActors[(poz_y + k) * Width + poz_x + l]->GetCellValue() == 9) continue; //wyjdz bo mina
				int32 TempValue = CellActors[(poz_y + k) * Width + poz_x + l]->GetCellValue();
				CellActors[(poz_y + k) * Width + poz_x + l]->SetCellValue(TempValue + 1);
				CellActors[(poz_y + k) * Width + poz_x + l]->SetCellColor();

			}
	}

	return true;
}


void AGridActor::odkryj_plansze(int32 x, int32 y)
{
	//if (x < 0 || x>9) return; // poza tablic¹ wyjœcie
	//if (y < 0 || y>9) return; // poza tablic¹ wyjœcie
	//if (plansza[x][y].odkryte == true) return;  // ju¿ odkryte wyjœcie
	//
	//if (plansza[x][y].wartosc != 9 && plansza[x][y].odkryte == false)
	//	plansza[x][y].odkryte = true;   // odkryj!
	//
	//if (plansza[x][y].wartosc != 0) return; // wartoœæ > 0 wyjœcie
	//
	////wywo³anie funkcji dla ka¿dego s¹siada
	//odkryj_plansze(x - 1, y - 1);
	//odkryj_plansze(x - 1, y);
	//odkryj_plansze(x - 1, y + 1);
	//odkryj_plansze(x + 1, y - 1);
	//odkryj_plansze(x + 1, y);
	//odkryj_plansze(x + 1, y + 1);
	//odkryj_plansze(x, y - 1);
	//odkryj_plansze(x, y);
	//odkryj_plansze(x, y + 1);
}

//TODO odkrywanie planszy, menu trudnoœci, umieszczanie min po pierwszym kliknieciu