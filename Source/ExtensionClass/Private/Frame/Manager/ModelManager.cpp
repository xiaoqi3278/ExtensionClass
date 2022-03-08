// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Manager/ModelManager.h"

#include "Frame/Utilities/ModelTree.h"
#include "Utilities/ExtLog.h"
#include "Frame/Model/BaseModel.h"
#include "Frame/Utilities/ModelLibrary.h"
#include "Frame/Manager/CommandManager.h"
#include "Frame/Utilities/CommandLibrary.h"

void UModelManager::OnBegin()
{
	ModelTree = NewObject<UModelTree>(this);

	Super::OnBegin();
}

void UModelManager::NotifyAllModelToProcesssingCommand(UBaseCommand* Command)
{
	TArray<UBaseModel*> ModelArray = UModelLibrary::GetAllModel(this);

	for (auto& Itr : ModelArray)
	{
		Itr->ProcessingCommand(Command);
	}

	//ÃüÁî³ö¶Ó
	UCommandManager* CommandManager = UCommandLibrary::GetCommandManager(this);
	if (CommandManager != nullptr)
	{
		CommandManager->DequeueCommand(Command);
	}
}
