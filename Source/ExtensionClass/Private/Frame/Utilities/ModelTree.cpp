// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Utilities/ModelTree.h"

#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

#include "Frame/Model/BaseModel.h"

UModelTree::UModelTree()
{
	//构造默认根节点
	UBaseModel* DefaultModel = NewObject<UBaseModel>();
	RootNode = FModelTreeNode(DefaultModel);
}

UModelTree::UModelTree(UBaseModel* Model)
{
	RootNode = FModelTreeNode(Model);
}

FModelTreeNode UModelTree::CreateNode(UBaseModel* Model)
{
	if (Model == nullptr)
	{
		return FModelTreeNode();
	}

	return FModelTreeNode(Model);
}

void UModelTree::Add(TSubclassOf<UBaseModel> ParentModelClass, UBaseModel* Model)
{
	FModelTreeNode* NewNode = new FModelTreeNode(Model, ParentModelClass);
	FModelTreeNode* ParentNode = SearchNode(ParentModelClass, &RootNode);

	//若指定的父节点为空
	if (ParentNode->Model == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] ModelTree->Add(): 指定的父节点类型为空！"), *this->GetName());
		return;
	}

	ParentNode->ChildNodes.Add(NewNode);
}

FModelTreeNode* UModelTree::SearchNode(TSubclassOf<UBaseModel> SearchNodeClass, FModelTreeNode* SearchBeginNode)
{
	if (SearchNodeClass == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] SearchNode(): 搜索类型为空！"), *this->GetName());
		return nullptr;
	}

	//若搜索类型为根节点类型
	if (SearchNodeClass == RootNode.Model->GetClass())
	{
		return &RootNode;
	}

	//递归搜索
	for (auto Itr : SearchBeginNode->ChildNodes)
	{	
		if (UKismetMathLibrary::EqualEqual_ClassClass(Itr->Model->GetClass(), SearchNodeClass))
		{
			return Itr;
		}
		
		FModelTreeNode* TempNode = SearchNode(SearchNodeClass, Itr);
		if (TempNode != nullptr)
		{
			return TempNode;
		}
	}

	return nullptr;
}

void UModelTree::DeleteNode(TSubclassOf<UBaseModel> DeleteNodeClass)
{
	FModelTreeNode* DeleteNode = SearchNode(DeleteNodeClass, &RootNode);

	if (DeleteNode->Model == nullptr)
	{
		return;
	}

	//删除子节点
	for (auto& Itr : DeleteNode->ChildNodes)
	{
		this->DeleteNode(Itr->Model->GetClass());
	}

	DeleteNode->Model->DestroyObject();
	DeleteNode->Model = nullptr;
}

TArray<FModelTreeNode*> UModelTree::SearchAllChildNode(TSubclassOf<UBaseModel> SearchModelClass)
{
	TArray<FModelTreeNode*> NodeArray = TArray<FModelTreeNode*>();

	if (SearchNode(SearchModelClass, &RootNode) == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] SearchAllChildNode(): 搜索类型为空！"), *this->GetName());
		return NodeArray;
	}

	//若子节点为空
	if (SearchNode(SearchModelClass, &RootNode)->ChildNodes.IsEmpty())
	{
		return NodeArray;
	}

	for (auto& Itr : SearchNode(SearchModelClass, &RootNode)->ChildNodes)
	{
		NodeArray.Add(Itr);
		if (!Itr->ChildNodes.IsEmpty())
		{
			NodeArray.Append(SearchAllChildNode(Itr->Model->GetClass()));
		}
	}
	
	return NodeArray;
}

TArray<FModelTreeNode*> UModelTree::GetAllNode()
{
	TArray<FModelTreeNode*> NodeArray = TArray<FModelTreeNode*>();

	//添加根节点
	NodeArray.Add(&RootNode);

	if (!RootNode.ChildNodes.IsEmpty())
	{
		NodeArray.Append(SearchAllChildNode(RootNode.Model->GetClass()));
	}

	return NodeArray;
}
