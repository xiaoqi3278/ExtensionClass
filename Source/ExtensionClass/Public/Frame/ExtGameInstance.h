// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ExtGameInstance.generated.h"

/**
 * 
 */

class UWidgetManager;
class UCheckBoxManager;
class UActorManager;
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

	/** 全局 CheckBoxManager */
	UPROPERTY(BlueprintReadOnly)
	UCheckBoxManager* CheckBoxManager;

	/** 全局 UActorManager */
	UPROPERTY(BlueprintReadOnly)
	UActorManager* ActorManager;

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

	/** 模块开始 */
	UFUNCTION(BlueprintCallable, Category = "ExtensionClass|Frame|ExtGameInstance")
	void CallModelManagerBegin();

protected:
	virtual void OnStart() override;
};
