// Fill out your copyright notice in the Description page of Project Settings.


#include "DevelopmentUtilities/ExtCheatManager.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Manager/CheckBoxManager.h"
#include "FunctionLibrary/CheckBoxLibrary.h"
#include "Utilities/ExtLog.h"
#include "Frame/Utilities/ModelLibrary.h"
#include "Frame/Model/BaseModel.h"
#include "Frame/Manager/ModelManager.h"
#include "Frame/Utilities/ModelTree.h"
#include "Frame/Manager/WidgetManager.h"
#include "Frame/Utilities/WidgetLibrary.h"
#include "Frame/ExtGameInstance.h"
#include "CurrencyCamera/Public/PlayerCharacterCamera.h"

void UExtCheatManager::InitCheatManager()
{
	UE_LOG(ExtensionLog, Log, TEXT("Create ExtCheatManager"));

	
}

void UExtCheatManager::ShowAllExtCheckBoxMainKey()
{
	TArray<FString> MainKeyArr = UCheckBoxLibrary::GetMainKeyArray(this);

	UE_LOG(ExtensionLog, Log, TEXT("==========================================MainKeyArrayStart=========================================="));

	for (auto Itr : MainKeyArr)
		UE_LOG(ExtensionLog, Log, TEXT("%s"), *Itr);

	UE_LOG(ExtensionLog, Log, TEXT("===========================================MainKeyArrayEnd==========================================="));
}

void UExtCheatManager::ShowAllExtCheckBoxChildKeyOfGroup(FString MainKey)
{
	TArray<FString> ChildKeyArr = UCheckBoxLibrary::GetChildKeyArray(this, MainKey);

	UE_LOG(ExtensionLog, Log, TEXT("==============================================MainKey: %s=========================================="), *MainKey);
	UE_LOG(ExtensionLog, Log, TEXT("==========================================ChildKeyArrayStart=========================================="));

	for (auto Itr : ChildKeyArr)
		UE_LOG(ExtensionLog, Log, TEXT("%s"), *Itr);

	UE_LOG(ExtensionLog, Log, TEXT("===========================================ChildKeyArrayEnd=========================================="));
	UE_LOG(ExtensionLog, Log, TEXT("===========================================ChildKeyArrayEnd=========================================="));
}

void UExtCheatManager::ShowAllModelName()
{
	TArray<UBaseModel*> ModelArr = UModelLibrary::GetAllModel(this);

	UE_LOG(ExtensionLog, Log, TEXT("==============================================ModelStart============================================="));

	for (auto& Itr : ModelArr)
		UE_LOG(ExtensionLog, Log, TEXT("%s"), *Itr->GetName())

	UE_LOG(ExtensionLog, Log, TEXT("===============================================ModelEnd=============================================="));
}

void UExtCheatManager::ShowAllModelNum()
{
	UModelTree* ModelTree = UModelLibrary::GetModelManager(this)->ModelTree;

	UE_LOG(ExtensionLog, Log, TEXT("The Num Of All Model: %d"), ModelTree->GetAllNode().Num());
}

void UExtCheatManager::ShowAllManagedWidget()
{
	TArray<FString> WidgetKeyArray = UWidgetLibrary::GetAllWidgetKey(this);

	UE_LOG(ExtensionLog, Log, TEXT("============================================WidgetKeyStart==========================================="));

	for(auto& Itr : WidgetKeyArray)
		UE_LOG(ExtensionLog, Log, TEXT("%s"), *Itr)

	UE_LOG(ExtensionLog, Log, TEXT("=============================================WidgetKeyEnd============================================"));
}

void UExtCheatManager::SetCurrentPoint()
{
	UExtGameInstance* GameInstance = Cast<UExtGameInstance>(UGameplayStatics::GetGameInstance(this));
	APlayerCharacterCamera* Camera = Cast<APlayerCharacterCamera>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (GameInstance != nullptr)
	{
		FString FilePath = UKismetSystemLibrary::GetProjectDirectory() + "Config/Point.json";
		FString FileContent;

		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		if (PlatformFile.FileExists(*FilePath))
		{
			FFileHelper::LoadFileToString(FileContent, *FilePath);

			TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<TCHAR>::Create(FileContent);
			TSharedPtr<FJsonObject> JsonObject;
			FJsonSerializer::Deserialize(JsonReader, JsonObject);
			TSharedPtr<FJsonObject> PointJsonObject = JsonObject->GetObjectField(GameInstance->CurrentPointKey);
			if (PointJsonObject != nullptr)
			{
				UE_LOG(ExtensionLog, Warning, TEXT("%s"), *GameInstance->CurrentPointKey);
				UE_LOG(ExtensionLog, Warning, TEXT("%s"), *Camera->GetActorLocation().ToString());
				UE_LOG(ExtensionLog, Warning, TEXT("%s"), *Camera->GetActorRotation().ToString());
				UE_LOG(ExtensionLog, Warning, TEXT("%f"), Camera->NativeArmLength);

				PointJsonObject->GetObjectField("location")->SetNumberField("x", Camera->GetActorLocation().X);
				PointJsonObject->GetObjectField("location")->SetNumberField("y", Camera->GetActorLocation().Y);
				PointJsonObject->GetObjectField("location")->SetNumberField("z", Camera->GetActorLocation().Z);

				PointJsonObject->GetObjectField("rotation")->SetNumberField("pitch", Camera->GetActorRotation().Pitch);
				PointJsonObject->GetObjectField("rotation")->SetNumberField("yaw", Camera->GetActorRotation().Yaw);
				PointJsonObject->GetObjectField("rotation")->SetNumberField("roll", Camera->GetActorRotation().Roll);

				PointJsonObject->SetNumberField("armLength", Camera->NativeArmLength);

				FString JsonString;
				TSharedRef<TJsonWriter<TCHAR>>  JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonString);
				FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
				FFileHelper::SaveStringToFile(JsonString, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_None);

				GameInstance->ReadPointFile();
			}
		}
		else
		{
			UE_LOG(ExtensionLog, Warning, TEXT("Read File Error!"));
			return;
		}
		//UE_LOG(ExtensionLog, Warning, TEXT("%s"), *FileContent);
	}
}

void UExtCheatManager::ShowTest()
{
	UModelTree* Test = UModelLibrary::GetModelManager(this)->ModelTree;

	UE_LOG(ExtensionLog, Log, TEXT("=============================================ShowTestStart==========================================="));

	for (auto& Itr : Test->GetAllNode())
		UE_LOG(ExtensionLog, Log, TEXT("%s"), *Itr->Model->GetName());

	UE_LOG(ExtensionLog, Log, TEXT("==============================================ShowTestEnd============================================"));
}
