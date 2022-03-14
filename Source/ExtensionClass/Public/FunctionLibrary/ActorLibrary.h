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
	* @param	GroupKey			添加到的 ActorGroup 的 Key
	* @param	ActorKey			添加到的 ActorGroup 中 Actor 的 Key
	* @param	Actor				添加的 Actor
	* @param	bSortByKeyAsInt		利用 ActorKey 进行升序排序, 必须保证键值能转换为 int 类型
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static void AddGroupActor(UObject* WorldContextObject, FString GroupKey, FString ActorKey, AActor* Actor, bool bSortByKeyAsInt);

	/**
	* 从 ActorManager.GroupActorMainMap 中获取一个Actor
	* 
	* @param	GroupKey	用于查找 ActorGroup 的 Key
	* @param	ActorKey	用于在 ActorGroup 中查找 Actor 的 Key
	* @return				查找到的 Actor
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static AActor* GetGroupActor(UObject* WorldContextObject, FString GroupKey, FString ActorKey);

	/**
	* 添加一组 Actor 到 ActorManager.GroupActorMainMap
	* 
	* @param	bObjectNameAsActorKey	使用 Actor 的 ObjectName() 作为 ActorKey
	* @param	GroupKey				添加到的 ActorGroup 的 Key
	* @param	ActorKeyArray			用于查找 Actor 的 Key
	* @param	ActorArray				添加的 Actor
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static void AddActorGroup(UObject* WorldContextObject, bool bObjectNameAsActorKey, FString GroupKey, TArray<FString> ActorKeyArray, TArray<AActor*> ActorArray);

	/**
	* 从 ActorManager.GroupActorMainMap 中获取一组 Actor 作为数组返回
	* 
	* @param	GroupKey		用于查找 ActorGroup 的 Key
	* @return					查找到的 ActorGroup
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static TArray<AActor*> GetActorGroup(UObject* WorldContextObject, FString GroupKey);

	/** 
	* 从 ActorManager.GroupActorMainMap 中获取一个 GroupActorChildMap
	* @param	GroupKey		用于查找 ActorGroup 的 Key
	* @return					查找到的 GroupActorChildMap
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static TMap<FString, AActor*> GetGroupActorChildMap(UObject* WorldContextObject, FString GroupKey);

	/**
	* 设置一组 ActorGroup 的可见性
	* 
	* @param	GroupKey		用于查找 ActorGroup 的 Key
	* @param	bNewHidden		新的可见性
	* @param	bCustomHidden	如果是 AExtActor 类或其子类则调用自定义方法
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static void SetActorGroupHidden(UObject* WorldContextObject, FString GroupKey, bool bNewHidden, bool bCustomHidden);

	/**
	* 设置一组 ActorGroup 中的某一个的可见性
	* 
	* @param	GroupKey		用于查找 ActorGroup 的 Key
	* @param	ActorKey		用于在 ActorGroup 中查找 Actor 的 Key
	* @param	bNewHidden		新的可见性
	* @param	bSetOtherHide	是否隐藏组内的其它 Actor
	* @param	bCustomHidden	如果是 AExtActor 类或其子类则调用自定义方法
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|ActorLibrary")
	static void SetGroupActorHidden(UObject* WorldContextObject, FString GroupKey, FString ActorKey, bool bNewHidden, bool bSetOtherHide, bool bCustomHidden);
};
