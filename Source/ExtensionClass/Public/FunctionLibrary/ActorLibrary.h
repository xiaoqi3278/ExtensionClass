// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActorLibrary.generated.h"

/**
 * 
 */

class UActorManager;
class Actor;

UCLASS()
class EXTENSIONCLASS_API UActorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/** 获取 ActorManager 管理类 */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static UActorManager* GetActorManager(UObject* WorldContextObject);

	/** 检查 ActorManager 是否有效 */
	UFUNCTION()
	static bool CheckAndOutLog(UObject* WorldContextObject, UActorManager* ActorManager, FString FunctionName);

	/** 
	* 添加一个 Actor 到 ActorManager.SingleActorMap
	* 
	* @param	ActorKey	添加的 Actor 的 Key
	* @param	Actor		添加的 Actor
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static void AddSingleActor(UObject* WorldContextObject, FString ActorKey, AActor* Actor);

	/**
	* 从 ActorManager.SingleActorMap 中获取一个 Actor 
	* 
	* @param	ActorKey	用于查找 Actor 的 Key
	* @return				查找到的 Actor
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static AActor* GetSingleActor(UObject* WorldContextObject, FString ActorKey);

	/**
	* 添加一个 Actor 到 ActorManager.GroupActorMainMap
	* 
	* @param	MainKey		添加到的 ActorGroup 的 Key
	* @param	ChildKey	添加到的 ActorGroup 中 Actor 的 Key
	* @param	Actor		添加的 Actor
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static void AddGroupActor(UObject* WorldContextObject, FString MainKey, FString ChildKey, AActor* Actor);

	/**
	* 从 ActorManager.GroupActorMainMap 中获取一个Actor
	* 
	* @param	MainKey		用于查找 ActorGroup 的 Key
	* @param	ChildKey	用于在 ActorGroup 中查找 Actor 的 Key
	* @return				查找到的 Actor
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static AActor* GetGroupActor(UObject* WorldContextObject, FString MainKey, FString ChildKey);

	/**
	* 添加一组 Actor 到 ActorManager.GroupActorMainMap
	* 
	* @param	bObjectNameAsChildKey	使用 Actor 的 ObjectName() 作为 ChildKey
	* @param	MainKey					添加到的 ActorGroup 的 Key
	* @param	ChildKeyArray			用于查找 Actor 的 Key
	* @param	ActorArray				添加的 Actor
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static void AddActorGroup(UObject* WorldContextObject, bool bObjectNameAsChildKey, FString MainKey, TArray<FString> ChildKeyArray, TArray<AActor*> ActorArray);

	/**
	* 从 ActorManager.GroupActorMainMap 中获取一组 Actor 作为数组返回
	* 
	* @param	MainKey		用于查找 ActorGroup 的 Key
	* @return				查找到的 ActorGroup
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static TArray<AActor*> GetActorGroup(UObject* WorldContextObject, FString MainKey);
};
