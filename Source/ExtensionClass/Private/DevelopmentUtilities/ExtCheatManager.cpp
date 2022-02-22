// Fill out your copyright notice in the Description page of Project Settings.


#include "DevelopmentUtilities/ExtCheatManager.h"
#include "Manager/CheckBoxManager.h"
#include "FunctionLibrary/CheckBoxLibrary.h"

void UExtCheatManager::InitCheatManager()
{
	UE_LOG(LogTemp, Warning, TEXT("Create ExtCheatManager"));

	
}

void UExtCheatManager::ShowExtCheckBoxMainKeyInLog()
{
	TArray<FString> MainKeyArr = UCheckBoxLibrary::GetMainKeyArray(this);

	UE_LOG(LogTemp, Warning, TEXT("------------------------------------------MainKeyArrayStart------------------------------------------"));

	for (auto Itr : MainKeyArr)
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Itr);

	UE_LOG(LogTemp, Warning, TEXT("------------------------------------------MainKeyArrayEnd--------------------------------------------"));
}
