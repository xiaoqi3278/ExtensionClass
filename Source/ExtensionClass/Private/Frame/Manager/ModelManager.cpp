// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Manager/ModelManager.h"

#include "Frame/Utilities/ModelTree.h"

void UModelManager::OnBegin()
{
	Super::OnBegin();

	ModelTree = NewObject<UModelTree>(this);
}