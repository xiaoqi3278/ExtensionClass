// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Utilities/ModelTree.h"

#include "Frame/Model/BaseModel.h"

UModelTree::UModelTree()
{
	RootNode = nullptr;
}

UModelTree::UModelTree(UBaseModel* Model)
{
	RootNode = &FModelTreeNode(Model);
}
