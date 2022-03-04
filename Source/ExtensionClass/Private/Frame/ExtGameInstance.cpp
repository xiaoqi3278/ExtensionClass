// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/ExtGameInstance.h"

#include "Frame/Manager/WidgetManager.h"
#include "Frame/Utilities/ModelTree.h"
#include "Frame/Model/BaseModel.h"

void UExtGameInstance::Init()
{
	WidgetManager = NewObject<UWidgetManager>(this);

	//UBaseModel* MainModel = NewObject<UBaseModel>();
	//ModelTree = NewObject<UModelTree>(MainModel);
}
