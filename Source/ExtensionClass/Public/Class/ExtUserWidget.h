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
	
protected:
	virtual void NativeOnInitialized() override;

public:
	/** 用作查找的主键 */
	UPROPERTY(BlueprintReadOnly, Category = "ExtensionClass|ExtUserWidget")
	FString WidgetMainKey;

	/** 用作查找的次键 */
	UPROPERTY(BlueprintReadOnly, Category = "ExtensionClass|ExtUserWidget")
	FString WidgetChildKey;
};
