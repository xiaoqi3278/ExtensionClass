// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class/ExtObject.h"

#include "Utilities/ExtLog.h"

#include "ModelTree.generated.h"

/**
 * 树形 Model 容器
 */

class UBaseModel;

/** 单个节点结构 */
struct EXTENSIONCLASS_API FModelTreeNode : public FGCObject
{
	//节点包含的模块
	UBaseModel* Model = nullptr;

	//父节点
	//FModelTreeNode* ParentNode;
	TSubclassOf<UBaseModel> ParentModelClass = nullptr;

	//子节点
	TArray<TSharedPtr<FModelTreeNode>> ChildNodes;

	FModelTreeNode()
	{
		ParentModelClass = nullptr;
		Model = nullptr;
		ChildNodes = TArray<TSharedPtr<FModelTreeNode>>();
	}

	FModelTreeNode(UBaseModel* TempModel)
	{
		ParentModelClass = nullptr;
		Model = TempModel;
		ChildNodes = TArray<TSharedPtr<FModelTreeNode>>();
	}

	FModelTreeNode(UBaseModel* TempModel, TSubclassOf<UBaseModel> TempParentModelClass)
	{
		ParentModelClass = TempParentModelClass;
		Model = TempModel;
		ChildNodes = TArray<TSharedPtr<FModelTreeNode>>();
	}

protected:

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		Collector.AddReferencedObject(Model);
	}
};

UCLASS()
class EXTENSIONCLASS_API UModelTree : public UExtObject
{
	GENERATED_BODY()
	
private:

protected:

	virtual void OnBegin() override;

public:

	/** 根节点 */
	TSharedPtr<FModelTreeNode> RootNode = nullptr;

	/** 根节点模块 */
	UPROPERTY()
	UBaseModel* DefaultModel = nullptr;

	/** 用于持久化创建的 Model */
	UPROPERTY()
	TArray<UBaseModel*> PersistenceArray;

public:

	/**
	* 创建一个包含传入 Model 的节点
	*/
	FModelTreeNode CreateNode(UBaseModel* Model);

	/**
	 * 创建一个包含传入 Model 的节点并加入 ModelTree 中
	 * 
	 * @param	ParentModelClass	父节点类型
	 * @param	Model				节点包含的 UBaseModel
	 */
	UFUNCTION()
	void Add(TSubclassOf<UBaseModel> ParentModelClass, UBaseModel* Model);

	/**
	 * 搜索包含对应类型的节点
	 * 
	 * @param	SearchNodeClass		需要搜索的节点包含的 Model 类型
	 * @return						搜索到的节点
	 */
	TSharedPtr<FModelTreeNode> SearchNode(TSubclassOf<UBaseModel> SearchNodeClass, TSharedPtr<FModelTreeNode> SearchBeginNode);

	/**
	 * 删除包含对应类型的节点以及所有子节点，对应会删除节点包含的所有 Model 对象
	 * 
	 * @param	DeleteNodeClass		需要删除的节点包含的 Model 的类型
	 */
	UFUNCTION()
	void DeleteNode(TSubclassOf<UBaseModel> DeleteNodeClass);

	/**
	* 搜索对应节点的所有子节点
	* 
	* @param	SearchModelClass	需要搜索的节点包含的 Model 类型
	* @return						搜索到的所有子节点
	*/
	TArray<TSharedPtr<FModelTreeNode>> SearchAllChildNode(TSubclassOf<UBaseModel> SearchModelClass);

	/**
	* 获取所有的节点
	*/
	TArray<TSharedPtr<FModelTreeNode>> GetAllNode();
};
