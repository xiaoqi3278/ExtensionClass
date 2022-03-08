// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class/ExtObject.h"
#include "BaseModel.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnModelDestroyed, TSubclassOf<UBaseModel>, ModelClass);

UCLASS()
class EXTENSIONCLASS_API UBaseModel : public UExtObject
{
	GENERATED_BODY()

public:

	/** 模块结束时调用 */
	UPROPERTY(BlueprintAssignable)
	FOnModelDestroyed OnModelDestroyed;

protected:
	virtual void OnBegin() override;

	virtual void OnEnd() override;

public:

	/** 蓝图重写, 模块开始事件 */
	UFUNCTION(BlueprintImplementableEvent)
	void ModelBegin();
};
