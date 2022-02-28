// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Utilities/ModelLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "Utilities/ExtLog.h"
#include "Frame/ExtGameInstance.h"
#include "Frame/Manager/ModelManager.h"
#include "Frame/Model/BaseModel.h"

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

UBaseModel* UModelLibrary::CreateMainModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ModelClass)
{
	if (*ModelClass == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] CreateMainModel(): 指定的创建类型为空！"), *WorldContextObject->GetName());
		return nullptr;
	}

	//创建 Model 对象
	UBaseModel* MainModel = NewObject<UBaseModel>(ModelClass);

	//加入 ModelManager
	//UModelManager* ModelManager = GetModelManager(WorldContextObject);
	//if (ModelManager != nullptr)
	//{
	//	ModelManager->ModelMainMap.Emplace(ModelClass, MainModel);
	//}

	return MainModel;
}

UBaseModel* UModelLibrary::CreateChildModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> OwnerModelClass, TSubclassOf<UBaseModel> ModelClass)
{
	if (*ModelClass == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] CreateChildModel(): 指定的创建类型为空！"), *WorldContextObject->GetName());
		return nullptr;
	}

	//创建 Model 对象
	UBaseModel* ChildModel = NewObject<UBaseModel>(ModelClass);

	if (*OwnerModelClass == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] CreateChildModel(): 指定的主 Model 类型为空！"), *WorldContextObject->GetName());
		return nullptr;
	}

	//加入 ModelManager
	//UModelManager* ModelManager = GetModelManager(WorldContextObject);
	//if (CheckModelManagerAndOutLog(WorldContextObject, ModelManager, "CreateChildModel"))
	//{
	//	(ModelManager->ModelGroupMap.FindOrAdd(OwnerModelClass)).ModelChildMap.Emplace(ModelClass, ChildModel);
	//}

	return ChildModel;
}

void UModelLibrary::DestroyMainModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ModelClass)
{
	if (*ModelClass == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] DestroyModel(): 指定的销毁类型为空！"), *WorldContextObject->GetName());
		return;
	}

	UModelManager* ModelManager = GetModelManager(WorldContextObject);
	if (CheckModelManagerAndOutLog(WorldContextObject, ModelManager, "DestroyModel"))
	{
		
	}
}
