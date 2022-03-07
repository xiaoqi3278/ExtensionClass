// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExtObject.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExtObjectDestroyed, int32, Index);

UCLASS(Blueprintable)
class EXTENSIONCLASS_API UExtObject : public UObject
{
	GENERATED_BODY()

public:
	/** Object 标识 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExtensinClass|ExtObject|Properties")
	int32 Index;

	/** 当使用 DestroyObject() 回收对象时调用 */
	UPROPERTY(BlueprintAssignable, Category = "ExtensoinClass|ExtObject|Event")
	FOnExtObjectDestroyed OnExtObjectDestroyed;

protected:
	/** 类初始化时调用 */
	virtual void OnBegin();
	/** 使用 DestroyObject() 回收当前对象时调用 */
	virtual void OnEnd();

public:
	virtual UWorld* GetWorld() const override;

	/** 在大部分变量都初始化结束后调用 */
	virtual void PostInitProperties() override;

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
