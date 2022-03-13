// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CanvasPanel.h"
#include "ExtCanvasPanel.generated.h"

/**
 * 
 */
UCLASS()
class EXTENSIONCLASS_API UExtCanvasPanel : public UCanvasPanel
{
	GENERATED_BODY()
	
public:

	/** 通过自定义方法设置为 Collapse 时是否把所有 CheckBox 设为不选中*/
	UPROPERTY(EditAnywhere)
	bool bUnCheckChildCheckBox;

	/** 设为不选中时且子组件为 ExtCheckBox 时调用绑定事件 */
	UPROPERTY(EditAnywhere)
	bool CallExtBindWhenUnCheck;

public:

	/** 设置可见性且可以设置子 CheckBox 状态 */
	UFUNCTION(BlueprintCallable)
	void SetExtVisibility(ESlateVisibility InVisibility, bool bUnCheck, bool bExecBindWhenUnCheck);
};
