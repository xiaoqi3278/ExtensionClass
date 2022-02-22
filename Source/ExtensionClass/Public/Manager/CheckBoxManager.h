// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckBoxManager.generated.h"

class UExtCheckBox;

USTRUCT(BlueprintType)
struct FCheckBoxGroup
{
	GENERATED_USTRUCT_BODY()

	//保存一组 ExtCheckBox 的键值
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, UExtCheckBox*> CheckBoxChildMap;
};

UCLASS()
class EXTENSIONCLASS_API ACheckBoxManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckBoxManager();

public:
	/** 用于管理 ExtCheckBox */
	UPROPERTY()
	TMap<FString, FCheckBoxGroup> CheckBoxMainMap;
};
