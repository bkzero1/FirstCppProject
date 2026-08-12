// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatformH.h"

// Sets default values
AMovingPlatformH::AMovingPlatformH()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(RootSceneComp);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(RootSceneComp);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_AssetPlatform.SM_AssetPlatform"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Engine/EditorResources/FieldNodes/_Resources/M_FieldRadiusPreview.M_FieldRadiusPreview"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}
	
	MoveSpeed = 200;
	MaxRange = 200;
}

// Called when the game starts or when spawned
void AMovingPlatformH::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	CurrentLocation = StartLocation;
}

// Called every frame
void AMovingPlatformH::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentLocation = GetActorLocation() + FVector(0.0f, MoveSpeed * DeltaTime, 0.0f);

	SetActorLocation(CurrentLocation);

	if(CurrentLocation.Y - StartLocation.Y >= MaxRange && MoveSpeed > 0.0f)// 최대 범위 이상 갔으면 + 스피드가 양수이면
	{
		// 스피드를 반대로
		MoveSpeed *= -1;
	}
	else if (CurrentLocation.Y - StartLocation.Y < 0 && MoveSpeed < 0.0f)// 시작지점까지 돌아왔으면 + 스피드가 음수이면
	{
		// 다시 스피드를 반대로
		MoveSpeed *= -1;
	}
}

