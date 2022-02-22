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

private:
	/** CheckBox 管理类 */
	UPROPERTY()
	ACheckBoxManager* CheckBoxManager;

public:
	UFUNCTION(Exec)
	void ShowExtCheckBoxMainKeyInLog();
};
