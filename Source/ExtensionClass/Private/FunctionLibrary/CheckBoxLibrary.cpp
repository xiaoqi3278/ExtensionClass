// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/CheckBoxLibrary.h"

#include "Kismet/GamePlayStatics.h"

#include "Manager/CheckBoxManager.h"
#include "Class/ExtCheckBox.h"
#include "Utilities/ExtLog.h"
#include "Frame/ExtGameInstance.h"

void UCheckBoxLibrary::TestFunction(UObject* WorldContextObject)
{
	UCheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	CheckAndOutLog(WorldContextObject, Manager, "<MainKey_NULL>", "<ChildKey_NULL>", 1, "TestFunctin");
}

UCheckBoxManager* UCheckBoxLibrary::GetCheckBoxManager(UObject* WorldContextObject)
{
	//UCheckBoxManager* CheckBoxManager = Cast<UExtGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject))->CheckBoxManager;
	UExtGameInstance* GameInstance = Cast<UExtGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));

	if (GameInstance == nullptr)
	{
		return nullptr;
	}

	return GameInstance->CheckBoxManager;
}

TMap<FString, FCheckBoxGroup> UCheckBoxLibrary::GetCheckBoxMainMap(UObject* WorldContextObject)
{
	UCheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);
	
	if (CheckAndOutLog(WorldContextObject, Manager, "", "", 1, "GetCheckBoxMainMap"))
	{
		return TMap<FString, FCheckBoxGroup>();
	}

	return Manager->CheckBoxMainMap;
}

TMap<FString, UExtCheckBox*> UCheckBoxLibrary::GetCheckBoxChildMap(UObject* WorldContextObject, FString MainKey)
{
	UCheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	//if (Manager == nullptr || !Manager->CheckBoxMainMap.Contains(MainKey))
	if (CheckAndOutLog(WorldContextObject, Manager, MainKey, "", 2, "GetCheckBoxChildMap"))
	{
		return TMap<FString, UExtCheckBox*>();
	}

	return Manager->CheckBoxMainMap.Find(MainKey)->CheckBoxChildMap;
}

TArray<UExtCheckBox*> UCheckBoxLibrary::GetCheckBoxArray(UObject* WorldContextObject, FString MainKey)
{
	UCheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	//如果不存在 MainKey 对应的组则直接返回空数组
	if (Manager == nullptr || !Manager->CheckBoxMainMap.Contains(MainKey))
	{
		return TArray<UExtCheckBox*>();
	}

	TArray<UExtCheckBox*> TempArr;
	(Manager->CheckBoxMainMap.Find(MainKey))->CheckBoxChildMap.GenerateValueArray(TempArr);

	return TempArr;
}

UExtCheckBox* UCheckBoxLibrary::GetCheckBox(UObject* WorldContextObject, FString MainKey, FString ChildKey)
{
	UCheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	//如果不存在 MainKey 对应的组则直接返回空指针
	if (Manager == nullptr || !Manager->CheckBoxMainMap.Contains(MainKey))
	{
		return nullptr;
	}

	//如果不存在 ChildKey 对应的 ExtCheckBox FindRef 则会返回空指针
	return Manager->CheckBoxMainMap.Find(MainKey)->CheckBoxChildMap.FindRef(ChildKey);
}

bool UCheckBoxLibrary::CheckAndOutLog(UObject* WorldContextObject, UCheckBoxManager* Manager, FString MainKey, FString ChildKey, int32 Index, FString FunctionName)
{
	//Manager 是否有效
	if (Index > 0 && Manager == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] %s(): CheckBoxManager Get Faild!"), *WorldContextObject->GetName(), *FunctionName);
		return true;
	}

	//是否存在 MainKey
	if (Index > 1 && !Manager->CheckBoxMainMap.Contains(MainKey))
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] %s(): ExtCheckBoxManager Does not Contain %s"), *WorldContextObject->GetName(), *FunctionName, *MainKey);
		return true;
	}

	//是否存在 ChildKey
	if (Index > 2 && !Manager->CheckBoxMainMap.Find(MainKey)->CheckBoxChildMap.Contains(ChildKey))
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] &s(): ExtCheckBoxManager=>%s Does not Contain %s"), *WorldContextObject->GetFName().ToString(), *FunctionName, *MainKey, *ChildKey);
		return true;
	}

	return false;
}

void UCheckBoxLibrary::AddCheckBox(UObject* WorldContextObject, FString MainKey, FString ChildKey, UExtCheckBox* InCheckBox)
{
	UCheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	if (Manager == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s]. AddCheckBoxFaild: CheckBoxManager Get Faild!"), *WorldContextObject->GetFName().ToString());
		return;
	}

	//添加 ExtCheckBox
	Manager->CheckBoxMainMap.FindOrAdd(MainKey).CheckBoxChildMap.Emplace(ChildKey, InCheckBox);
}

