// Fill out your copyright notice in the Description page of Project Settings.


#include "Class/ExtCheckBox.h"
#include "FunctionLibrary/CheckBoxLibrary.h"
#include "Utilities/ExtLog.h"

void UExtCheckBox::SynchronizeProperties()
{
	Super::SynchronizeProperties();

}

void UExtCheckBox::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (this->GetWorld()->IsEditorWorld())
		return;

	UE_LOG(ExtensionLog, Warning, TEXT("OnExtCheckBoxRebuilt"));

	OnCheckStateChanged.AddDynamic(this, &UExtCheckBox::OnClick);

	UCheckBoxLibrary::AddCheckBox(this, MainKey, ChildKey, this);

	Manager = UCheckBoxLibrary::GetCheckBoxManager(this);
}

void UExtCheckBox::OnClick(bool bIsChecked)
{
	UCheckBoxLibrary::SetExtCheckedState(this, MainKey, ChildKey);
}

void UExtCheckBox::SetExtCheckedState(ECheckBoxState ExtCheckedState)
{
	SetCheckedState(ExtCheckedState);

	//调用 OnExtCheckedStateChanged 绑定的事件
	OnExtCheckStateChanged.Broadcast(ExtCheckedState == ECheckBoxState::Checked ? true : false, Index);
}
