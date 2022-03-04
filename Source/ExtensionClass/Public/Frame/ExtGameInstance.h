// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ExtGameInstance.generated.h"

/**
 * 
 */

class UWidgetManager;
class UModelManager;
class UModelTree;

UCLASS()
class EXTENSIONCLASS_API UExtGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/** 全局 WidgetManager */
	UPROPERTY()
	UWidgetManager* WidgetManager;

	/** 全局 ModelManager */
	UPROPERTY()
	UModelManager* ModelManager;

	/** 全局 Model 树 */
	//UPROPERTY()
	//UModelTree* ModelTree;

public:
	virtual void Init() override;
};
