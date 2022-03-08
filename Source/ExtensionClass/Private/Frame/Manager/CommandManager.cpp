// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Manager/CommandManager.h"

#include "Frame/Manager/ModelManager.h"
#include "Frame/Utilities/ModelLibrary.h"

void UCommandManager::EnqueueCommand(UBaseCommand* Command)
{
	CommandQueue.Enqueue(Command);

	UModelManager* ModelManager = UModelLibrary::GetModelManager(this);
	if (ModelManager != nullptr)
	{
		ModelManager->NotifyAllModelToProcesssingCommand(Command);
	}
}

void UCommandManager::DequeueCommand(UBaseCommand* Command)
{
	CommandQueue.Dequeue(Command);
}
