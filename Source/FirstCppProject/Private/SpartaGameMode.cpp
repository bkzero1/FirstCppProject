// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameMode.h"
#include "MovingPawnTest.h"
#include "SpartaPlayerController.h"

ASpartaGameMode::ASpartaGameMode()
{
	DefaultPawnClass = AMovingPawnTest::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
}
