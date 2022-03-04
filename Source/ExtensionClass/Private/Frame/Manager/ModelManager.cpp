// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Manager/ModelManager.h"

#include "Frame/Utilities/ModelTree.h"

UModelManager::UModelManager()
{
	UBaseModel* MainModel = NewObject<UBaseModel>();
	ModelTree = NewObject<UModelTree>(MainModel);
}