// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CheckBoxLibrary.generated.h"

/**
 * 
 */

class ACheckBoxManager;

UCLASS()
class EXTENSIONCLASS_API UCheckBoxLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** 获取 CheckBox 管理类 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static ACheckBoxManager* GetCheckBoxManager(UObject* WorldContextObject);

	/**
	 * 将一个 ExtCheckBox 添加到组中
	 * 
	 * @param WorldContextObject 世界上下文
	 * @param MainKey 将要添加到的组对应的键，若不存在则创建对应的组
	 * @param ChildKey ExtCheckBox 对应的键，若已存在则会覆盖原来的 ExtCheckBox
	 * @param InCheckBox 将要添加的 ExtCheckBox
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static void AddCheckBox(UObject* WorldContextObject, FString MainKey, FString ChildKey, UExtCheckBox* InCheckBox);

	/** 查找对应的 ExtCheckBox，若不存在则返回空指针 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static UExtCheckBox* GetCheckBox(UObject* WorldContextObject, FString MainKey, FString ChildKey);

	/** 查找对应的一组 ExtCheckBox 并返回 ExtCheckBox 数组 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static TArray<UExtCheckBox*> GetCheckBoxArray(UObject* WorldContextObject, FString MainKey);

	/** 查找某个 ExtCheckBox 在组中对应的下标，若不存在对应的 ExtCheckBox 则返回-1，若查找失败则返回-2 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static int32 GetCheckBoxIndex(UObject* WorldContextObject, FString MainKey, FString ChildKey);

	/** 查找 MainKey 对应存储 ExtCheckBox 的键值对 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static TMap<FString, UExtCheckBox*> GetChildMap(UObject* WorldContextObject, FString MainKey);

	/** 查找对应的一组 ExtCheckBox 并返回状态为已选中的 ExtCheckBox */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static UExtCheckBox* GetCheckedOne(UObject* WorldContextObject, FString MainKey);

	/** 查找所有的主键 MainKey 并作为数组返回 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static TArray<FString> GetMainKeyArray(UObject* WorldContextObject);

	/** 设置某个 ExtCheckBox 的状态，如果绑定了 OnExtCheckStateChanged 事件则会同时调用 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static void SetExtCheckedState(UObject* WorldContextObject, FString MainKey, FString ChildKey);
};
