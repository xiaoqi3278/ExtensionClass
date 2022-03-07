// Fill out your copyright notice in the Description page of Project Settings.


#include "DevelopmentUtilities/ExtCheatManager.h"

#include "Manager/CheckBoxManager.h"
#include "FunctionLibrary/CheckBoxLibrary.h"
#include "Utilities/ExtLog.h"
#include "Frame/Utilities/ModelLibrary.h"
#include "Frame/Model/BaseModel.h"
#include "Frame/Manager/ModelManager.h"
#include "Frame/Utilities/ModelTree.h"

void UExtCheatManager::InitCheatManager()
{
	UE_LOG(ExtensionLog, Log, TEXT("Create ExtCheatManager"));

	
}

void UExtCheatManager::ShowMainKey()
{
	TArray<FString> MainKeyArr = UCheckBoxLibrary::GetMainKeyArray(this);

	UE_LOG(ExtensionLog, Log, TEXT("------------------------------------------MainKeyArrayStart------------------------------------------"));

	for (auto Itr : MainKeyArr)
		UE_LOG(ExtensionLog, Log, TEXT("%s"), *Itr);

	UE_LOG(ExtensionLog, Log, TEXT("-------------------------------------------MainKeyArrayEnd-------------------------------------------"));
}

void UExtCheatManager::ShowChildKey(FString MainKey)
{
	TArray<FString> ChildKeyArr = UCheckBoxLibrary::GetChildKeyArray(this, MainKey);

	UE_LOG(ExtensionLog, Log, TEXT("----------------------------------------------MainKey: %s------------------------------------------"), *MainKey);
	UE_LOG(ExtensionLog, Log, TEXT("------------------------------------------ChildKeyArrayStart------------------------------------------"));

	for (auto Itr : ChildKeyArr)
		UE_LOG(ExtensionLog, Log, TEXT("%s"), *Itr);

	UE_LOG(ExtensionLog, Log, TEXT("-------------------------------------------ChildKeyArrayEnd------------------------------------------"));
}

void UExtCheatManager::ShowAllModelName()
{
	TArray<UBaseModel*> ModelArr = UModelLibrary::GetAllModel(this);

	UE_LOG(ExtensionLog, Log, TEXT("----------------------------------------------ModelStart---------------------------------------------"));

	for (auto& Itr : ModelArr)
		UE_LOG(ExtensionLog, Log, TEXT("%s"), *Itr->GetName())

	UE_LOG(ExtensionLog, Log, TEXT("-----------------------------------------------ModelEnd----------------------------------------------"));
}

void UExtCheatManager::ShowAllModelNum()
{
	UModelTree* ModelTree = UModelLibrary::GetModelManager(this)->ModelTree;

	UE_LOG(ExtensionLog, Log, TEXT("The Num Of All Model: %d"), ModelTree->GetAllNode().Num());
}

void UExtCheatManager::ShowTest()
{
	UModelTree* Test = UModelLibrary::GetModelManager(this)->ModelTree;

	UE_LOG(ExtensionLog, Log, TEXT("---------------------------------------------ShowTestStart-------------------------------------------"));

	for (auto& Itr : Test->GetAllNode())
		UE_LOG(ExtensionLog, Log, TEXT("%s"), *Itr->Model->GetName());

	UE_LOG(ExtensionLog, Log, TEXT("----------------------------------------------ShowTestEnd--------------------------------------------"));
}
