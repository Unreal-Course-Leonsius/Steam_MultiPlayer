// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"
#include "Components/Button.h"
#include "PuzzlePlatformsGameInstance.h"
#include "Edit_Tools/HandTools.h"


bool UInGameMenu::Initialize()
{

	bool Success = Super::Initialize();
	if (!Success) return false;

	LOG_S(FString("InGameMenu Initilize"));

	if (!ensure(CancleButton != nullptr)) return false;
	CancleButton->OnClicked.AddDynamic(this, &UInGameMenu::BackInGame);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::ExitGame);

	return true;
}

void UInGameMenu::BackInGame()
{
	//this->RemoveFromViewport();

	this->SetGameMode();
	
}

void UInGameMenu::ExitGame()
{
	//this->RemoveFromViewport();
	//this->SetUIMode();
	this->SetGameMode();
	if (GameInstanceInterface)
	{
		GameInstanceInterface->ReLoadMainMenu();
	}
}



/*
void UInGameMenu::SetInputComponent()
{
	auto World = GetWorld();

	APlayerController* PlayerController = World->GetFirstPlayerController();

	InputComponent = PlayerController->FindComponentByClass<UInputComponent>();

	LOG_S(FString("SetInputComponent"));

	//InputComponentt = FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		/// Bind Input axis
		InputComponent->BindAction("Pause", IE_Pressed, this, &UInGameMenu::PauseGame); // qualify class name 1
		//InputComponentt->BindAction("Grabb", IE_Released, this, &UGrabberr::Releasedd);

		LOG_S(FString("InputComponent"));
	}
}

void UInGameMenu::PauseGame()
{
	LOG_S(FString("PauseGame-Start"));

	PPGameInstance = Cast<UPuzzlePlatformsGameInstance>(GetWorld()->GetGameInstance());
	if (!ensure(PPGameInstance != nullptr)) return;

	PPGameInstance->InGameLoadMenu();



}
*/