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
	* true => 加入到 ActorManager.SingleActorMap
	* false => 加入到 ActorManager.GroupActorMainMap
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtActorComponent|SingleManage")
	bool bIsSingleActor;

	/** 勾选 IsSingleActor 时有效, 用于查找 Actor 的 Key */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtActorComponent|SingleManage")
	FString ActorKey;

	/** 用于查找 ActorGroup 的 Key */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtActorComponent|GroupManage")
	FString MainKey;

	/** 用于在 ActorGroup 中查找 ActorG 的 Key */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtActorComponent|GroupManage")
	FString ChildKey;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
