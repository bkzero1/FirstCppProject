// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovingPawnTest.generated.h"

class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;
struct FInputActionValue;

UCLASS()
class FIRSTCPPPROJECT_API AMovingPawnTest : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovingPawnTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/*-`CapsuleComponent` (또는 Box / Sphere 중 택 1)
	- `SkeletalMeshComponent`
	- `SpringArmComponent`
	- `CameraComponent`*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn|Components")
	UBoxComponent* BoxComp;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn|Components")
	USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn|Components")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn|Components")
	UCameraComponent* CameraComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn|Mobility")
	FVector2D MoveInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn|Mobility")
	float MaxMovementSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn|Mobility")
	FVector2D LookInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn|Mobility")
	float LookSensitivity = 60.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StopMove(const FInputActionValue& value);

	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StopLook(const FInputActionValue& value);
};
