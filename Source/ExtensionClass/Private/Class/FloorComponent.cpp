// Fill out your copyright notice in the Description page of Project Settings.


#include "Class/FloorComponent.h"

#include "FunctionLibrary/ActorLibrary.h"

// Sets default values for this component's properties
UFloorComponent::UFloorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFloorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* OwnerActor = this->GetOwner();

	if (OwnerActor != nullptr)
	{
		UActorLibrary::AddGroupActor(this, BuildingName, FString::FromInt(FloorNum), OwnerActor, true);
		InitLocation = OwnerActor->GetActorLocation();
		InitRotation = OwnerActor->GetActorRotation();
	}
}


// Called every frame
void UFloorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

