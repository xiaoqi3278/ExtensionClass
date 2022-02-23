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

public:
	UFUNCTION(BlueprintImplementableEvent)
	void BeginPlay();
};
