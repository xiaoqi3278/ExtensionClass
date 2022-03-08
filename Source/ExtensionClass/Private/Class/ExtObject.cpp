// Fill out your copyright notice in the Description page of Project Settings.


#include "Class/ExtObject.h"

#include "Utilities/ExtLog.h"

void UExtObject::PostInitProperties()
{
	Super::PostInitProperties();

	/** 只在游戏世界中调用 */
	if (GetWorld())
	{
		OnBegin();
	}

	/*
	//Вызываем только в игре, когда есть мир. В редакторе BeginPlay вызван не будет
	//机翻：只在游戏世界中调用，不会在编辑器中调用。
	if (GetOuter() && GetOuter()->GetWorld())
		OnBegin();
	*/
}

UWorld* UExtObject::GetWorld() const
{
	// CDO objects do not belong to a world
	// If the actors outer is destroyed or unreachable we are shutting down and the world should be nullptr
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(), TEXT("Actor: %s has a null OuterPrivate in AActor::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		return GetOuter()->GetWorld();
	}
	return nullptr;

	/*
	// Возвращаем ссылку на мир из владельца объекта, если не работаем редакторе.
	if (!FApp::IsGame()) return nullptr;
	else if (GetOuter()) return GetOuter()->GetWorld();
	else return nullptr;
	*/
}

void UExtObject::OnBegin()
{
	BeginPlay();
}

void UExtObject::OnEnd()
{
	EndPlay();
}

void UExtObject::DestroyObject()
{
	OnEnd();
	
	OnExtObjectDestroyed.Broadcast(Index);

	//标记为需要被回收，所有引用置空
	this->MarkPendingKill();
}
