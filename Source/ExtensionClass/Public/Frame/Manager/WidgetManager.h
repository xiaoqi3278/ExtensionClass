// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetManager.generated.h"

/**
 * ��չ�� UObject
 * Widget������
 */

class UExtUserWidget;

USTRUCT(BlueprintType)
struct FWidgetGroup
{
	GENERATED_BODY()

	//�洢ĳһ����ص� Widget
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, UExtUserWidget*> WidgetChildMap;
};

UCLASS()
class EXTENSIONCLASS_API UWidgetManager : public UObject
{
	GENERATED_BODY()
	
public:

	/** ÿ������Ӧһ�� Widget */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, UExtUserWidget*> WidgetMap;

	/** ÿ������Ӧһ�� FWidgetGroup */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FWidgetGroup> WidgetMainMap;

	UFUNCTION()
	void Test();
};
