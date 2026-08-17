// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingPlatform.h"

// Sets default values
ARotatingPlatform::ARotatingPlatform()
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

	RotateSpeed = 30;
}

// Called when the game starts or when spawned
void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &ARotatingPlatform::MoveByTimer, SetTime, IsRepeat);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ARotatingPlatform::DestroyActorByTimer, DestroyTime, false);
}

void ARotatingPlatform::MoveByTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("Timer"));

	SetActorLocation(GetActorLocation() + MoveOffset);
	MoveOffset *= -1;
}

void ARotatingPlatform::DestroyActorByTimer()
{
	Destroy();
}

// Called every frame
void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotateSpeed))
	{
		AddActorLocalRotation(FRotator(RotateSpeed * DeltaTime, 0.0f, 0.0f));
	}
}

