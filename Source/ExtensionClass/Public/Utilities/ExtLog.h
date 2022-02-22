// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExtLog.generated.h"

/**
 * 自定义日志类别
 * 
 */

DECLARE_LOG_CATEGORY_EXTERN(ExtensionLog, Log, All);

UCLASS()
class EXTENSIONCLASS_API UExtLog : public UObject
{
	GENERATED_BODY()
	
};
