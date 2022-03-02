// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class/ExtObject.h"
//#include "Tree.generated.h"

/**
 * 
 */

template <typename TData>
struct FTreeNode
{
	TData data;
	FTreeNode FirstChild;
	FTreeNode NextBrother;
};

//UCLASS(typename, TData)
template <typename TData>
class EXTENSIONCLASS_API UTree : public UExtObject
{
	//GENERATED_BODY()
	
public:

	/** 根节点 */
	FTreeNode RootNode;

public:

	UTree();
	UTree(TData Data);
};
