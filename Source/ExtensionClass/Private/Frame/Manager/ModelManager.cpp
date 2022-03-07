// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Manager/ModelManager.h"

#include "Frame/Utilities/ModelTree.h"
#include "Utilities/ExtLog.h"

void UModelManager::OnBegin()
{
	Super::OnBegin();

	UE_LOG(ExtensionLog, Warning, TEXT("ModelManager Created!"));
	ModelTree = NewObject<UModelTree>(this);
}