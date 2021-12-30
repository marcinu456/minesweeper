// Fill out your copyright notice in the Description page of Project Settings.


#include "CellActor.h"

#include "CityBuildGameModeBase.h"
#include "GridActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACellActor::ACellActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CellRootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CellMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	FScriptDelegate OnClickedDelegate;
	FScriptDelegate OnBeginCursorOverDelegate;
	FScriptDelegate OnEndCursorOverDelegate;
	OnClickedDelegate.BindUFunction(this, "Clicked");
	OnBeginCursorOverDelegate.BindUFunction(this, "BeginCursorOver");
	OnEndCursorOverDelegate.BindUFunction(this, "EndCursorOver");
	OnClicked.Add(OnClickedDelegate);
	OnBeginCursorOver.Add(OnBeginCursorOverDelegate);
	OnEndCursorOver.Add(OnEndCursorOverDelegate);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Game/Materials/Shape_Sphere.Shape_Sphere"));
	if (SphereMeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(SphereMeshAsset.Object);
	}
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
	if(CellVisible)
	{
		StaticMeshComponent->SetMaterial(0, RedColorOfCell);
		EndCursorOverMaterial = RedColorOfCell;
	}
}

void ACellActor::Clicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Some warning message"));
	CellVisible = true;
	StaticMeshComponent->SetMaterial(0, RedColorOfCell);
	EndCursorOverMaterial = RedColorOfCell;

	GridActorManager->odkryj_plansze(CellX, CellY);
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

