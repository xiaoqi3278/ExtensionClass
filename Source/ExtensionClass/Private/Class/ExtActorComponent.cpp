// Fill out your copyright notice in the Description page of Project Settings.


#include "Class/ExtActorComponent.h"

#include "ExtensionClass/Public/Manager/ActorManager.h"
#include "ExtensionClass/Public/FunctionLibrary/ActorLibrary.h"
#include "Utilities/ExtLog.h"

// Sets default values for this component's properties
UExtActorComponent::UExtActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UExtActorComponent::BeginPlay()
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
			ChildKey = this->GetOwner()->GetName();
		}
		ActorManager->GroupActorMainMap.FindOrAdd(MainKey).GroupActorChildMap.Emplace(ChildKey, this->GetOwner());
	}
}


// Called every frame
void UExtActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

