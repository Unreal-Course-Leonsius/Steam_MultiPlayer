// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"

//#include "PlatformTrigger.h"
#include "Edit_Tools/HandTools.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"

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

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

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
