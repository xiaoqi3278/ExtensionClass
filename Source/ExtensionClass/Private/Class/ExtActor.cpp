// Fill out your copyright notice in the Description page of Project Settings.


#include "Class/ExtActor.h"

#include "ExtensionClass/Public/Manager/ActorManager.h"
#include "ExtensionClass/Public/FunctionLibrary/ActorLibrary.h"
#include "Utilities/ExtLog.h"

// Sets default values
AExtActor::AExtActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExtActor::BeginPlay()
{
	Super::BeginPlay();
	
	UActorManager* ActorManager = UActorLibrary::GetActorManager(this);

	if (ActorManager == nullptr)
	{
		UE_LOG(ExtensionLog, Warning, TEXT("[%s] BeginPlay(): GetActorManager Failed!"), *this->GetName());
		return;
	}

	if (bIsSingleActor)
	{
		if (ActorKey == "")
		{
			ActorKey = this->GetName();
		}
		ActorManager->SingleActorMap.Emplace(ActorKey, this->GetOwner());
	}
	else
	{
		if (MainKey == "")
		{
			return;
		}
		if (ChildKey == "")
		{
			ChildKey = this->GetName();
		}
		ActorManager->GroupActorMainMap.FindOrAdd(MainKey).GroupActorChildMap.Emplace(ChildKey, this);
	}
}

// Called every frame
void AExtActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExtActor::SetExtActorHiddenInGame(bool bNewHidden)
{
	if (IsHidden() != bNewHidden)
	{
		this->SetActorHiddenInGame(bNewHidden);
		OnActorHiddenChanged.Broadcast(bNewHidden);
	}
}

