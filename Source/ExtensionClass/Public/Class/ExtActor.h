// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExtActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorHiddenChanged, bool, Hidden);

UCLASS()
class EXTENSIONCLASS_API AExtActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtActor();

public:

	/**
	* true => 加入到 ActorManager.SingleActorMap
	* false => 加入到 ActorManager.GroupActorMainMap
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtActor|SingleManage")
	bool bIsSingleActor;

	/** 勾选 IsSingleActor 时有效, 用于查找 Actor 的 Key */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtActor|SingleManage")
	FString ActorKey;

	/** 用于查找 ActorGroup 的 Key */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtActor|GroupManage")
	FString MainKey;

	/** 用于在 ActorGroup 中查找 ActorG 的 Key */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtActor|GroupManage")
	FString ChildKey;

	UPROPERTY(BlueprintAssignable)
	FOnActorHiddenChanged OnActorHiddenChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** 自定义隐藏 ExtActor, 会执行 OnActorHiddenChanged 绑定的事件*/
	UFUNCTION(BlueprintCallable)
	void SetExtActorHiddenInGame(bool bNewHidden);

};
