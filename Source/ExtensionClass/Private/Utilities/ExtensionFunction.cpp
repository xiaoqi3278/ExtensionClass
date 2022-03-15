// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/ExtensionFunction.h"

TArray<int32> UExtensionFunction::StringArrayToInt(TArray<FString> StringArray)
{
	TArray<int32> TempIntArr = TArray<int32>();

	for (auto& Itr : StringArray)
	{
		TempIntArr.Add(FCString::Atoi(*Itr));
	}

	return TempIntArr;
}
