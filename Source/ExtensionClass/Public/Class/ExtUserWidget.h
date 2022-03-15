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

	virtual void NativeConstruct() override;

public:

	/** 是否存储在 WidgetManager 中 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtUserWidget")
	bool bSaveToWidgetManager;

	/** 是否作为单个 Widget 存储在 WidgetManager->WidgetMap 中 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtUserWidget|SingleWidget")
	bool bSingleWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionCLass|ExtUserWidget|SingleWidget")
	FString WidgetKey;

	/** 用作查找的主键 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtUserWidget|GroupWidget")
	FString WidgetMainKey;

	/** 用作查找的次键 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtUserWidget|GroupWidget")
	FString WidgetChildKey;

public:

	/** 移除 Widget 并标记为 IsPendingKill */
	UFUNCTION(BlueprintCallable, Category = "ExtensionClass|ExtUserWidget")
	void RemoveAndMarkGC();
};
