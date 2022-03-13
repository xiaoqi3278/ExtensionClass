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

	/** ͨ���Զ��巽������Ϊ Collapse ʱ�Ƿ������ CheckBox ��Ϊ��ѡ��*/
	UPROPERTY(EditAnywhere)
	bool bUnCheckChildCheckBox;

	/** ��Ϊ��ѡ��ʱ�������Ϊ ExtCheckBox ʱ���ð��¼� */
	UPROPERTY(EditAnywhere)
	bool CallExtBindWhenUnCheck;

public:

	/** ���ÿɼ����ҿ��������� CheckBox ״̬ */
	UFUNCTION(BlueprintCallable)
	void SetExtVisibility(ESlateVisibility InVisibility, bool bUnCheck, bool bExecBindWhenUnCheck);
};
