// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ExtensionFunction.generated.h"

/**
 * 
 */
UCLASS()
class EXTENSIONCLASS_API UExtensionFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/** String 数组转为 int 数组 */
	UFUNCTION(BlueprintPure, Category = "ExtensionClass|Utilities|ExtensionFunction")
	static TArray<int32> StringArrayToInt(TArray<FString> StringArray);
};
