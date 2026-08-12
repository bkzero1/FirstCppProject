// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
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

	MoveVelocity = FVector(0.0f, 200.0f, 0.0f);
	MaxRange = FVector(0.0f, 200.0f, 0.0f);
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	CurrentLocation = StartLocation;
}

void AMovingPlatform::CheckAndReverseAxis(EAxis::Type Axis)
{
	const float StartAxis = StartLocation.GetComponentForAxis(Axis);
	float CurrentAxis = CurrentLocation.GetComponentForAxis(Axis);
	const float MaxAxis = MaxRange.GetComponentForAxis(Axis);
	float VelocityAxis = MoveVelocity.GetComponentForAxis(Axis);

	const float DistanceFromStart = CurrentAxis - StartAxis;	// 레퍼런스로는 불가능해서 아래 if문에서 실제 대입
	if (FMath::IsNearlyZero(VelocityAxis) || FMath::IsNearlyZero(MaxAxis))
		return;
	if (DistanceFromStart >= MaxAxis && VelocityAxis > 0.0f)// 최대 범위 이상 갔으면 + 스피드가 양수이면
	{
		// 스피드를 반대로
		VelocityAxis *= -1;
		MoveVelocity.SetComponentForAxis(Axis, VelocityAxis);
		
	}
	else if (DistanceFromStart < 0 && VelocityAxis < 0.0f)// 시작지점까지 돌아왔으면 + 스피드가 음수이면
	{
		// 다시 스피드를 반대로
		VelocityAxis *= -1;
		MoveVelocity.SetComponentForAxis(Axis, VelocityAxis);
	}
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector AppliedVelocity = MoveVelocity;

	// 범위가 없는 축은 이번 프레임 이동에서 제외
	if (FMath::IsNearlyZero(MaxRange.X))
	{
		AppliedVelocity.X = 0.0f;
	}

	if (FMath::IsNearlyZero(MaxRange.Y))
	{
		AppliedVelocity.Y = 0.0f;
	}

	if (FMath::IsNearlyZero(MaxRange.Z))
	{
		AppliedVelocity.Z = 0.0f;
	}

	CurrentLocation = GetActorLocation() + AppliedVelocity * DeltaTime;

	SetActorLocation(CurrentLocation);

	// 방향 반전을 위한 함수
	CheckAndReverseAxis(EAxis::X);
	CheckAndReverseAxis(EAxis::Y);
	CheckAndReverseAxis(EAxis::Z);
	//if (CurrentLocation.Y - StartLocation.Y >= MaxRange.Y && MoveVelocity.Y > 0.0f)// 최대 범위 이상 갔으면 + 스피드가 양수이면
	//{
	//	// 스피드를 반대로
	//	MoveVelocity.Y *= -1;
	//}
	//else if (CurrentLocation.Y - StartLocation.Y < 0 && MoveVelocity.Y < 0.0f)// 시작지점까지 돌아왔으면 + 스피드가 음수이면
	//{
	//	// 다시 스피드를 반대로
	//	MoveVelocity.Y *= -1;
	//}
}

