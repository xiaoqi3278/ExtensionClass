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
	
	//调用绑定回调
	OnExtObjectDestroyed.Broadcast(Index);

	//标记为需要被GC
	this->MarkPendingKill();
}
