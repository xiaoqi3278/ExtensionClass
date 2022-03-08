// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Manager/ModelManager.h"

#include "Frame/Utilities/ModelTree.h"
#include "Utilities/ExtLog.h"

void UModelManager::OnBegin()
{
	ModelTree = NewObject<UModelTree>(this);

	Super::OnBegin();
}
