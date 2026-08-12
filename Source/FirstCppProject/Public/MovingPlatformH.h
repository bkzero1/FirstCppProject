// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatformH.generated.h"

UCLASS()
class FIRSTCPPPROJECT_API AMovingPlatformH : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatformH();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	USceneComponent* RootSceneComp;

	UPROPERTY(EditAnywhere, Category = "Platform|StaticMesh")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
	FVector StartLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
	int MaxRange;

	FVector CurrentLocation;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
