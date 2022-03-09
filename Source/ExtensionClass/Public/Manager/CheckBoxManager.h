// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class/ExtObject.h"
#include "CheckBoxManager.generated.h"

class UExtCheckBox;

USTRUCT(BlueprintType)
struct FCheckBoxGroup
{
	GENERATED_USTRUCT_BODY()

	//保存一组 ExtCheckBox 的键值
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, UExtCheckBox*> CheckBoxChildMap;

	//当前组中选中的 ChildKey
	UPROPERTY(BlueprintReadOnly)
	FString CheckedChildKey = "ChildKey_NULL";
};

UCLASS()
class EXTENSIONCLASS_API UCheckBoxManager : public UExtObject
{
	GENERATED_BODY()

public:
	/** 用于管理 ExtCheckBox */
	UPROPERTY()
	TMap<FString, FCheckBoxGroup> CheckBoxMainMap;
};
