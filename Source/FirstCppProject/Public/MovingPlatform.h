// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class FIRSTCPPPROJECT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	USceneComponent* RootSceneComp;

	UPROPERTY(EditAnywhere, Category = "Platform|StaticMesh")
	UStaticMeshComponent* StaticMeshComp;

	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Platform|Movement")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
	FVector MoveVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
	FVector MaxRange;

	FVector CurrentLocation;

	void CheckAndReverseAxis(EAxis::Type Axis);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
