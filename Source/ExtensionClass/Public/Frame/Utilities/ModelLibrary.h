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

	UFUNCTION()
	static bool CheckModelManagerAndOutLog(UObject* WorldContextObject, UModelManager* Manager, FString FunctionName);

	/**
	 * 创建一个主 Model 对象
	 * 
	 * @param ModelClass		创建的 Model 对象类型
	 * @return					对象引用
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "ModelClass"), Category = "ExtensionClass|Frame|ModelLibrary")
	static UBaseModel* CreateMainModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ModelClass);

	/**
	 * 创建一个子 Model 对象
	 * 
	 * @param OwnerModelClass	拥有此 Model 对象的主 Model 类型
	 * @param ModelClass		创建的 Model 对象类型
	 * @return					对象引用
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "ModelClass"), Category = "ExtensionClass|Frame|ModelLibrary")
	static UBaseModel* CreateChildModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> OwnerModelClass, TSubclassOf<UBaseModel> ModelClass);

	/**
	 * 销毁一个 Model 对象
	 * 
	 * @param ModelClass		需要销毁的对象类型
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|ModelLibrary")
	static void DestroyMainModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ModelClass);
};
