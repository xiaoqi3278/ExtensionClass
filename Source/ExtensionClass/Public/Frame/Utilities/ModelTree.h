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

	//�ڵ�ģ��
	UPROPERTY(BlueprintReadWrite)
	UBaseModel* Model;

	//��һ���ӽڵ�
	UPROPERTY(BlueprintReadWrite)
	FModelTreeNode* FirstChild;

	//��һ���ֵܽڵ�
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

	//���ڵ�
	UPROPERTY()
	FModelTreeNode* RootNode;

public:

	UModelTree();

	UModelTree(UBaseModel* Model);
};
