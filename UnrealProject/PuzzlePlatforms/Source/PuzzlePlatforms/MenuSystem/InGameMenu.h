// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Blueprint/UserWidget.h"
//#include "Components/ActorComponent.h"
#include "MenuWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(meta = (BindWidget))
	class UButton* CancleButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

protected:

	virtual bool Initialize() override;

protected:

	UFUNCTION()
	void BackInGame();

	UFUNCTION()
	void ExitGame();
/*
protected:

	class UInputComponent* InputComponent;

public:

	void SetInputComponent();
	
	void PauseGame();

private:

	class UPuzzlePlatformsGameInstance* PPGameInstance = nullptr;
	*/
};
