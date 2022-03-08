// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Utilities/CommandLibrary.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "Frame/Command/BaseCommand.h"
#include "Frame/Utilities/CommandLibrary.h"
#include "Frame/ExtGameInstance.h"
#include "Utilities/ExtLog.h"
#include "Frame/Manager/CommandManager.h"

UCommandManager* UCommandLibrary::GetCommandManager(UObject* WorldContextObject)
{
	UExtGameInstance* TempGameInstance = Cast<UExtGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));

	return TempGameInstance->CommandManager;
}

bool UCommandLibrary::CheckCommandManagerAndOutLog(UObject* WorldContextObject, UCommandManager* Manager, FString FunctionName)
{
	if (Manager != nullptr)
	{
		return true;
	}

	UE_LOG(ExtensionLog, Warning, TEXT("[%s] %s(): 未能获取到 CommandManager!"), *WorldContextObject->GetName(), *FunctionName);
	return false;
}

UBaseCommand* UCommandLibrary::CreateCommand(UObject* WorldContextObject, TSubclassOf<UBaseCommand> CommandClass)
{
	if (CommandClass == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] CreateModel(): 指定的创建类型为空！"), *WorldContextObject->GetName());
		return nullptr;
	}

	UCommandManager* CommandManager = GetCommandManager(WorldContextObject);
	if (CheckCommandManagerAndOutLog(WorldContextObject, CommandManager, "CreateCommand"))
	{
		//创建 Command 对象
		UBaseCommand* NewCommand = NewObject<UBaseCommand>(WorldContextObject, CommandClass);

		return NewCommand;
		//命令入队
		//CommandManager->EnqueueCommand(NewCommand);
	}

	return nullptr;
}

void UCommandLibrary::EnqueueCommand(UObject* WorldContextObject, UBaseCommand* Command)
{
	UCommandManager* CommandManager = GetCommandManager(WorldContextObject);
	if (CheckCommandManagerAndOutLog(WorldContextObject, CommandManager, "CreateCommand"))
	{
		CommandManager->EnqueueCommand(Command);
	}
}
