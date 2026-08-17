// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleSpawner.generated.h"

UCLASS()
class FIRSTCPPPROJECT_API APuzzleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedRotatingActors;
	
	FTimerHandle SpawnRotatingPlatformTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Roatating")
	int RotatingPlatfromCount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Roatating")
	float RoatingPlatformSpawnTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Roatating")
	bool IsRepeatRotatingPlatform = true;

	void SpawnRotatingPlatfromByTimer();
	

	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedMovingActors;

	FTimerHandle SpawnMovingPlatformTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Moving")
	int MovingPlatfromCount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Moving")
	float MovingPlatformSpawnTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Moving")
	bool IsRepeatMovingPlatform = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Moving")
	FVector MaxMovingRange = FVector(500.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Moving")
	FVector MaxMovingSpeedRange = FVector(500.0f);
	

	void SpawnMovingPlatfromByTimer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
