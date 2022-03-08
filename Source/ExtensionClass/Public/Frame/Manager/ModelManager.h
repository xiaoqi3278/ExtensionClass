// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class/ExtObject.h"
#include "ModelManager.generated.h"

/**
 * Model管理器 
 */

class UBaseModel;
class UModelTree;
class UBaseCommand;

UCLASS()
class EXTENSIONCLASS_API UModelManager : public UExtObject
{
	GENERATED_BODY()
	
public:

	virtual void OnBegin() override;

	/** 全局 Model 树 */
	UPROPERTY(BlueprintReadOnly)
	UModelTree* ModelTree;

public:

	/** 蓝图重写, ModelManager 开始事件 */
	UFUNCTION(BlueprintImplementableEvent)
	void ModelManagerBegin();

	void NotifyAllModelToProcesssingCommand(UBaseCommand* Command);
};
