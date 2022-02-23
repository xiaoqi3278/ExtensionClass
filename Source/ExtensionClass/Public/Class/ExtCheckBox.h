// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CheckBox.h"
#include "ExtCheckBox.generated.h"

/**
 * 拓展自 UCheckBox
 * 
 */

class ACheckBoxManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FExtOnCheckStateChanged, bool, bIsChecked, int32, Index);

UCLASS()
class EXTENSIONCLASS_API UExtCheckBox : public UCheckBox
{
	GENERATED_BODY()
	
public:
	/** 用于查找当前 ExtCheckBox 所在组的键 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtCheckBox")
	FString MainKey;

	/** 用于查找当前 ExtCheckBox 的键 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtCheckBox")
	FString ChildKey;

	/** 当前 ExtCheckBox 的标识 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExtensionClass|ExtCheckBox")
	int32 Index;

	/** 当前 ExtCheckBox 选中状态发生改变时调用 */
	UPROPERTY(BlueprintAssignable, Category = "ExtensionClass|ExtCheckBox|Event")
	FExtOnCheckStateChanged OnExtCheckStateChanged;

private:
	/** 根据自定规则自动生成 Index */
	UPROPERTY(EditAnywhere, Category = "ExtensionClass|Utilities")
	FString GenerateIndex;

	/** 是否加入到 CheckBoxManager 中进行管理 */
	UPROPERTY(EditAnywhere, Category = "ExtensionClass|Control")
	bool bDontManage;

	/** 已选中时无法取消选中状态 */
	UPROPERTY(EditAnywhere, Category = "ExtensionClass|Control")
	bool bAlwaysChecked;

	/** 重复点击已选中按钮时是否执行绑定事件 */
	UPROPERTY(EditAnywhere, category = "ExtensionClass|Control")
	bool bExecuteBindOnReChecked;

	/** CheckBox 管理类 */
	UPROPERTY()
	ACheckBoxManager* Manager;

	/** 是否是需要初始化 */
	UPROPERTY()
	bool bIsInitial = true;

public:
	/** Applies all properties to the live slot if possible. */
	virtual void SynchronizeProperties() override;

public:
	/**
	 * 点击当前 ExtCheckBox 时调用
	 * 
	 * @param bIsChecked 点击后当前 ExtCheckBox 的状态
	 */
	UFUNCTION()
	void OnClick(bool bIsChecked);

	/** 设置当前 ExtCheckBox 的选中状态，会调用 OnExtCheckStateChanged 绑定的事件 */
	UFUNCTION(BlueprintCallable)
	void SetExtCheckedState(ECheckBoxState ExtCheckedState);

private:
	/** ExtCheckBox 初始化 */
	UFUNCTION()
	virtual void OnInitialized();

	/** 根据输入的字符自动生成 Index */
	UFUNCTION()
	void GenerateToIndex(FString GenerateKey);
};

