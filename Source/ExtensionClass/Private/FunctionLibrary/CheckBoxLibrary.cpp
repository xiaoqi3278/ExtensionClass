// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/CheckBoxLibrary.h"

#include "Kismet/GamePlayStatics.h"

#include "Manager/CheckBoxManager.h"
#include "Class/ExtCheckBox.h"
#include "Utilities/ExtLog.h"

ACheckBoxManager* UCheckBoxLibrary::GetCheckBoxManager(UObject* WorldContextObject)
{
	AActor* TempManager = UGameplayStatics::GetActorOfClass(WorldContextObject, ACheckBoxManager::StaticClass());

	if (TempManager == nullptr)
		return nullptr;

	return Cast<ACheckBoxManager>(TempManager);
}

void UCheckBoxLibrary::AddCheckBox(UObject* WorldContextObject, FString MainKey, FString ChildKey, UExtCheckBox* InCheckBox)
{
	ACheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	if (Manager == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("AddCheckBoxFaild: CheckBoxManager Get Faild!"));
		return;
	}

	if (Manager->CheckBoxMainMap.Contains(MainKey))
	{
		UE_LOG(ExtensionLog, Warning, TEXT("AddCheckBoxFaild: %s Does Not Contain %s"), *MainKey, *ChildKey);
		return;
	}

	//添加 ExtCheckBox
	Manager->CheckBoxMainMap.Find(MainKey)->CheckBoxChildMap.Emplace(ChildKey, InCheckBox);
}

UExtCheckBox* UCheckBoxLibrary::GetCheckBox(UObject* WorldContextObject, FString MainKey, FString ChildKey)
{
	ACheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	//如果不存在 MainKey 对应的组则直接返回空指针
	if (Manager == nullptr || !Manager->CheckBoxMainMap.Contains(MainKey))
		return nullptr;

	//如果不存在 ChildKey 对应的 ExtCheckBox FindRef 则会返回空指针
	return Manager->CheckBoxMainMap.Find(MainKey)->CheckBoxChildMap.FindRef(ChildKey);
}

TArray<UExtCheckBox*> UCheckBoxLibrary::GetCheckBoxArray(UObject* WorldContextObject, FString MainKey)
{
	ACheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);
	
	//如果不存在 MainKey 对应的组则直接返回空数组
	if (Manager == nullptr || !Manager->CheckBoxMainMap.Contains(MainKey))
		return TArray<UExtCheckBox*>();

	TArray<UExtCheckBox*> TempArr;
	(Manager->CheckBoxMainMap.Find(MainKey))->CheckBoxChildMap.GenerateValueArray(TempArr);

	return TempArr;
}

int32 UCheckBoxLibrary::GetCheckBoxIndex(UObject* WorldContextObject, FString MainKey, FString ChildKey)
{
	ACheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	//查找失败
	if (Manager == nullptr)
		return -2;

	//不存在对应组
	if (!Manager->CheckBoxMainMap.Contains(MainKey))
		return -1;

	int32 index = 0;
	for (auto& Itr : Manager->CheckBoxMainMap.Find(MainKey)->CheckBoxChildMap)
	{
		++index;
		if (Itr.Key == ChildKey)
			return index;
	}

	//不存在对应 ExtCheckBox
	return -1;
}

TMap<FString, UExtCheckBox*> UCheckBoxLibrary::GetChildMap(UObject* WorldContextObject, FString MainKey)
{
	ACheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);
	
	if (Manager == nullptr || !Manager->CheckBoxMainMap.Contains(MainKey))
		return TMap<FString, UExtCheckBox*>();

	return Manager->CheckBoxMainMap.Find(MainKey)->CheckBoxChildMap;
}

UExtCheckBox* UCheckBoxLibrary::GetCheckedOne(UObject* WorldContextObject, FString MainKey)
{
	ACheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	if (Manager == nullptr || !Manager->CheckBoxMainMap.Contains(MainKey))
		return nullptr;

	for (auto& Itr : Manager->CheckBoxMainMap.Find(MainKey)->CheckBoxChildMap)
	{
		if (Itr.Value->IsChecked())
			return Itr.Value;
	}

	return nullptr;
}

TArray<FString> UCheckBoxLibrary::GetMainKeyArray(UObject* WorldContextObject)
{
	ACheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	if (Manager == nullptr)
		return TArray<FString>();

	TArray<FString> StringArr;
	Manager->CheckBoxMainMap.GenerateKeyArray(StringArr);

	return StringArr;
}

void UCheckBoxLibrary::SetExtCheckedState(UObject* WorldContextObject, FString MainKey, FString ChildKey)
{
	ACheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);
	
	if (Manager == nullptr || !Manager->CheckBoxMainMap.Find(MainKey)->CheckBoxChildMap.Contains(ChildKey))
		return;

	UExtCheckBox* CheckedOne = GetCheckedOne(WorldContextObject, MainKey);
	UExtCheckBox* NeedCheckedOne = GetCheckBox(WorldContextObject, MainKey, ChildKey);

	if (CheckedOne == nullptr || NeedCheckedOne == nullptr)
		return;

	CheckedOne->SetExtCheckedState(ECheckBoxState::Unchecked);
	NeedCheckedOne->SetExtCheckedState(ECheckBoxState::Checked);
}
