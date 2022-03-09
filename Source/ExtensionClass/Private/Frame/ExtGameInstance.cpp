// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/ExtGameInstance.h"

#include "Frame/Manager/WidgetManager.h"
#include "ExtensionClass/Public/Manager/CheckBoxManager.h"
#include "ExtensionClass/Public/Manager/ActorManager.h"
#include "Frame/Utilities/ModelTree.h"
#include "Frame/Model/BaseModel.h"
#include "Frame/Manager/ModelManager.h"
#include "Utilities/ExtLog.h"
#include "Frame/Manager/CommandManager.h"

void UExtGameInstance::Init()
{
	Super::Init();

	WidgetManager = NewObject<UWidgetManager>(this);
	CheckBoxManager = NewObject<UCheckBoxManager>(this);
	ActorManager = NewObject<UActorManager>(this);
	ModelManager = NewObject<UModelManager>(this, ModelManagerClass);
	CommandManager = NewObject<UCommandManager>(this);

	//ModelManager->ModelManagerBegin();
}

void UExtGameInstance::OnStart()
{
	ModelManager->ModelManagerBegin();
}

