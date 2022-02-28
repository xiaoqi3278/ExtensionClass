// Fill out your copyright notice in the Description page of Project Settings.


#include "Class/ExtObject.h"

void UExtObject::PostInitProperties()
{
	Super::PostInitProperties();

	/** 只在游戏世界中调用 */
	if (GetWorld())
	{
		NativeBegin();
	}
}

UWorld* UExtObject::GetWorld() const
{
	//if (GetOuter())
	//{
	//	return GetOuter()->GetWorld();
	//}

	//return nullptr;

	// CDO objects do not belong to a world
	// If the actors outer is destroyed or unreachable we are shutting down and the world should be nullptr
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(), TEXT("Actor: %s has a null OuterPrivate in AActor::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		return GetOuter()->GetWorld();
	}
	return nullptr;
}

void UExtObject::NativeBegin()
{
	BeginPlay();
}
