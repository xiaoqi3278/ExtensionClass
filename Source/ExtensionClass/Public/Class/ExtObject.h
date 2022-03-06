// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExtObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class EXTENSIONCLASS_API UExtObject : public UObject
{
	GENERATED_BODY()

	/** 在大部分变量都初始化结束后调用 */
	virtual void PostInitProperties() override;

public:
	virtual UWorld* GetWorld() const override;

protected:
	/** 类初始化时调用 */
	virtual void OnBegin();
	/** 使用 DestroyObject() 回收当前对象时调用 */
	virtual void OnEnd();

public:
	/** 蓝图重写，类初始化时调用 */
	UFUNCTION(BlueprintImplementableEvent)
	void BeginPlay();

	/** 蓝图重写，使用 DestroyObject() 回收当前对象时调用 */
	UFUNCTION(BlueprintImplementableEvent)
	void EndPlay();

	UFUNCTION(BlueprintCallable)
	void DestroyObject();
};
