// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "ExtCheatManager.generated.h"

/**
 * 包含自定义命令行函数
 * 
 */

class ACheckBoxManager;

UCLASS( Within = ExtPlayerController )
class EXTENSIONCLASS_API UExtCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:
	virtual void InitCheatManager() override;

public:
	/** 输出所有 ExtCheckBox 组的主键到日志中 */
	UFUNCTION(Exec)
	void ShowMainKey();

	/** 输出对应 ExtCheckBox 组的所有 ChileKey 到日志中 */
	UFUNCTION(Exec)
	void ShowChildKey(FString MainKey);

	/** 输出所有的 Model 名称到日志中 */
	UFUNCTION(Exec)
	void ShowAllModelName();

	/** 输出所有的 Model	数量到日志中 */
	UFUNCTION(Exec)
	void ShowAllModelNum();

	UFUNCTION(Exec)
	void ShowTest();
};
