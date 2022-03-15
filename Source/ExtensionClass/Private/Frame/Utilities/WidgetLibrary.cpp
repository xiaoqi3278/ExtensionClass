// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Utilities/WidgetLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

#include "ExtensionClass/Public/Utilities/ExtLog.h"
#include "Frame/ExtGameInstance.h"
#include "Frame/Manager/WidgetManager.h"
#include "ExtensionClass/Public/Class/ExtUserWidget.h"



UWidgetManager* UWidgetLibrary::GetWidgetManager(UObject* WorldContextObject)
{
	UExtGameInstance* TempGameInstance = Cast<UExtGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));

	if (TempGameInstance != nullptr)
	{
		return TempGameInstance->WidgetManager;
	}

	return nullptr;
}

UExtUserWidget* UWidgetLibrary::CreateExtWidget(UObject* WorldContextObject, TSubclassOf<UExtUserWidget> WidgetClass)
{
	if (WidgetClass != nullptr)
	{
		return CreateWidget<UExtUserWidget>(UGameplayStatics::GetPlayerController(WorldContextObject, 0), WidgetClass);
	}

	return nullptr;
}

void UWidgetLibrary::AddToWidgetManager(UObject* WorldContextObject, FString WidgetKey, UExtUserWidget* Widget)
{
	UWidgetManager* WidgetManager = GetWidgetManager(WorldContextObject);

	if (WidgetManager != nullptr)
	{
		WidgetManager->WidgetMap.Emplace(WidgetKey, Widget);
	}
}

void UWidgetLibrary::AddToWidgetManagerOfGroup(UObject* WorldContextObject, FString WidgetMainKey, FString WidgetChildKey, UExtUserWidget* Widget)
{
	UWidgetManager* WidgetManager = GetWidgetManager(WorldContextObject);

	if (WidgetManager != nullptr)
	{
		//GetWidgetGroup(WorldContextObject, WidgetMainKey).WidgetChildMap.Emplace(WidgetChildKey, Widget);
		WidgetManager->WidgetMainMap.FindOrAdd(WidgetMainKey).WidgetChildMap.Emplace(WidgetChildKey, Widget);
	}
}

UExtUserWidget* UWidgetLibrary::GetWidget(UObject* WorldContextObject, FString WidgetKey, TSubclassOf<UExtUserWidget> WidgetClass)
{
	UWidgetManager* WidgetManager = GetWidgetManager(WorldContextObject);

	if (WidgetManager != nullptr)
	{
		return WidgetManager->WidgetMap.FindRef(WidgetKey);
	}
	return nullptr;
}

UExtUserWidget* UWidgetLibrary::GetWidgetOfGroup(UObject* WorldContextObject, FString WidgetMainKey, FString WidgetChildKey)
{
	UWidgetManager* WidgetManager = GetWidgetManager(WorldContextObject);

	if (WidgetManager != nullptr)
	{
		return GetWidgetGroup(WorldContextObject, WidgetMainKey).WidgetChildMap.FindRef(WidgetChildKey);
	}

	return nullptr;
}

FWidgetGroup UWidgetLibrary::GetWidgetGroup(UObject* WorldContextObject, FString WidgetMainKey)
{
	UWidgetManager* WidgetManager = GetWidgetManager(WorldContextObject);

	if (WidgetManager != nullptr)
	{
		return WidgetManager->WidgetMainMap.FindRef(WidgetMainKey);
	}

	//WidgetManager 中不存在 WidgetMainKey
	UE_LOG(ExtensionLog, Warning, TEXT("[%s] GetWidgetGroup(): WidgetManager=>WidgetMainMap Does not Contain %s"), *WorldContextObject->GetName(), *WidgetMainKey);
	return FWidgetGroup();
}

