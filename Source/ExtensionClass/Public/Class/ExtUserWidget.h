// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExtUserWidget.generated.h"

/**
 * 拓展自 UUserWidget
 */

UCLASS()
class EXTENSIONCLASS_API UExtUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** 用作查找的主键 */
	UPROPERTY(BlueprintReadOnly, Category = "ExtensionClass|ExtUserWidget")
	FString WidgetMainKey;

	/** 用作查找的次键 */
	UPROPERTY(BlueprintReadOnly, Category = "ExtensionClass|ExtUserWidget")
	FString WidgetChildKey;

public:

	/** 移除 Widget 并标记为 IsPendingKill */
	UFUNCTION(BlueprintCallable, Category = "ExtensionClass|ExtUserWidget")
	void RemoveAndMarkGC();
};
