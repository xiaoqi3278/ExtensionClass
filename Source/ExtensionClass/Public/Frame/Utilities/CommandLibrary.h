// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommandLibrary.generated.h"

/**
 * Command 函数库
 */

class UBaseCommand;
class UCommandManager;

UCLASS()
class EXTENSIONCLASS_API UCommandLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/** 
	* 获取 CommandManager
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|CommandLibrary")
	static UCommandManager* GetCommandManager(UObject* WorldContextObject);

	/** 
	* 检查 CommandManager 是否有效，无效则返回 false 并输出到日志
	* 
	* @param	WorldContextObject	调用此函数的对象
	* @param	Manager				进行判断的 CommandManager 对象
	* @param	FunctoinName		调用此函数的函数名称，用于输出到日志
	* @return						有效返回 true, 无效返回 false
	*/
	UFUNCTION()
	static bool CheckCommandManagerAndOutLog(UObject* WorldContextObject, UCommandManager* Manager, FString FunctionName);

	/**
	* 创建一个命令
	* 
	* @param	CommandClass	命令类型
	* @return					创建的命令
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "CommandClass"), Category = "ExtensionClass|Frame|CommandLibrary")
	static UBaseCommand* CreateCommand(UObject* WorldContextObject, TSubclassOf<UBaseCommand> CommandClass);

	/**
	* 将一个命令加入命令队列, 并通知所有模块对命令进行处理
	* 
	* @param	Command			要入队的命令
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|CommandLibrary")
	static void EnqueueCommand(UObject* WorldContextObject, UBaseCommand* Command);
};