int32 UCheckBoxLibrary::GetCheckBoxIndex(UObject* WorldContextObject, FString MainKey, FString ChildKey)
{
	UCheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	//查找失败
	if (Manager == nullptr)
	{
		return -2;
	}

	//不存在对应组
	if (!Manager->CheckBoxMainMap.Contains(MainKey))
	{
		return -1;
	}

	int32 index = 0;
	for (auto& Itr : Manager->CheckBoxMainMap.Find(MainKey)->CheckBoxChildMap)
	{
		++index;
		if (Itr.Key == ChildKey)
		{
			return index;
		}
	}

	//不存在对应 ExtCheckBox
	return -1;
}

UExtCheckBox* UCheckBoxLibrary::GetCheckedOne(UObject* WorldContextObject, FString MainKey)
{
	UCheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	if (CheckAndOutLog(WorldContextObject, Manager, MainKey, "", 2, "GetCheckedOne"))
	{
		return nullptr;
	}

	FString CheckedKey = Manager->CheckBoxMainMap.Find(MainKey)->CheckedChildKey;
	if (CheckedKey != "ChildKey_NULL")
	{
		return (Manager->CheckBoxMainMap.Find(MainKey)->CheckBoxChildMap).FindRef(CheckedKey);
	}

	UE_LOG(ExtensionLog, Warning, TEXT("[%s] GetCheckedOne: %s Does Not Have CheckedOne!"), *WorldContextObject->GetFName().ToString(), *MainKey);
	return nullptr;
}

TArray<FString> UCheckBoxLibrary::GetMainKeyArray(UObject* WorldContextObject)
{
	UCheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	if (Manager == nullptr)
	{
		return TArray<FString>();
	}

	TArray<FString> StringArr;
	Manager->CheckBoxMainMap.GenerateKeyArray(StringArr);

	return StringArr;
}

TArray<FString> UCheckBoxLibrary::GetChildKeyArray(UObject* WorldContextObject, FString MainKey)
{
	UCheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	//有效性判断
	if (CheckAndOutLog(WorldContextObject, Manager, MainKey, "", 2, "GetChildKeyArray"))
	{
		return TArray<FString>();
	}

	TArray<FString> ChildKeyArray;
	for (auto& Itr : Manager->CheckBoxMainMap.Find(MainKey)->CheckBoxChildMap)
	{
		ChildKeyArray.Add(Itr.Value->ChildKey);
	}

	return ChildKeyArray;
}

FString UCheckBoxLibrary::GetCheckedChildKey(UObject* WorldContextObject, FString MainKey)
{
	UCheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);

	//有效性判断
	if (CheckAndOutLog(WorldContextObject, Manager, MainKey, "", 2, "GetCheckedChildKey"))
	{
		return "";
	}

	return Manager->CheckBoxMainMap.Find(MainKey)->CheckedChildKey;
}

void UCheckBoxLibrary::SetOneExtChecked(UObject* WorldContextObject, FString MainKey, FString ChildKey)
{
	UCheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);
	
	//有效性判断
	if (CheckAndOutLog(WorldContextObject, Manager, MainKey, ChildKey, 3, "SetOneExtChecked"))
	{
		return;
	}

	UExtCheckBox* CheckedOne = GetCheckedOne(WorldContextObject, MainKey);
	UExtCheckBox* NeedCheckedOne = GetCheckBox(WorldContextObject, MainKey, ChildKey);

	//是否存在已选中的ExtCheckeBox
	if (CheckedOne == nullptr)
	{
		
	}
	else
	{
		CheckedOne->SetExtCheckedState(ECheckBoxState::Unchecked, true);
	}

	if (NeedCheckedOne == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] SetOneExtChecked: %s=>%s Is nullptr"), *WorldContextObject->GetFName().ToString(), *MainKey, *ChildKey);
		return;
	}

	NeedCheckedOne->SetExtCheckedState(ECheckBoxState::Checked, true);
	Manager->CheckBoxMainMap.Find(MainKey)->CheckedChildKey = ChildKey;

}

void UCheckBoxLibrary::SetOneExtCheckedState(UObject* WorldContextObject, FString MainKey, FString ChildKey, ECheckBoxState State)
{
	UExtCheckBox* CheckedOne = GetCheckedOne(WorldContextObject, MainKey);
	UExtCheckBox* CheckBox = GetCheckBox(WorldContextObject, MainKey, ChildKey);

	UCheckBoxManager* Manager = GetCheckBoxManager(WorldContextObject);
	if (CheckAndOutLog(WorldContextObject, Manager, MainKey, ChildKey, 2, "SetOneExtCheckedState"))
	{
		return;
	}

	//已选中的取消选中
	if (CheckedOne != nullptr && State != ECheckBoxState::Unchecked)
	{
		//Manager->CheckBoxMainMap.Find(MainKey)->CheckedChildKey = "ChildKey_NULL";
		CheckedOne->SetExtCheckedState(ECheckBoxState::Unchecked, true);
		
	}

	if (CheckBox != nullptr)
	{
		//Manager->CheckBoxMainMap.Find(MainKey)->CheckedChildKey = ChildKey;
		CheckBox->SetExtCheckedState(State, true);
	}
}
