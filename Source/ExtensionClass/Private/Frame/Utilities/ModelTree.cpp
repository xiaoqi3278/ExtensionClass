// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Utilities/ModelTree.h"

#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

#include "Frame/Model/BaseModel.h"

void UModelTree::OnBegin()
{
	Super::OnBegin();

	//构造默认根节点
	DefaultModel = NewObject<UBaseModel>();
	//RootNode = FModelTreeNode(DefaultModel);
	RootNode = MakeShareable(new FModelTreeNode(DefaultModel));
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
	TSharedPtr<FModelTreeNode> NewNode = MakeShareable(new FModelTreeNode(Model, ParentModelClass));
	TSharedPtr<FModelTreeNode> ParentNode = SearchNode(ParentModelClass, RootNode);

	//若指定的父节点类型为空则默认添加到根节点下
	if (ParentModelClass == nullptr)
	{
		RootNode->ChildNodes.Add(NewNode);
	}

	
	if (ParentNode == nullptr || ParentNode->Model == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] ModelTree->Add(): 不存在指定的父节点。ParentModelClass: %s。Model: %s ！"), *this->GetName(), *ParentModelClass->GetName(), *Model->GetName());
		return;
	}

	ParentNode->ChildNodes.Add(NewNode);
}

TSharedPtr<FModelTreeNode> UModelTree::SearchNode(TSubclassOf<UBaseModel> SearchNodeClass, TSharedPtr<FModelTreeNode> SearchBeginNode)
{
	if (SearchNodeClass == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] SearchNode(): 搜索类型为空！"), *this->GetName());
		return nullptr;
	}

	//若搜索类型为根节点类型
	if (SearchNodeClass == RootNode->Model->GetClass())
	{
		return RootNode;
	}

	//递归搜索
	for (auto Itr : SearchBeginNode->ChildNodes)
	{	
		if (UKismetMathLibrary::EqualEqual_ClassClass(Itr->Model->GetClass(), SearchNodeClass))
		{
			return Itr;
		}
		
		TSharedPtr<FModelTreeNode> TempNode = SearchNode(SearchNodeClass, Itr);
		if (TempNode != nullptr)
		{
			return TempNode;
		}
	}

	return nullptr;
}

void UModelTree::DeleteNode(TSubclassOf<UBaseModel> DeleteNodeClass)
{
	TSharedPtr<FModelTreeNode> DeleteNode = SearchNode(DeleteNodeClass, RootNode);

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

TArray<TSharedPtr<FModelTreeNode>> UModelTree::SearchAllChildNode(TSubclassOf<UBaseModel> SearchModelClass)
{
	TArray<TSharedPtr<FModelTreeNode>> NodeArray = TArray<TSharedPtr<FModelTreeNode>>();

	if (SearchNode(SearchModelClass, RootNode) == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] SearchAllChildNode(): 搜索类型为空！"), *this->GetName());
		return NodeArray;
	}

	//若子节点为空
	if (SearchNode(SearchModelClass, RootNode)->ChildNodes.IsEmpty())
	{
		return NodeArray;
	}

	for (auto& Itr : SearchNode(SearchModelClass, RootNode)->ChildNodes)
	{
		NodeArray.Add(Itr);
		if (!Itr->ChildNodes.IsEmpty())
		{
			NodeArray.Append(SearchAllChildNode(Itr->Model->GetClass()));
		}
	}
	
	return NodeArray;
}

TArray<TSharedPtr<FModelTreeNode>> UModelTree::GetAllNode()
{
	TArray<TSharedPtr<FModelTreeNode>> NodeArray = TArray<TSharedPtr<FModelTreeNode>>();

	//添加根节点
	NodeArray.Add(RootNode);

	if (!RootNode->ChildNodes.IsEmpty())
	{
		NodeArray.Append(SearchAllChildNode(RootNode->Model->GetClass()));
	}

	return NodeArray;
}
