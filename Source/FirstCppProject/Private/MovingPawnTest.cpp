// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPawnTest.h"
#include "SpartaPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h" 


// Sets default values
AMovingPawnTest::AMovingPawnTest()
{
	// BoxComp를 rootComponent로 설정
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	SetRootComponent(BoxComp);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(BoxComp);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(BoxComp);
	SpringArmComp->TargetArmLength = 300.0f;
	//SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bUsePawnControlRotation = false;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	BoxComp->SetSimulatePhysics(false);
	SkeletalMeshComp->SetSimulatePhysics(false);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPawnTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingPawnTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 이동
	AddActorLocalOffset(FVector(MoveInput.X * MaxMovementSpeed * DeltaTime
		, MoveInput.Y * MaxMovementSpeed * DeltaTime
		, 0.0f));
	
	// 회전 시
	// Yaw는 카메라, 액터를 같이 회전 -> 액터 자체를 돌리면 같이 회전됨

	// 액터 회전
	AddActorLocalRotation(FRotator(0.0f,
		LookInput.X * LookSensitivity * DeltaTime,
		0.0f));
	
	//// Pitch는 카메라만 회전
	//SpringArmComp->AddLocalRotation(FRotator(LookInput.Y * LookSensitivity * DeltaTime,
	//	0.0f,
	//	0.0f));


	// 현재 각도 저장
	FRotator SpringArmRotation = SpringArmComp->GetRelativeRotation();

	// 변화량
	const float PitchAmount = LookInput.Y * LookSensitivity * DeltaTime;

	// 각도 범위 제한
	SpringArmRotation.Pitch = FMath::Clamp(
		SpringArmRotation.Pitch + PitchAmount,	// 현재 값 + 변화량
		-85.0f,
		85.0f
	);

	SpringArmComp->SetRelativeRotation(SpringArmRotation);	// 최종 값 적용
}

// Called to bind functionality to input
void AMovingPawnTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				// 이 부분이 BP_캐릭터에서 Event로 바인딩 하는 부분인듯
				EnhancedInput->BindAction(
					PlayerController->MoveAction,	// BP 에서 설정한 IA_Move를 가져옴
					ETriggerEvent::Triggered,
					this,
					&AMovingPawnTest::Move	// 실제 동작할 함수의 주소값을 가져옴
				);	// -> MoveAction 이 있을 때, Move를 실행시키겠다 -> 그래서 UFUNCTION()로 Move 함수를 등록한듯
			}
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Completed,
					this,
					&AMovingPawnTest::StopMove
				);
			}
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Canceled,
					this,
					&AMovingPawnTest::StopMove
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AMovingPawnTest::Look
				);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Completed,
					this,
					&AMovingPawnTest::StopLook
				);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Canceled,
					this,
					&AMovingPawnTest::StopLook
				);
			}
		}
	}
}

void AMovingPawnTest::Move(const FInputActionValue& value)
{
	if (!Controller) return;
	
	MoveInput = value.Get<FVector2D>();
	/*MoveInput.X = GetActorForwardVector().X;
	MoveInput.Y = GetActorRightVector().Y;

	UE_LOG(LogTemp, Warning, TEXT("XX %f"), MoveInput.X);
	UE_LOG(LogTemp, Warning, TEXT("YY %f"), MoveInput.Y);*/
}

void AMovingPawnTest::StopMove(const FInputActionValue& value)
{
	if (!Controller) return;

	MoveInput = FVector2D(0.0f, 0.0f);

}

void AMovingPawnTest::Look(const FInputActionValue& value)
{
	if (!Controller) return;
	//const float pitch = SpringArmComp->GetRelativeRotation().Pitch;

	LookInput = value.Get<FVector2D>();
	/*if (pitch <= -85.0f && LookInput.Y <= 0.0f)
	{
		LookInput.Y = 0.0f;
	}
	if (pitch >= 85.0f && LookInput.Y >= 0.0f)
	{
		LookInput.Y = 0.0f;
	}

	UE_LOG(LogTemp, Warning, TEXT("pitch %f"), pitch);
	UE_LOG(LogTemp, Warning, TEXT("Y %f"), LookInput.Y);*/

}

void AMovingPawnTest::StopLook(const FInputActionValue& value)
{
	if (!Controller) return;

	LookInput = FVector2D(0.0f, 0.0f);
}

