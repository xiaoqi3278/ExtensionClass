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
		GetWidgetGroup(WorldContextObject, WidgetMainKey).WidgetChildMap.Emplace(WidgetChildKey, Widget);
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

	//WidgetManager 中不存在 WidgetMainKey
	UE_LOG(ExtensionLog, Warning, TEXT("[%s] GetWidgetGroup(): WidgetManager=>WidgetMainMap Does not Contain %s"), *WorldContextObject->GetName(), *WidgetMainKey);
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

	UExtUserWidget* Widget = GetWidget(WorldContextObject, WidgetKey, WidgetManager->GetClass());

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
