// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class/ExtObject.h"
#include "ActorManager.generated.h"

/**
 * 
 */

class AActor;

USTRUCT(BlueprintType)
struct FActorGroup
{
	GENERATED_BODY()

public:

	/** 用于存储一组 Actor 的 Map */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, AActor*> GroupActorChildMap;
};

UCLASS()
class EXTENSIONCLASS_API UActorManager : public UExtObject
{
	GENERATED_BODY()
	
public:

	/** 用于存储 单个 String 对应单个 Actor 的 Map */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, AActor*> SingleActorMap;

	/** 用于存储 ActorGroup 的 Map */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FActorGroup> GroupActorMainMap;
};
