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

	//初始化
	if (!IsDesignTime() && bIsInitial)
		OnInitialized();

	//生成 Index
	if (IsDesignTime() && GenerateIndex != "")
		GenerateToIndex(GenerateIndex);
}

void UExtCheckBox::OnClick(bool bIsChecked)
{
	if (!bIsChecked && !bAlwaysChecked)
	{
		if (bExecuteBindOnReChecked)
		{
			OnExtCheckStateChanged.Broadcast(false, Index);
			return;
		}
		return;
	}

	UCheckBoxLibrary::SetOneExtChecked(this, MainKey, ChildKey);
}

void UExtCheckBox::SetExtCheckedState(ECheckBoxState ExtCheckedState)
{
	if (bDontManage)
		return;

	SetCheckedState(ExtCheckedState);

	//调用 OnExtCheckedStateChanged 绑定的事件
	OnExtCheckStateChanged.Broadcast(ExtCheckedState == ECheckBoxState::Checked ? true : false, Index);

	UCheckBoxLibrary::GetCheckBoxMainMap(this).Find(MainKey)->CheckedChildKey = ExtCheckedState == ECheckBoxState::Checked ? ChildKey : "ChildKey_NULL";
}

void UExtCheckBox::OnInitialized()
{
	bIsInitial = false;

	OnCheckStateChanged.AddDynamic(this, &UExtCheckBox::OnClick);

	UCheckBoxLibrary::AddCheckBox(this, MainKey, ChildKey, this);

	Manager = UCheckBoxLibrary::GetCheckBoxManager(this);
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
		return;

	if (LeftString == "ChildKey")
		Index = ChildKeyAsNum + AddNum;
}
