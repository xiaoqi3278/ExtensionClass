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

public:

	/** 添加一个命令到命令队列, 并通知 ModelManager 对命令进行处理 */
	void EnqueueCommand(UBaseCommand* Command);

	/** 移除命令队列中的一个命令 */
	void DequeueCommand(UBaseCommand* Command);
};
