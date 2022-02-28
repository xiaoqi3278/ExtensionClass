// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetManager.generated.h"

/**
 * 拓展自 UObject
 * Widget管理器
 */

class UExtUserWidget;

USTRUCT(BlueprintType)
struct FWidgetGroup
{
	GENERATED_BODY()

	//存储某一类相关的 Widget
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, UExtUserWidget*> WidgetChildMap;
};

UCLASS()
class EXTENSIONCLASS_API UWidgetManager : public UObject
{
	GENERATED_BODY()
	
public:

	/** 存储Widget, 每个键对应一个 Widget */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, UExtUserWidget*> WidgetMap;

	/** 存储WidgetGroup, 每个键对应一个 FWidgetGroup */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FWidgetGroup> WidgetMainMap;

	UFUNCTION()
	void Test();
};
