// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"
//#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

//#include "PlatformTrigger.h"
#include "Edit_Tools/HandTools.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"


#define OUT
const static FName SESSION_NAME = TEXT("My Session Game");

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{

	LOG_S(FString("GameInstance Constructor"));

	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (!ensure(MainMenuBPClass.Class != nullptr)) return;

	//MainMenu = MainMenuBPClass.Class.DefaulObject();  // If MainMenu is class UUserWidget MainMenu = nullptr;

	MainMenu = MainMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;

	LOG_S(FString::Printf(TEXT("Found Class: %s"), *MainMenu->GetName()));

	InGameMenu = InGameMenuBPClass.Class;

	/*ConstructorHelpers::FClassFinder<APlatformTrigger> PlatformTriggerBPClass(TEXT("/Game/PuzzlePlatforms/BP_PlatformTrigger"));
	if (!ensure(PlatformTriggerBPClass.Class != nullptr)) return;

	LOG_S(FString::Printf(TEXT("Found Class: %s"), *PlatformTriggerBPClass.Class->GetName()));*/
}

void UPuzzlePlatformsGameInstance::Init()
{
	
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();

	if (Subsystem != nullptr)
	{
		LOG_S(FString::Printf(TEXT("Found Subsystem %s"), *Subsystem->GetSubsystemName().ToString()));
		SessionInterface = Subsystem->GetSessionInterface();  // IOnlineSessionPtr is typedef of TSharePtr pointer
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnJoinSessionComplete);
			//LOG_S(FString::Printf(TEXT("Session Iterface Name = %s"), *SessionInterface.ToSharedR)

		}
	}
	else
	{
		LOG_S(FString("Not Found Subsystem"));
	}

}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	if (!ensure(MainMenu != nullptr)) return;
	MenuLaunch = CreateWidget<UMainMenu>(this, MainMenu);

	if (!ensure(MenuLaunch != nullptr)) return;

	/// we take out this code in MainMenu
	//Menu->AddToViewport();
	
	//SetFocusAndCursorMenuMode();
	///

	MenuLaunch->SetUIScreen();

	MenuLaunch->SetGameInstanceInterface(this);
	
}

void UPuzzlePlatformsGameInstance::InGameLoadMenu()
{
	if (!ensure(InGameMenu != nullptr)) return;
	MenuGame = CreateWidget<UInGameMenu>(this, InGameMenu);

	if (!ensure(MenuGame != nullptr)) return;
	MenuGame->SetUIScreen();

	MenuGame->SetGameInstanceInterface(this);
}



void UPuzzlePlatformsGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			//LOG_S(FString("DestroySession_Start"));
			SessionInterface->DestroySession(SESSION_NAME);
			//LOG_S(FString("DestroySession_End"));
		}
		else
		{
			this->CreateSession();
		}
	}

}

void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{

	if (!Success)
	{
		LOG_S(FString("Could not Create Session"));
		return;
	}

	/// we take out this code in MainMenu
	//SetFocuseAndCursorGameMode();
	///

	MenuLaunch->SetGameMode();

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));
	LOG_S(FString("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		//LOG_S(FString("DestroySessionDelegate_Start"));
		this->CreateSession();
		//LOG_S(FString("DestroySessionDelegate_End"));
	}
}

void UPuzzlePlatformsGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = true;
	if (SessionSearch.IsValid())
	{
		int32 Time = int32(GetWorld()->GetTimeSeconds());
		LOG_S(FString("Star Find Session"));
		LOG_I(Time);
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}

}

void UPuzzlePlatformsGameInstance::OnFindSessionComplete(bool Sucess)
{
	if (Sucess && SessionSearch.IsValid())
	{
		int32 Time = int32(GetWorld()->GetTimeSeconds());
		LOG_S(FString("Finsh Find Session"));
		TArray<FString> ServerNames;
		for (const FOnlineSessionSearchResult& searchResult : SessionSearch->SearchResults)
		{
			LOG_S(FString::Printf(TEXT("Session Name = %s"), *searchResult.GetSessionIdStr()));
			ServerNames.Add(searchResult.GetSessionIdStr());
		}
		
		LOG_I(Time);

		if (!ensure(MenuLaunch != nullptr)) return;
		MenuLaunch->SetServerList(ServerNames);

	}

	/// Sucess in every case = true if this function (OnFindSessionComplete()) is completed, that's why we don't need [ else{} ]
	/*else
	{
		int32 Time = int32(GetWorld()->GetTimeSeconds());
		LOG_S(FString("Finsh Find Session FAIL"));
		for (auto& searchResult : SessionSearch->SearchResults)
		{
			LOG_S(FString::Printf(TEXT("Session Name = %s"), *searchResult.GetSessionIdStr()));
		}
		LOG_I(Time);
	}*/
	
	
}



void UPuzzlePlatformsGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.NumPublicConnections = 2;
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings); // CallBack OnCreateSessionComplete(); 
	}

}
 

void UPuzzlePlatformsGameInstance::Join(uint32 Index)
{
	if (!SessionInterface.IsValid() && !SessionSearch.IsValid()) return;

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);

}


void UPuzzlePlatformsGameInstance::OnJoinSessionComplete(FName SessinName, EOnJoinSessionCompleteResult::Type Result)
{
	LOG_S(FString("JoinSessionComplete Function"));
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	FString Address;

	if (!SessionInterface.IsValid()) return;
	bool success = SessionInterface->GetResolvedConnectString(SESSION_NAME, OUT Address);

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);

	MenuLaunch->SetGameMode();
}

void UPuzzlePlatformsGameInstance::ReLoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMneu", ETravelType::TRAVEL_Absolute);
}




/*void UPuzzlePlatformsGameInstance::SetFocusAndCursorMenuMode()
{
	auto World = GetWorld();

	APlayerController* PlayerController = World->GetFirstPlayerController();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(Menu->GetCachedWidget());
	PlayerController->SetInputMode(Mode);
	PlayerController->bShowMouseCursor = true;

	/// Sam's Code
	/**	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // without it code works fine

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;**

}*/

/*void UPuzzlePlatformsGameInstance::SetFocuseAndCursorGameMode()
{
	auto World = GetWorld();

	APlayerController* PlayerController = World->GetFirstPlayerController();
	Menu->RemoveFromViewport();
	Menu = nullptr;
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	//FSlateApplication::Get().SetFocusToGameViewport();
	PlayerController->bShowMouseCursor = false;
}*/
