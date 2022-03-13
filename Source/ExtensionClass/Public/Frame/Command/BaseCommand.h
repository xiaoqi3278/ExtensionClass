// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class/ExtObject.h"
#include "BaseCommand.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class EXTENSIONCLASS_API UBaseCommand : public UExtObject
{
	GENERATED_BODY()

public:

	/** 命令行为是创建还是销毁 */
	UPROPERTY(BlueprintReadWrite)
	bool bIsCreate = true;
	
};
