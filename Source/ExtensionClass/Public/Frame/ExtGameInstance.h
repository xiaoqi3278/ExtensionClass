// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ExtGameInstance.generated.h"

/**
 * 
 */

class UWidgetManager;

UCLASS()
class EXTENSIONCLASS_API UExtGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/** È«¾Ö WidgetManager */
	UPROPERTY()
	UWidgetManager* WidgetManager;

public:
	virtual void Init() override;
};
