// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Utilities/ModelLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "Utilities/ExtLog.h"
#include "Frame/ExtGameInstance.h"
#include "Frame/Manager/ModelManager.h"
#include "Frame/Model/BaseModel.h"
#include "Frame/Utilities/ModelTree.h"

UModelManager* UModelLibrary::GetModelManager(UObject* WorldContextObject)
{
	UExtGameInstance* TempGameInstance = Cast<UExtGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));

	return TempGameInstance->ModelManager;
}

bool UModelLibrary::CheckModelManagerAndOutLog(UObject* WorldContextObject, UModelManager* Manager, FString FunctionName)
{
	if (Manager != nullptr)
	{
		return true;
	}

	UE_LOG(ExtensionLog, Warning, TEXT("[%s] %s(): 未能获取到 ModleManager!"), *WorldContextObject->GetName(), *FunctionName);
	return false;
}

UBaseModel* UModelLibrary::CreateModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ParentModelClass, TSubclassOf<UBaseModel> ModelClass)
{
	if (*ModelClass == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] CreateMainModel(): 指定的创建类型为空！"), *WorldContextObject->GetName());
		return nullptr;
	}

	UModelManager* ModelManager = GetModelManager(WorldContextObject);
	if (CheckModelManagerAndOutLog(WorldContextObject, ModelManager, "CraeteModel"))
	{
		//创建 Model 对象
		UBaseModel* NewModel = NewObject<UBaseModel>(ModelClass);

		//将 Model 对象添加到 全局 ModelTree 中
		ModelManager->ModelTree->Add(ParentModelClass, NewModel);

		return NewModel;
	}

	return nullptr;
}

void UModelLibrary::DestroyModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ModelClass)
{
	UModelManager* ModelManager = GetModelManager(WorldContextObject);
	if (CheckModelManagerAndOutLog(WorldContextObject, ModelManager, "CraeteModel"))
	{
		ModelManager->ModelTree->DeleteNode(ModelClass);
	}
}
