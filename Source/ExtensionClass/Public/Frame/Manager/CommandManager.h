// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class/ExtObject.h"
#include "CommandManager.generated.h"

/**
 * Command 管理器
 */

class UBaseCommand;

UCLASS()
class EXTENSIONCLASS_API UCommandManager : public UExtObject
{
	GENERATED_BODY()
	
public:

	/** 命令队列 */
	TQueue<UBaseCommand*> CommandQueue;
};
