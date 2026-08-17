// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleSpawner.h"
#include "RotatingPlatform.h"
#include "MovingPlatform.h"

// Sets default values
APuzzleSpawner::APuzzleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APuzzleSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(
		SpawnRotatingPlatformTimerHandle, 
		this, 
		&APuzzleSpawner::SpawnRotatingPlatfromByTimer, 
		RoatingPlatformSpawnTime,
		IsRepeatRotatingPlatform);
	
	GetWorld()->GetTimerManager().SetTimer(
		SpawnMovingPlatformTimerHandle, 
		this, 
		&APuzzleSpawner::SpawnMovingPlatfromByTimer, 
		MovingPlatformSpawnTime,
		IsRepeatMovingPlatform);
}

void APuzzleSpawner::SpawnRotatingPlatfromByTimer()
{
	if (SpawnedRotatingActors.Num() < RotatingPlatfromCount)
	{
		const FVector RandomOffset(
			FMath::RandRange(-300.0f, 300.0f),	// X
			FMath::RandRange(-300.0f, 300.0f),	// Y
			FMath::RandRange(50.0f, 300.0f)		// Z
		);

		const FRotator SpawnRotation(
			FMath::RandRange(-15.0f, 15.0f),	// Pitch
			FMath::RandRange(0.0f, 360.0f),		// Yaw
			FMath::RandRange(-15.0f, 15.0f)		// Roll
		);

		ARotatingPlatform* SpawnedActor = GetWorld()->SpawnActor<ARotatingPlatform>(
			GetActorLocation() + RandomOffset,
			SpawnRotation
		);

		if (SpawnedActor)
		{
			SpawnedRotatingActors.Add(SpawnedActor);
		}
	}
	else
	{
		IsRepeatRotatingPlatform = false;

		GetWorld()->GetTimerManager().ClearTimer(
			SpawnRotatingPlatformTimerHandle
		);
	}

}

void APuzzleSpawner::SpawnMovingPlatfromByTimer()
{
	if (SpawnedMovingActors.Num() < MovingPlatfromCount)
	{
		const FVector RandomOffset(
			FMath::RandRange(-300.0f, 300.0f),	// X
			FMath::RandRange(-300.0f, 300.0f),	// Y
			FMath::RandRange(50.0f, 300.0f)		// Z
		);

		const FRotator SpawnRotation(
			FMath::RandRange(-15.0f, 15.0f),	// Pitch
			FMath::RandRange(0.0f, 360.0f),		// Yaw
			FMath::RandRange(-15.0f, 15.0f)		// Roll
		);

		AMovingPlatform* SpawnedActor = GetWorld()->SpawnActor<AMovingPlatform>(
			GetActorLocation() + RandomOffset,
			SpawnRotation
		);

		if (SpawnedActor)
		{
			SpawnedActor->SetMoveVelocity(FVector(
				FMath::RandRange(100.0, MaxMovingSpeedRange.X),
				FMath::RandRange(100.0, MaxMovingSpeedRange.Y), 
				FMath::RandRange(100.0, MaxMovingSpeedRange.Z))
			);
			SpawnedActor->SetMaxRange(FVector(
				FMath::RandRange(100.0, MaxMovingRange.X),
				FMath::RandRange(100.0, MaxMovingRange.Y),
				FMath::RandRange(100.0, MaxMovingRange.Z))
			);

			SpawnedMovingActors.Add(SpawnedActor);
		}
	}
	else
	{
		IsRepeatMovingPlatform = false;

		GetWorld()->GetTimerManager().ClearTimer(
			SpawnMovingPlatformTimerHandle
		);
	}
}

// Called every frame
void APuzzleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

