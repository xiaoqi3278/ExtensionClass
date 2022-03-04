// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Utilities/ModelTree.h"

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

void UModelTree::Add(TSubclassOf<UBaseModel> ParentModelClass, UBaseModel* Model)
{
	FModelTreeNode NewNode = FModelTreeNode(Model);
	FModelTreeNode ParentNode = SearchNode(ParentModelClass);

	//指定父节点为空
	if (ParentNode.Model == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] ModelTree->Add(): 指定的父节点类型为空！"), *this->GetName());
		return;
	}

	ParentNode.ChildNodes.Add(NewNode);
}

FModelTreeNode UModelTree::SearchNode(TSubclassOf<UBaseModel> SearchNodeClass)
{
	if (SearchNodeClass == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] SearchNode(): 搜索类型为空！"), *this->GetName());
		return FModelTreeNode();
	}

	//搜索类型为根节点类型
	if (SearchNodeClass == RootNode.Model->GetClass())
	{
		return RootNode;
	}

	//递归搜索
	for (auto& Itr : RootNode.ChildNodes)
	{
		if (Itr.Model->GetClass() == SearchNodeClass)
		{
			return Itr;
		}
		
		SearchNode(Itr.Model->GetClass());
	}

	return FModelTreeNode();
}

void UModelTree::DeleteNode(TSubclassOf<UBaseModel> DeleteNodeClass)
{
	FModelTreeNode DeleteNode = SearchNode(DeleteNodeClass);

	if (DeleteNode.Model == nullptr)
	{
		return;
	}

	//删除子节点
	for (auto& Itr : DeleteNode.ChildNodes)
	{
		this->DeleteNode(Itr.Model->GetClass());
	}

	DeleteNode.Model->DestroyObject();
	DeleteNode.Model = nullptr;
}
