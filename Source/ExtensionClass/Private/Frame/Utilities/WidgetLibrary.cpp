// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Utilities/WidgetLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

#include "Frame/ExtGameInstance.h"
#include "Frame/Manager/WidgetManager.h"
#include "ExtensionClass/Public/Class/ExtUserWidget.h"

UWidgetManager* GetWidgetManager(UObject* WorldContextObject)
{
	UExtGameInstance* TempGameInstance = Cast<UExtGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));

	if (TempGameInstance != nullptr)
	{
		return TempGameInstance->WidgetManager;
	}

	return nullptr;
}

//void UWidgetLibrary::CreateWidget()
//{
//	
//}

UExtUserWidget* UWidgetLibrary::GetWidget(UObject* WorldContextObject, FString WidgetKey)
{
	UWidgetManager* WidgetManager = GetWidgetManager(WorldContextObject);

	if (WidgetManager != nullptr)
	{
		return WidgetManager->WidgetMap.FindRef(WidgetKey);
	}
	return nullptr;
}

UExtUserWidget* UWidgetLibrary::GetOneWidgetOfGroup(UObject* WorldContextObject, FString WidgetMainKey, FString WidgetChildKey)
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

	return FWidgetGroup();
}

TArray<UExtUserWidget*> UWidgetLibrary::GetWidgetArray(UObject* WorldContextObject, FString WidgetMainKey)
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

void UWidgetLibrary::RemoveWidget(UObject* WorldContextObject, FString WidgetKey)
{
	UWidgetManager* WidgetManager = GetWidgetManager(WorldContextObject);

	UExtUserWidget* Widget = GetWidget(WorldContextObject, WidgetKey);

	if (WidgetManager != nullptr && Widget != nullptr)
	{
		WidgetManager->WidgetMap.Remove(WidgetKey);
		Widget->RemoveFromParent();
	}
}

void UWidgetLibrary::RemoveOneOfGroupWidget(UObject* WorldContextObject, FString WidgetMainKey, FString WidgetChildKey)
{
	UWidgetManager* WidgetManager = GetWidgetManager(WorldContextObject);
	UExtUserWidget* Widget = GetOneWidgetOfGroup(WorldContextObject, WidgetMainKey, WidgetChildKey);

	if (WidgetManager != nullptr && Widget != nullptr)
	{
		GetWidgetGroup(WorldContextObject, WidgetMainKey).WidgetChildMap.Remove(WidgetChildKey);
		Widget->RemoveFromParent();
	}
}
