// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ExtGameInstance.generated.h"

/**
 * 
 */

class UWidgetManager;
class UModelManager;
class UCommandManager;

class UModelTree;

UCLASS()
class EXTENSIONCLASS_API UExtGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/** 全局 WidgetManager */
	UPROPERTY(BlueprintReadOnly)
	UWidgetManager* WidgetManager;

	/** 全局 ModelManager */
	UPROPERTY(BlueprintReadOnly)
	UModelManager* ModelManager;

	/** 全局 CommandManger */
	UPROPERTY(BlueprintReadOnly)
	UCommandManager* CommandManager;

	/** 默认创建的 ModelManager 类型 */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UModelManager> ModelManagerClass;

public:
	virtual void Init() override;

protected:
	virtual void OnStart() override;
};
