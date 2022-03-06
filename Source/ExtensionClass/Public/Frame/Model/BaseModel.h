// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Class/ExtObject.h"
#include "BaseModel.generated.h"

/**
 * 
 */
UCLASS()
class EXTENSIONCLASS_API UBaseModel : public UExtObject
{
	GENERATED_BODY()

protected:
	virtual void OnBegin() override;

	virtual void OnEnd() override;
};
