// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class/ExtObject.h"

#include "Utilities/ExtLog.h"

#include "ModelTree.generated.h"

/**
 * 
 */

class UBaseModel;

struct FModelTreeNode
{
	//节点模块
	UBaseModel* Model;

	//父节点
	//FModelTreeNode* ParentNode;
	TSubclassOf<UBaseModel> ParentModelClass;

	//子节点
	TArray<FModelTreeNode> ChildNodes;

	FModelTreeNode()
	{
		ParentModelClass = nullptr;
		Model = nullptr;
	}

	FModelTreeNode(UBaseModel* TempModel)
	{
		ParentModelClass = nullptr;
		Model = TempModel;
	}
};

UCLASS()
class EXTENSIONCLASS_API UModelTree : public UExtObject
{
	GENERATED_BODY()
	
public:

	//根节点
	FModelTreeNode RootNode;

public:

	UModelTree();

	UModelTree(UBaseModel* Model);

	/**
	 * 创建一个包含传入 Model 的节点
	 * 
	 * @param ParentModelClass		父节点类型
	 * @param Model					节点包含的 UBaseModel
	 */
	UFUNCTION()
	void Add(TSubclassOf<UBaseModel> ParentModelClass, UBaseModel* Model);

	/**
	 * 搜索包含对应类型的节点
	 * 
	 * @param SearchNodeClass		需要搜索的节点包含的 Model s类型
	 * @return						搜索到的节点
	 */
	FModelTreeNode SearchNode(TSubclassOf<UBaseModel> SearchNodeClass);

	/**
	 * 删除包含对应类型的节点以及所有子节点，对应会删除节点包含的所有 Model 对象
	 * 
	 * @param DeleteNodeClass		需要删除的节点包含的 Model 的类型
	 */
	UFUNCTION()
	void DeleteNode(TSubclassOf<UBaseModel> DeleteNodeClass);
};
