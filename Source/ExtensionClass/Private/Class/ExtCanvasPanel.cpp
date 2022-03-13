// Fill out your copyright notice in the Description page of Project Settings.


#include "Class/ExtCanvasPanel.h"

#include "Class/ExtCheckBox.h"

void UExtCanvasPanel::SetExtVisibility(ESlateVisibility InVisibility, bool bUnCheck = true, bool bExecBindWhenUnCheck = true)
{
	this->SetVisibility(InVisibility);

	if (bUnCheck && InVisibility == ESlateVisibility::Collapsed)
	{
		for (auto& Itr : this->GetAllChildren())
		{
			UExtCheckBox* TempExtCheckBox = Cast<UExtCheckBox>(Itr);
			if (TempExtCheckBox != nullptr)		//ExtCheckBox
			{
				TempExtCheckBox->SetExtCheckedState(ECheckBoxState::Unchecked, !bExecBindWhenUnCheck);
			}
			else
			{
				UCheckBox* TempCheckBox = Cast<UCheckBox>(Itr);
				if (TempCheckBox != nullptr)	//CheckBox
				{
					TempCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
				}
			}
		}
	}
}
