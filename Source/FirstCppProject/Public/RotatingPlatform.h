// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatform.generated.h"
//#include "TimerManager.h"

UCLASS()
class FIRSTCPPPROJECT_API ARotatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// 1. 루트컴포넌트용 씬 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	USceneComponent* RootSceneComp;

	// 2. 스태틱 메시
	UPROPERTY(EditAnywhere, Category = "Platform|StaticMesh")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Rotation")
	float RotateSpeed;

	FTimerHandle MoveTimerHandle;

	void MoveByTimer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
	FVector MoveOffset = FVector(0.0f, 0.0f, 100.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
	float SetTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
	bool IsRepeat = false;

	FTimerHandle DestroyTimerHandle;

	void DestroyActor();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Destroy")
	float DestroyTime = 0.0f;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
