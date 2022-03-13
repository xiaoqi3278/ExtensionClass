// Fill out your copyright notice in the Description page of Project Settings.


#include "Class/ExtUserWidget.h"

void UExtUserWidget::RemoveAndMarkGC()
{
	this->RemoveFromParent();
	this->MarkPendingKill();
}
