// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/Model/BaseModel.h"

#include "Utilities/ExtLog.h"
#include "Frame/Utilities/ModelLibrary.h"
#include "Frame/Utilities/ModelTree.h"
#include "Frame/Manager/ModelManager.h"

void UBaseModel::OnBegin()
{
	Super::OnBegin();
}

void UBaseModel::OnEnd()
{
	Super::OnEnd();

	OnModelDestroyed.Broadcast(this->GetClass());
	
}

TSubclassOf<UBaseModel> UBaseModel::GetSelfClass()
{
	return this->GetClass();
}

TSubclassOf<UBaseModel> UBaseModel::GetParentClass()
{
	UModelTree* TempModelTree = UModelLibrary::GetModelManager(this)->ModelTree;
	if (TempModelTree == nullptr)
	{
		//UE_LOG(ExtensionLog, Warning, TEXT("[%s] GetParentClass(): ��ȡ ModelTree ʧ��"), *this->GetName());
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] GetParentClass(): ָ���Ĵ�������Ϊ�գ�"), *this->GetName());

		return nullptr;
	}

	TSharedPtr<FModelTreeNode> TempNode = TempModelTree->SearchNode(this->GetClass(), TempModelTree->RootNode);
	if (TempNode == nullptr)
	{
		//UE_LOG(ExtensionLog, Warning, TEXT("[%s] GetParentClass(): ModelTree �в����ڰ��� %s �Ľڵ�"), *this->GetName(), *this->GetClass()->GetName());
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] GetParentClass(): ModelTree �в����ڰ��� %s �Ľڵ�"), *this->GetName(), *(this->GetClass())->GetName());
		return nullptr;
	}
	
	return TempNode->ParentModelClass;
}
