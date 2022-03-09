// Fill out your copyright notice in the Description page of Project Settings.


#include "Class/ExtCheckBox.h"

#include "FunctionLibrary/CheckBoxLibrary.h"
#include "Manager/CheckBoxManager.h"
#include "Utilities/ExtLog.h"

void UExtCheckBox::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	
	if (bDontManage)
		return;

	this->SetCheckedState(bIsDefaultChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);

	//初始化
	if (!IsDesignTime() && bIsInitial)
		OnInitialized();

	//生成 Index
	if (IsDesignTime() && GenerateIndex != "")
		GenerateToIndex(GenerateIndex);
}

void UExtCheckBox::OnInitialized()
{
	bIsInitial = false;

	OnCheckStateChanged.AddDynamic(this, &UExtCheckBox::OnClick);

	UCheckBoxLibrary::AddCheckBox(this, MainKey, ChildKey, this);

	Manager = UCheckBoxLibrary::GetCheckBoxManager(this);

	if (bIsDefaultChecked && Manager != nullptr)
	{
		if (bExecuteBindOnDefaultChecked)
		{
			UCheckBoxLibrary::SetOneExtCheckedState(this, this->MainKey, this->ChildKey, ECheckBoxState::Checked);
		}
		Manager->CheckBoxMainMap.Find(MainKey)->CheckedChildKey = this->ChildKey;
	}
}

void UExtCheckBox::GenerateToIndex(FString GenerateKey)
{
	//仅在编辑状态下能修改

	FString LeftString;
	FString RightString;

	GenerateKey.Split("<>", &LeftString, &RightString, ESearchCase::IgnoreCase, ESearchDir::FromStart);

	int32 AddNum = FCString::Atoi(*RightString);
	int32 ChildKeyAsNum = FCString::Atoi(*ChildKey);
	
	//解析失败
	if (AddNum == 0 || (ChildKeyAsNum == 0 && ChildKey != "0"))
	{
		return;
	}

	if (LeftString == "ChildKey")
	{
		Index = ChildKeyAsNum + AddNum;
	}
}

void UExtCheckBox::OnClick(bool bIsChecked)
{
	UCheckBoxLibrary::SetOneExtCheckedState(this, MainKey, ChildKey, bIsChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
}

void UExtCheckBox::SetExtCheckedState(ECheckBoxState ExtCheckedState)
{
	if (bDontManage)
	{
		return;
	}

	if (Manager == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] %s(): CheckBoxManage Get Faild!"), *this->GetName(), *"SetExtCheckedState");
		return;
	}

	if (ExtCheckedState == ECheckBoxState::Unchecked && bAlwaysChecked)
	{
		//始终选中
		this->SetCheckedState(ECheckBoxState::Checked);
		Manager->CheckBoxMainMap.Find(MainKey)->CheckedChildKey = "ChildKey_NULL";

		if (bExecuteBindOnReChecked)
		{
			OnExtCheckStateChanged.Broadcast(true, Index);
			return;
		}

		return;
	}

	SetCheckedState(ExtCheckedState);

	Manager->CheckBoxMainMap.Find(MainKey)->CheckedChildKey = ExtCheckedState == ECheckBoxState::Checked ? ChildKey : "ChildKey_NULL";
	if (bAlwaysChecked)
	{
		Manager->CheckBoxMainMap.Find(MainKey)->CheckedChildKey = "ChildKey_NULL";
	}


	//调用 OnExtCheckedStateChanged 绑定的事件
	OnExtCheckStateChanged.Broadcast(ExtCheckedState == ECheckBoxState::Checked ? true : false, Index);
}
