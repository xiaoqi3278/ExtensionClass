// Fill out your copyright notice in the Description page of Project Settings.


#include "DevelopmentUtilities/ExtCheatManager.h"
#include "Manager/CheckBoxManager.h"
#include "FunctionLibrary/CheckBoxLibrary.h"
#include "Utilities/ExtLog.h"

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
