// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXTENSIONCLASS_API UFloorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFloorComponent();
	
	/** 楼栋名称 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|FloorComponent")
	FString BuildingName;

	/** 楼层数 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|FloorComponent")
	int32 FloorNum;

	/** 楼层初始位置 */
	UPROPERTY(BlueprintReadOnly)
	FVector InitLocation;

	/** 楼层是否是显示状态 */
	UPROPERTY(BlueprintReadWrite)
	bool bIsShow;

	/** 楼层移动过后的位置 */
	UPROPERTY(BlueprintReadWrite)
	FVector SecondLocation;

	/** 楼层初始旋转 */
	UPROPERTY(BlueprintReadOnly)
	FRotator InitRotation;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
