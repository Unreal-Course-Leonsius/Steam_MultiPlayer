// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlatformTrigger.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()


public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init();

	/// For MainMenu Widget Functions
	UFUNCTION(BlueprintCallable)
	void LoadMainMenu();

	UFUNCTION(BlueprintCallable)
	void InGameLoadMenu();

	UFUNCTION(BlueprintCallable)
	virtual void Host() override;

	UFUNCTION(BlueprintCallable) // UFUNCTION(Exec) to get command in Editor command with key ~
	virtual void Join(const FString& Address) override;

	/// For InGameMenu
	virtual void ReLoadMainMenu() override;

private:

	/// we take this code in to MainMenu
	//void SetFocusAndCursorMenuMode();
	//void SetFocuseAndCursorGameMode();

private:

	TSubclassOf<class UUserWidget> MainMenu; // Such way MainMenu = PlatformTriggerBPClass.Class Because both of they is TSubclassOf<>(); 
	//class UUserWidget* MainMenu = nullptr;  // Such way MainMenu = PlatformTriggerBPClass.Class.GetDefaultObject(); Because they are different type // But we need TSubclassOf<>() because CreateWidget() function requier it

	TSubclassOf<class UUserWidget> InGameMenu;

	class UMainMenu* MenuLaunch = nullptr;  //it's for to get value which CreateWidget() return

	class UInGameMenu* MenuGame = nullptr;

	APlayerController* PlayerController = nullptr;


};