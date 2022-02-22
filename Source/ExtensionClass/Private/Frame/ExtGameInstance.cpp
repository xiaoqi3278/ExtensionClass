// Fill out your copyright notice in the Description page of Project Settings.


#include "Frame/ExtGameInstance.h"

#include "Frame/Manager/WidgetManager.h"

void UExtGameInstance::Init()
{
	WidgetManager = NewObject<UWidgetManager>(this);
}
