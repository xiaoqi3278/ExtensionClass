// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/ExtGameInstance.h"

#include "Frame/Manager/WidgetManager.h"
#include "Frame/Utilities/ModelTree.h"
#include "Frame/Model/BaseModel.h"
#include "Frame/Manager/ModelManager.h"

void UExtGameInstance::Init()
{
	WidgetManager = NewObject<UWidgetManager>(this);
	ModelManager = NewObject<UModelManager>(this);

	Super::Init();
}
