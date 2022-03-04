// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class/ExtObject.h"
#include "ModelTree.generated.h"

/**
 * 
 */

class UBaseModel;

USTRUCT()
struct FModelTreeNode
{
	GENERATED_BODY()

	//节点模块
	UPROPERTY(BlueprintReadWrite)
	UBaseModel* Model;

	//第一个子节点
	UPROPERTY(BlueprintReadWrite)
	FModelTreeNode* FirstChild;

	//下一个兄弟节点
	UPROPERTY(BlueprintReadWrite)
	FModelTreeNode* NextBrother;

	FModelTreeNode(UBaseModel* TempModel)
	{
		Model = TempModel;
		FirstChild = nullptr;
		NextBrother = nullptr;
	}
};

UCLASS()
class EXTENSIONCLASS_API UModelTree : public UExtObject
{
	GENERATED_BODY()
	
public:

	//根节点
	UPROPERTY()
	FModelTreeNode* RootNode;

public:

	UModelTree();

	UModelTree(UBaseModel* Model);
};
