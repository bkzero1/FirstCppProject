// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
	/*
	아래 코드들은 한 문장으로 보면 이렇게입니다.
	
	AItem이 만들어질 때, 보이지 않는 기준점과 의자 모양 메시를 준비하고, 의자 메시와 금색 재질을 붙인다.

	처음에는 전부 외우려 하지 말고, "무엇을 만들고 → 어떻게 연결하고 → 어떤 모습을 입히는가" 순서로 읽으시면 편합니다.

	구조를 그림으로 보면 이렇습니다.
	AItem
	└─ SceneRoot                 ← 보이지 않는 기준점
	   └─ StaticMeshComp          ← 의자 모양을 화면에 보여 주는 부품
		  ├─ SM_Chair             ← 실제 메시 에셋
		  └─ M_Metal_Gold         ← 표면 재질 에셋
	*/

	// 1. 기준점 역할의 루트 컴포넌트를 만든다.
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	// 2. 화면에 보일 메시 컴포넌트를 만든다.
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	// 3. 메시를 루트 기준점 아래에 붙인다.
	StaticMeshComp->SetupAttachment(SceneRoot);

	// 헤더파일에서 디테일창에서 EditAnywhere로 했기 때문에 없어도 설정 가능
	// 4. Content 폴더에서 의자 메시 에셋을 찾는다.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Chair.SM_Chair"));

	// 5. 찾기에 성공했다면 메시 컴포넌트에 의자를 적용한다.
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	// 6. 금색 머티리얼 에셋을 찾는다.
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Metal_Gold.M_Metal_Gold"));
	
	// 7. 찾기에 성공했다면 메시의 첫 번째 머티리얼 칸에 적용한다.
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	PrimaryActorTick.bCanEverTick = true;
	
	RotationSpeed = 90.0f;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	//SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	//SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));	// pitch , yaw, roll
	//												//   y	 ,  z ,  x
	//SetActorScale3D(FVector(2.0f));
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}

}