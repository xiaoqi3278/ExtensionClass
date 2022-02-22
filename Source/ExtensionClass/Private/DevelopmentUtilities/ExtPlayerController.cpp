// Fill out your copyright notice in the Description page of Project Settings.


#include "DevelopmentUtilities/ExtPlayerController.h"
#include "DevelopmentUtilities/ExtCheatManager.h"

AExtPlayerController::AExtPlayerController()
{
	CheatClass = UExtCheatManager::StaticClass();
}
