// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ModelLibrary.generated.h"

/**
 * 
 */

class UModelManager;
class UBaseModel;

UCLASS()
class EXTENSIONCLASS_API UModelLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**
	 * 获取 ModelManager
	 */
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|ModelLibrary")
	static UModelManager* GetModelManager(UObject* WorldContextObject);

	/**
	* 检查 ModelManager 是否有效，无效则返回 false 并输出到日志
	* 
	* @param WorldContextObject	调用此函数的对象
	* @param Manager			进行判断的 ModelManager 对象
	* @param FunctoinName		调用此函数的函数名称，用于输出到日志
	* @return					有效返回 true, 无效返回 false
	*/
	UFUNCTION()
	static bool CheckModelManagerAndOutLog(UObject* WorldContextObject, UModelManager* Manager, FString FunctionName);

	/**
	 * 创建一个 Model
	 * 
	 * @param ModelClass		创建的 Model 对象类型
	 * @return					对象引用
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "ModelClass"), Category = "ExtensionClass|Frame|ModelLibrary")
	static UBaseModel* CreateModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ParentModelClass, TSubclassOf<UBaseModel> ModelClass);

	/**
	 * 销毁一个 Model
	 * 
	 * @param ModelClass		需要销毁的对象类型
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|ModelLibrary")
	static void DestroyModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ModelClass);

	/** 
	* 搜索对应的 Model
	* 
	* @param ModelClass			查找的 Model 类型
	* @return					查找到的 Model，若无则返回空
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|ModelLibrary")
	static UBaseModel* SearchModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ModelClass);

	/**
	* 搜索对应的一级子 Model
	* 
	* @param ModelClass			父 Model 类型
	* @return					搜索到的所有一级子 Model
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|ModelLibrary")
	static TArray<UBaseModel*> SearchChildFirstLevelModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ModelClass);

	/**
	* 搜索对应的所有子 Model
	* 
	* @param ModelClass			父 Model 类型
	* @return					搜索到的所有子 Model
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|ModelLibrary")
	static TArray<UBaseModel*> SearchAllChildModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ModelClass);

	/**
	* 获取所有的 Model
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|ModelLibrary")
	static TArray<UBaseModel*> GetAllModel(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	static void ModelTest(TSubclassOf<UBaseModel> Class1,  TSubclassOf<UBaseModel> Class2);
};