TArray<UExtUserWidget*> UWidgetLibrary::GetWidgetArrayOfGroup(UObject* WorldContextObject, FString WidgetMainKey)
{
	UWidgetManager* WidgetManager = GetWidgetManager(WorldContextObject);

	if (WidgetManager != nullptr)
	{
		TMap<FString, UExtUserWidget*> WidgetMap = WidgetManager->WidgetMainMap.FindRef(WidgetMainKey).WidgetChildMap;

		TArray<UExtUserWidget*> WidgetArray;
		WidgetMap.GenerateValueArray(WidgetArray);

		return WidgetArray;
	}

	return TArray<UExtUserWidget*>();
}

TArray<UExtUserWidget*> UWidgetLibrary::GetAllWidget(UObject* WorldContextObject)
{
	TArray<UExtUserWidget*> WidgetArray = TArray<UExtUserWidget*>();

	UWidgetManager* WidgetManager = GetWidgetManager(WorldContextObject);
	if (WidgetManager == nullptr)
	{
		return WidgetArray;
	}

	//获取 WidgetMap 中的所有 ExtUserWidget
	for (auto& Itr : WidgetManager->WidgetMap)
	{
		WidgetArray.Add(Itr.Value);
	}

	//获取 WidgetMainMap 中所有组的所有 ExtUserWidget
	for (auto& Itr : WidgetManager->WidgetMainMap)
	{
		TArray<UExtUserWidget*> TempWidgetArray = TArray<UExtUserWidget*>();
		Itr.Value.WidgetChildMap.GenerateValueArray(TempWidgetArray);
		WidgetArray.Append(TempWidgetArray);
	}

	return WidgetArray;
}

TArray<FString> UWidgetLibrary::GetAllWidgetKey(UObject* WorldContextObject)
{
	TArray<FString> KeyArray = TArray<FString>();

	UWidgetManager* WidgetManager = GetWidgetManager(WorldContextObject);
	if (WidgetManager == nullptr)
	{
		return KeyArray;
	}

	//获取 WidgetMap 中的所有 ExtUserWidget
	for (auto& Itr : WidgetManager->WidgetMap)
	{
		KeyArray.Add(Itr.Key);
	}

	//获取 WidgetMainMap 中所有组的所有 ExtUserWidget
	for (auto& Itr : WidgetManager->WidgetMainMap)
	{
		TArray<FString> TempWidgetArray = TArray<FString>();
		Itr.Value.WidgetChildMap.GenerateKeyArray(TempWidgetArray);
		KeyArray.Append(TempWidgetArray);
	}

	return KeyArray;
}

void UWidgetLibrary::RemoveWidget(UObject* WorldContextObject, FString WidgetKey)
{
	UWidgetManager* WidgetManager = GetWidgetManager(WorldContextObject);

	UExtUserWidget* Widget = GetWidget(WorldContextObject, WidgetKey, WidgetManager->GetClass());

	if (WidgetManager != nullptr && Widget != nullptr)
	{
		UE_LOG(ExtensionLog, Log, TEXT("[%s] RemoveWidget(): 从 WidgetMap 中移除 %s !"), *WorldContextObject->GetName(), *Widget->GetName());
		WidgetManager->WidgetMap.Remove(WidgetKey);
		WidgetManager->WidgetMap.Compact();
		WidgetManager->WidgetMap.Shrink();
	}
}

void UWidgetLibrary::RemoveOneOfGroupWidget(UObject* WorldContextObject, FString WidgetMainKey, FString WidgetChildKey)
{
	UWidgetManager* WidgetManager = GetWidgetManager(WorldContextObject);
	UExtUserWidget* Widget = GetWidgetOfGroup(WorldContextObject, WidgetMainKey, WidgetChildKey);

	if (WidgetManager != nullptr && Widget != nullptr)
	{
		UE_LOG(ExtensionLog, Log, TEXT("[%s] RemoveWidget(): 从 %s 中移除 %s !"), *WorldContextObject->GetName(), *WidgetChildKey, *Widget->GetName());
		GetWidgetGroup(WorldContextObject, WidgetMainKey).WidgetChildMap.Remove(WidgetChildKey);
		GetWidgetGroup(WorldContextObject, WidgetMainKey).WidgetChildMap.Compact();
		GetWidgetGroup(WorldContextObject, WidgetMainKey).WidgetChildMap.Shrink();
	}
}
