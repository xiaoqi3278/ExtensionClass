// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/ActorLibrary.h"

#include "Kismet/GameplayStatics.h"

#include "Utilities/ExtLog.h"
#include "Manager/ActorManager.h"
#include "Frame/ExtGameInstance.h"

UActorManager* UActorLibrary::GetActorManager(UObject* WorldContextObject)
{
	UExtGameInstance* GameInstance = Cast<UExtGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (GameInstance == nullptr)
	{
		return nullptr;
	}

	return GameInstance->ActorManager;
}

bool UActorLibrary::CheckAndOutLog(UObject* WorldContextObject, UActorManager* ActorManager, FString FunctionName)
{
	if (ActorManager == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] %s(): ActorManager Get Faild!"), *WorldContextObject->GetName(), *FunctionName);
		return true;
	}

	return false;
}

void UActorLibrary::AddSingleActor(UObject* WorldContextObject, FString ActorKey, AActor* Actor)
{
	UActorManager* ActorManager = GetActorManager(WorldContextObject);
	
	if (CheckAndOutLog(WorldContextObject, ActorManager, "AddSingleActor"))
	{
		return;
	}

	ActorManager->SingleActorMap.Emplace(ActorKey, Actor);
}

AActor* UActorLibrary::GetSingleActor(UObject* WorldContextObject, FString ActorKey)
{
	UActorManager* ActorManager = GetActorManager(WorldContextObject);

	if (CheckAndOutLog(WorldContextObject, ActorManager, "AddSingleActor"))
	{
		return nullptr;
	}

	//若不存在则返回 nullptr
	return ActorManager->SingleActorMap.FindRef(ActorKey);
}

void UActorLibrary::AddGroupActor(UObject* WorldContextObject, FString MainKey, FString ChildKey, AActor* Actor)
{
	UActorManager* ActorManager = GetActorManager(WorldContextObject);

	if (CheckAndOutLog(WorldContextObject, ActorManager, "AddSingleActor"))
	{
		return;
	}

	ActorManager->GroupActorMainMap.FindOrAdd(MainKey).GroupActorChildMap.Emplace(ChildKey, Actor);
}

AActor* UActorLibrary::GetGroupActor(UObject* WorldContextObject, FString MainKey, FString ChildKey)
{
	UActorManager* ActorManager = GetActorManager(WorldContextObject);

	if (CheckAndOutLog(WorldContextObject, ActorManager, "AddSingleActor"))
	{
		return nullptr;
	}

	FActorGroup TempActorGroup = ActorManager->GroupActorMainMap.FindRef(MainKey);
	return TempActorGroup.GroupActorChildMap.FindRef(ChildKey);
}
