// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Manager/CheckBoxManager.h"

#include "CheckBoxLibrary.generated.h"

/**
 * 
 */

class UCheckBoxManager;

UCLASS()
class EXTENSIONCLASS_API UCheckBoxLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** 测试 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static void TestFunction(UObject* WorldContextObject);

	/** 获取 CheckBox 管理类 */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static UCheckBoxManager* GetCheckBoxManager(UObject* WorldContextObject);

	/** 获取主键值对 */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static TMap<FString, FCheckBoxGroup> GetCheckBoxMainMap(UObject* WorldContextObject);

	/** 查找 MainKey 对应存储 ExtCheckBox 的键值对 */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static TMap<FString, UExtCheckBox*> GetCheckBoxChildMap(UObject* WorldContextObject, FString MainKey);

	/** 查找对应的一组 ExtCheckBox 并返回 ExtCheckBox 数组 */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static TArray<UExtCheckBox*> GetCheckBoxArray(UObject* WorldContextObject, FString MainKey);

	/** 查找对应的 ExtCheckBox，若不存在则返回空指针 */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static UExtCheckBox* GetCheckBox(UObject* WorldContextObject, FString MainKey, FString ChildKey);

	/**
	 * 检查是否存在 MainKey 或 ChildKey 如不存在则输出到日志
	 * 
	 * @param WorldContextObject 世界上下文
	 * @param Manager 需要进行判断的 UCheckBoxManager 类
	 * @param MainKey 判断此主键是否在传入的 Manager 中存在
	 * @param ChildKey 此子键是否在传入的 Manager.MainKey 中存在
	 * @param Index 传入的参数从 Manager 到 ChildKey 需要判断的个数
	 * @param FunctionNamae 本次调用 CheckAndOutLog 的函数名称
	 * 
	 * @return 如不包含其中的 MainKey 或 ChildKey 则返回 true
	 */
	UFUNCTION()
	static bool CheckAndOutLog(UObject* WorldContextObject, UCheckBoxManager* Manager, FString MainKey, FString ChildKey, int32 Index, FString FunctionName);

	/**
	 * 将一个 ExtCheckBox 添加到组中
	 * 
	 * @param WorldContextObject 世界上下文
	 * @param MainKey 将要添加到的组对应的键，若不存在则创建对应的组
	 * @param ChildKey ExtCheckBox 对应的键，若已存在则会覆盖原来的 ExtCheckBox
	 * @param InCheckBox 将要添加的 ExtCheckBox
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static void AddCheckBox(UObject* WorldContextObject,  FString MainKey, FString ChildKey, UExtCheckBox* InCheckBox);

	/** 查找某个 ExtCheckBox 在组中对应的下标，若不存在对应的 ExtCheckBox 则返回-1，若查找失败则返回-2 */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static int32 GetCheckBoxIndex(UObject* WorldContextObject, FString MainKey, FString ChildKey);

	/** 查找对应的一组 ExtCheckBox 并返回状态为已选中的 ExtCheckBox */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static UExtCheckBox* GetCheckedOne(UObject* WorldContextObject, FString MainKey);

	/** 查找所有的主键 MainKey 并作为数组返回 */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static TArray<FString> GetMainKeyArray(UObject* WorldContextObject);

	/** 查找对应的一组 ExtCheckBox 并把所有的 ChildKey 作为数组返回 */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static TArray<FString> GetChildKeyArray(UObject* WorldContextObject, FString MainKey);

	/** 查找对应的一组 ExtCheckBox 中已选中的 ChildKey */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static FString GetCheckedChildKey(UObject* WorldContextObject, FString MainKey);

	/** 设置某个 ExtCheckBox 的状态为选中，如果绑定了 OnExtCheckStateChanged 事件则会同时调用 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static void SetOneExtChecked(UObject* WorldContextObject, FString MainKey, FString ChildKey);

	/** 设置某个 ExtCheckBox 的状态，如果绑定了 OnExtCheckStateChanged 事件则会同时调用*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|CheckBoxLibrary")
	static void SetOneExtCheckedState(UObject* WorldContextObject, FString MainKey, FString ChildKey, ECheckBoxState State);
};
