// Fill out your copyright notice in the Description page of Project Settings.


#include "Class/ExtUserWidget.h"

#include "Frame/Utilities/WidgetLibrary.h"

void UExtUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (bSaveToWidgetManager)
	{
		if (bSingleWidget)
		{
			UWidgetLibrary::AddToWidgetManager(this, WidgetKey, this);
		}
		else
		{
			UWidgetLibrary::AddToWidgetManagerOfGroup(this, WidgetMainKey, WidgetChildKey, this);
		}
	}
}

void UExtUserWidget::RemoveAndMarkGC()
{
	this->RemoveFromParent();
	this->MarkPendingKill();
}
