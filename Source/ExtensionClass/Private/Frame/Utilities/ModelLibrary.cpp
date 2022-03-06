// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Utilities/ModelLibrary.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

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
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] CreateModel(): 指定的创建类型为空！"), *WorldContextObject->GetName());
		return nullptr;
	}

	if (SearchModel(WorldContextObject, ParentModelClass) == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] CreateModel(): 不存在父模块：ParentModelClass: %s, ModelClass: %s !"), *WorldContextObject->GetName(), *ParentModelClass->GetName(), *ModelClass->GetName());
		return nullptr;
	}
	
	if (SearchModel(WorldContextObject, ModelClass) != nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] CreateModel(): 已存在 %s 模块！"), *WorldContextObject->GetName(), *ModelClass->GetName());
		return nullptr;
	}

	UModelManager* ModelManager = GetModelManager(WorldContextObject);
	if (CheckModelManagerAndOutLog(WorldContextObject, ModelManager, "CreateModel"))
	{
		//创建 Model 对象
		UBaseModel* NewModel = NewObject<UBaseModel>(WorldContextObject, ModelClass);

		//持久化 Model 对象，保证不被回收
		ModelManager->ModelTree->PersistenceArray.Add(NewModel);

		//在不对此对象进行引用时保证其不被回收
		//NewModel->AddToRoot();

		//将 Model 对象添加到 全局 ModelTree 中
		ModelManager->ModelTree->Add(ParentModelClass, NewModel);

		return NewModel;
	}

	return nullptr;
}

void UModelLibrary::DestroyModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ModelClass)
{
	UModelManager* ModelManager = GetModelManager(WorldContextObject);
	if (CheckModelManagerAndOutLog(WorldContextObject, ModelManager, "DestroyModel"))
	{
		ModelManager->ModelTree->DeleteNode(ModelClass);
	}
}

UBaseModel* UModelLibrary::SearchModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ModelClass)
{
	UModelManager* ModelManager = GetModelManager(WorldContextObject);
	if (CheckModelManagerAndOutLog(WorldContextObject, ModelManager, "SearchModel"))
	{
		TSharedPtr<FModelTreeNode> TreeNode = ModelManager->ModelTree->SearchNode(ModelClass, ModelManager->ModelTree->RootNode);

		if (TreeNode == nullptr)
		{
			//UE_LOG(ExtensionLog, Warning, TEXT("[%s] SearchModel(): 不存在 %s 模块！"), *WorldContextObject->GetName(), *ModelClass->GetName());
			return nullptr;
		}
		return TreeNode->Model;
	}

	return nullptr;
}

TArray<UBaseModel*> UModelLibrary::SearchChildFirstLevelModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ModelClass)
{
	UModelManager* ModelManager = GetModelManager(WorldContextObject);
	if (CheckModelManagerAndOutLog(WorldContextObject, ModelManager, "SearchModel"))
	{
		//子节点为空
		TArray<TSharedPtr<FModelTreeNode>> ChildNodeArray = ModelManager->ModelTree->SearchNode(ModelClass, ModelManager->ModelTree->RootNode)->ChildNodes;
		if (ChildNodeArray.IsEmpty())
		{
			return TArray<UBaseModel*>();
		}

		TArray<UBaseModel*> ModelArray;
		for (auto& Itr : ChildNodeArray)
		{
			ModelArray.Add(Itr->Model);
		}

		return ModelArray;
	}

	return TArray<UBaseModel*>();
}

TArray<UBaseModel*> UModelLibrary::SearchAllChildModel(UObject* WorldContextObject, TSubclassOf<UBaseModel> ModelClass)
{
	TArray<UBaseModel*> ModelArray = TArray<UBaseModel*>();

	UModelManager* ModelManager = GetModelManager(WorldContextObject);
	if (CheckModelManagerAndOutLog(WorldContextObject, ModelManager, "SearchModel"))
	{
		//子节点为空
		TArray<TSharedPtr<FModelTreeNode>> ChildNodeArray = ModelManager->ModelTree->SearchAllChildNode(ModelClass);
		if (ChildNodeArray.IsEmpty())
		{
			return ModelArray;
		}

		for (auto& Itr : ChildNodeArray)
		{
			ModelArray.Add(Itr->Model);
		}
	}

	return ModelArray;
}

TArray<UBaseModel*> UModelLibrary::GetAllModel(UObject* WorldContextObject)
{
	TArray<UBaseModel*> ModelArray = TArray<UBaseModel*>();

	UModelManager* ModelManager = GetModelManager(WorldContextObject);
	if (CheckModelManagerAndOutLog(WorldContextObject, ModelManager, "SearchModel"))
	{
		for (auto& Itr : ModelManager->ModelTree->GetAllNode())
		{
			if (Itr->Model != nullptr)
			{
				ModelArray.Add(Itr->Model);
			}
		}
	}

	return ModelArray;
}

void UModelLibrary::ModelTest(TSubclassOf<UBaseModel> Class1, TSubclassOf<UBaseModel> Class2)
{
	bool test = UKismetMathLibrary::EqualEqual_ClassClass(Class1, Class2);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, test ? "True" : "False");
}
