// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"



void UMenuWidget::SetUIScreen()
{
	this->AddToViewport();

	SetUIMode();

	/// Sam's Code
	/*	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // without it code works fine

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;*/
}

void UMenuWidget::SetUIMode()
{
	auto World = GetWorld();

	APlayerController* PlayerController = World->GetFirstPlayerController();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(this->TakeWidget());  // Mode.SetWidgetToFocus(this->GetCachedWidget());
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(Mode);
	PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::SetGameMode()
{
	this->RemoveFromViewport();

	auto World = GetWorld();

	APlayerController* PlayerController = World->GetFirstPlayerController();



	/// This code is not work here in UUserWidget
	//this = nullptr;
	//UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	//FSlateApplication::Get().SetFocusToGameViewport();
	///

	FInputModeGameOnly Mode;
	PlayerController->SetInputMode(Mode);
	PlayerController->bShowMouseCursor = false;
}

void UMenuWidget::SetGameInstanceInterface(IMenuInterface * GameInstanceInterface)
{
	this->GameInstanceInterface = GameInstanceInterface;
}

