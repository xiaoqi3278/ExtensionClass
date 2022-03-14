// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/ActorLibrary.h"

#include "Kismet/GameplayStatics.h"

#include "Utilities/ExtLog.h"
#include "Manager/ActorManager.h"
#include "Frame/ExtGameInstance.h"
#include "Class/ExtActor.h"

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

	if (CheckAndOutLog(WorldContextObject, ActorManager, "GetSingleActor"))
	{
		return nullptr;
	}

	//若不存在则返回 nullptr
	return ActorManager->SingleActorMap.FindRef(ActorKey);
}

void UActorLibrary::AddGroupActor(UObject* WorldContextObject, FString GroupKey, FString ActorKey, AActor* Actor, bool bSortByKeyAsInt)
{
	UActorManager* ActorManager = GetActorManager(WorldContextObject);

	if (CheckAndOutLog(WorldContextObject, ActorManager, "AddGroupActor"))
	{
		return;
	}

	ActorManager->GroupActorMainMap.FindOrAdd(GroupKey).GroupActorChildMap.Emplace(ActorKey, Actor);

	//升序排列
	if (bSortByKeyAsInt)
	{
		ActorManager->GroupActorMainMap.Find(GroupKey)->GroupActorChildMap.KeySort([](FString A, FString B) {
			return FCString::Atoi(*A) < FCString::Atoi(*B);
		});
	}
}

AActor* UActorLibrary::GetGroupActor(UObject* WorldContextObject, FString GroupKey, FString ActorKey)
{
	UActorManager* ActorManager = GetActorManager(WorldContextObject);

	if (CheckAndOutLog(WorldContextObject, ActorManager, "GetGroupActor"))
	{
		return nullptr;
	}

	FActorGroup TempActorGroup = ActorManager->GroupActorMainMap.FindRef(GroupKey);
	return TempActorGroup.GroupActorChildMap.FindRef(ActorKey);
}

void UActorLibrary::AddActorGroup(UObject* WorldContextObject, bool bObjectNameAsActorKey, FString GroupKey, TArray<FString> ActorKeyArray, TArray<AActor*> ActorArray)
{
	UActorManager* ActorManager = GetActorManager(WorldContextObject);

	if (CheckAndOutLog(WorldContextObject, ActorManager, "AddActorGroup"))
	{
		return;
	}

	FActorGroup* TempActorGroup = &(ActorManager->GroupActorMainMap.FindOrAdd(GroupKey));

	for (int32 i = 0; i < ActorArray.Num(); i++)
	{
		//如果为空，则默认使用 GetName() 作为 ActorKey
		if (ActorKeyArray[i] == "")
		{
			ActorKeyArray[i] = ActorArray[i]->GetName();
		}
		TempActorGroup->GroupActorChildMap.Emplace(bObjectNameAsActorKey ? ActorArray[i]->GetName() : ActorKeyArray[i], ActorArray[i]);
	}
}

TArray<AActor*> UActorLibrary::GetActorGroup(UObject* WorldContextObject, FString GroupKey)
{
	UActorManager* ActorManager = GetActorManager(WorldContextObject);

	if (CheckAndOutLog(WorldContextObject, ActorManager, "GetActorGroup") || !ActorManager->GroupActorMainMap.Contains(GroupKey))
	{
		return TArray<AActor*>();
	}

	if (!ActorManager->GroupActorMainMap.Contains(GroupKey))
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] GetActorGroup(): ActorManager->GroupActorMainMap 不存在组: %s"), *WorldContextObject->GetName(), *GroupKey);
		return TArray<AActor*>();
	}

	TMap<FString, AActor*> TempGroupMap = ActorManager->GroupActorMainMap.Find(GroupKey)->GroupActorChildMap;

	TArray<AActor*> ActorArray = TArray<AActor*>();
	TempGroupMap.GenerateValueArray(ActorArray);

	return ActorArray;
}

TMap<FString, AActor*> UActorLibrary::GetGroupActorChildMap(UObject* WorldContextObject, FString GroupKey)
{
	UActorManager* ActorManager = GetActorManager(WorldContextObject);

	if (CheckAndOutLog(WorldContextObject, ActorManager, "GetActorGroup") || !ActorManager->GroupActorMainMap.Contains(GroupKey))
	{
		return TMap<FString, AActor*>();
	}

	if (!ActorManager->GroupActorMainMap.Contains(GroupKey))
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] GetGroupActorChildMap(): ActorManager->GroupActorMainMap 中不包含 %s"), *WorldContextObject->GetName(), *GroupKey);
		return TMap<FString, AActor*>();
	}

	return ActorManager->GroupActorMainMap.Find(GroupKey)->GroupActorChildMap;
}

void UActorLibrary::SetActorGroupHidden(UObject* WorldContextObject, FString GroupKey, bool bNewHidden, bool bCustomHidden)
{
	for (auto& Itr : GetActorGroup(WorldContextObject, GroupKey))
	{
		AExtActor* TempExtActor = Cast<AExtActor>(Itr);
		if (bCustomHidden && TempExtActor != nullptr)    //如果是 AExtActor 类或其子类则调用自定义方法
		{
			TempExtActor->SetExtActorHiddenInGame(bNewHidden);
		}
		else
		{
			Itr->SetActorHiddenInGame(bNewHidden);
		}
	}
}

void UActorLibrary::SetGroupActorHidden(UObject* WorldContextObject, FString GroupKey, FString ActorKey, bool bNewHidden, bool bSetOtherHide, bool bCustomHidden)
{
	UActorManager* ActorManager = GetActorManager(WorldContextObject);

	if (CheckAndOutLog(WorldContextObject, ActorManager, "GetActorGroup") || !ActorManager->GroupActorMainMap.Contains(GroupKey))
	{
		return;
	}

	TMap<FString, AActor*> ActorGroupMap = ActorManager->GroupActorMainMap.Find(GroupKey)->GroupActorChildMap;

	for (auto& Itr : ActorGroupMap)
	{
		AExtActor* TempActor = Cast<AExtActor>(Itr.Value);

		if (Itr.Key == ActorKey)
		{
			if (bCustomHidden && TempActor != nullptr)    //如果是 AExtActor 类或其子类则调用自定义方法
			{
				TempActor->SetExtActorHiddenInGame(bNewHidden);
			}
			else
			{
				Itr.Value->SetActorHiddenInGame(bNewHidden);
			}
		}
		else
		{
			if (bSetOtherHide)		//将组内其它 Actor 隐藏
			{
				if (bCustomHidden && TempActor != nullptr)    //如果是 AExtActor 类或其子类则调用自定义方法
				{
					TempActor->SetExtActorHiddenInGame(true);
				}
				else
				{
					Itr.Value->SetActorHiddenInGame(true);
				}
			}
		}
	}
}
