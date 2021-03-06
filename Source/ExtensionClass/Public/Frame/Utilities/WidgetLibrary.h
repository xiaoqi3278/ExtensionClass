// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Frame/Manager/WidgetManager.h"

#include "WidgetLibrary.generated.h"

/**
 * Widget 工具类
 * 
 * 提供 Widget 相关函数
 */

class UWidgetManager;
class UExtUserWidget;

UCLASS()
class EXTENSIONCLASS_API UWidgetLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** 获取 WidgetManager */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static UWidgetManager* GetWidgetManager(UObject* WorldContextObject);

	/** 创建 Widget */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "WidgetClass"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static UExtUserWidget* CreateExtWidget(UObject* WorldContextObject, TSubclassOf<UExtUserWidget> WidgetClass);

	/**
	 * 将一个 ExtUserWidget 对象加入 WidgetManager 中的 WidgetMap 中
	 * 
	 * @param WidgetKey			键
	 * @param Widget			加入管理的 ExtUserWidget对象
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static void AddToWidgetManager(UObject* WorldContextObject, FString WidgetKey, UExtUserWidget* Widget);

	/**
	 * 将一个 ExtUserWidget 对象加入 WidgetManager 中的 WidgetGroup 中
	 * 
	 * @param WidgetMainKey		用作查找 WidgetGroup 的主键
	 * @param WidgetChildKey	用作查找 ExtUserWIdget 的次键
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static void AddToWidgetManagerOfGroup(UObject* WorldContextObject, FString WidgetMainKey, FString WidgetChildKey, UExtUserWidget* Widget);

	/**
	* 查找 WidgetManager 中 WidgetMap 对应的一个 UExtUserWidget
	* 
	* @param WidgetKey			用作查找的键
	* 
	* @return	查找到的 ExtUserWidget，可为 nullptr
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "WidgetClass"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static UExtUserWidget* GetWidget(UObject* WorldContextObject, FString WidgetKey, TSubclassOf<UExtUserWidget> WidgetClass);

	/**
	* 查找 WidgetManager 中 某个 WidgetGroup 对应的一个 ExtUserWidget
	*
	* @param WidgetMainKey		用作查找 WidgetGroup 的键
	* @param WidgetChildKey		用作查找 WidgetGroup 中对应的一个 ExtUserWidget 的键
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static UExtUserWidget* GetWidgetOfGroup(UObject* WorldContextObject, FString WidgetMainKey, FString WidgetChildKey);

	/**
	* 查找 WidgetManager 中对应的 FWidgetGroup
	* 
	* @param WidgetMainKey		用作查找的键
	* 
	* @return	查找到的 WidgetGroup，可为默认构造的对象
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static FWidgetGroup GetWidgetGroup(UObject* WorldContextObject, FString WidgetMainKey);

	/**
	* 查找 WidgetManager 中对应的 一个 WidgetGroup中所有的 ExtUserWidget
	* 
	* @param WidgetMainKey		用作查找的键
	* 
	* @return	查找到的 ExtUserWidget 数组，可为空
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static TArray<UExtUserWidget*> GetWidgetArrayOfGroup(UObject* WorldContextObject, FString WidgetMainKey);

	/**
	* 获取所有已被管理的 ExtUserWidget
	* 
	* @return	查找到的 ExtUserWidget 数组，可为空
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Fram|WidgetLibrary")
	static TArray<UExtUserWidget*> GetAllWidget(UObject* WorldContextObject);

	/** 
	* 获取所有已被管理的 ExtUserWidget 的 Key
	* 
	* @return	查找到的 ExtUserWidget Key
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static TArray<FString> GetAllWidgetKey(UObject* WorldContextObject);

	/** 
	* 移除 WidgetManager 中 WidgetMap 对应的某一个 ExtUserWidget
	* 
	* @param WidgetKey			用作查找的键
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static void RemoveWidget(UObject* WorldContextObject, FString WidgetKey);

	/**
	* 移除 WidgetManager 中 WidgetMainMap 中对应的 WidgetGroup 中的某一个 ExtUserWidget
	* 
	* @param WidgetMainKey		用作查找 WidgetGroup 的键
	* @param WidgetChildKey		用作查找 WidgetGroup 中对应的一个 ExtUserWidget 的键
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static void RemoveOneOfGroupWidget(UObject* WorldContextObject, FString WidgetMainKey, FString WidgetChildKey);
};
