// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExtActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXTENSIONCLASS_API UExtActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExtActorComponent();

public:

	/**
	* true => ���뵽 ActorManager.SingleActorMap
	* false => ���뵽 ActorManager.GroupActorMainMap
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtActorComponent|SingleManage")
	bool bIsSingleActor;

	/** ��ѡ IsSingleActor ʱ��Ч, ���ڲ��� Actor �� Key */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtActorComponent|SingleManage")
	FString ActorKey;

	/** ���ڲ��� ActorGroup �� Key */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtActorComponent|GroupManage")
	FString MainKey;

	/** ������ ActorGroup �в��� ActorG �� Key */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtActorComponent|GroupManage")
	FString ChildKey;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
