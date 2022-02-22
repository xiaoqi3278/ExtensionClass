// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Frame/Manager/WidgetManager.h"

#include "WidgetLibrary.generated.h"

/**
 * Widget ������
 * 
 * �ṩ Widget ��غ���
 */

class UWidgetManager;
class UExtUserWidget;

UCLASS()
class EXTENSIONCLASS_API UWidgetLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** ��ȡ WidgetManager */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static UWidgetManager* GetWidgetManager(UObject* WorldContextObject);

	/** ���� Widget */
	//UFUNCTION(BlueprintCallable, Category = "ExtensionClass|Frame|WidgetLibrary")
	//static void CreateWidget();

	/**
	* ���� WidgetManager �� WidgetMap ��Ӧ��һ�� UExtUserWidget
	* 
	* @param WidgetKey			�������ҵļ�
	* 
	* @return	���ҵ��� ExtUserWidget����Ϊ nullptr
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static UExtUserWidget* GetWidget(UObject* WorldContextObject, FString WidgetKey);

	/**
	* ���� WidgetManager �� ĳ�� WidgetGroup ��Ӧ��һ�� ExtUserWidget
	*
	* @param WidgetMainKey		�������� WidgetGroup �ļ�
	* @param WidgetChildKey		�������� WidgetGroup �ж�Ӧ��һ�� ExtUserWidget �ļ�
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static UExtUserWidget* GetOneWidgetOfGroup(UObject* WorldContextObject, FString WidgetMainKey, FString WidgetChildKey);

	/**
	* ���� WidgetManager �ж�Ӧ�� FWidgetGroup
	* 
	* @param WidgetMainKey		�������ҵļ�
	* 
	* @return	���ҵ��� WidgetGroup����ΪĬ�Ϲ���Ķ���
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static FWidgetGroup GetWidgetGroup(UObject* WorldContextObject, FString WidgetMainKey);

	/**
	* ���� WidgetManager �ж�Ӧ�� һ�� WidgetGroup�����е� ExtUserWidget
	* 
	* @param WidgetMainKey		�������ҵļ�
	* 
	* @return	���ҵ��� ExtUserWidget ���飬��Ϊ��
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static TArray<UExtUserWidget*> GetWidgetArray(UObject* WorldContextObject, FString WidgetMainKey);

	/** 
	* �Ƴ� WidgetManager �� WidgetMap ��Ӧ��ĳһ�� ExtUserWidget
	* 
	* @param WidgetKey			�������ҵļ�
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static void RemoveWidget(UObject* WorldContextObject, FString WidgetKey);

	/**
	* �Ƴ� WidgetManager �� WidgetMainMap �ж�Ӧ�� WidgetGroup �е�ĳһ�� ExtUserWidget
	* 
	* @param WidgetMainKey		�������� WidgetGroup �ļ�
	* @param WidgetChildKey		�������� WidgetGroup �ж�Ӧ��һ�� ExtUserWidget �ļ�
	*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ExtensionClass|Frame|WidgetLibrary")
	static void RemoveOneOfGroupWidget(UObject* WorldContextObject, FString WidgetMainKey, FString WidgetChildKey);
};
