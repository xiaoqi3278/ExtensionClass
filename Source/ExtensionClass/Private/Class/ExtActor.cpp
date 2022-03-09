// Fill out your copyright notice in the Description page of Project Settings.


#include "Class/ExtActor.h"



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
	
}

// Called every frame
void AExtActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExtActor::SetExtActorHiddenInGame(bool NewHidden)
{
	this->SetActorHiddenInGame(NewHidden);

	OnActorHiddenChanged.Broadcast(NewHidden);
}

