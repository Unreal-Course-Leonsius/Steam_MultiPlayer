// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

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

	void NetworkError(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

public:


	/// For MainMenu Widget Functions
	UFUNCTION(BlueprintCallable)
		void LoadMainMenu();

	UFUNCTION(BlueprintCallable)
		void InGameLoadMenu();

	UFUNCTION(Exec)
		virtual void Host(FString UserServerName) override;

	UFUNCTION(Exec) // UFUNCTION(Exec) to get command in Editor command with key ~
		virtual void Join(uint32 Index) override;


	/// For InGameMenu
	virtual void ReLoadMainMenu() override;

	/// For Find Session
	virtual void RefreshServerList() override;

private:

	/// we take this code in to MainMenu
	//void SetFocusAndCursorMenuMode();
	//void SetFocuseAndCursorGameMode();

	UEngine* Engine;

private:

	TSubclassOf<class UUserWidget> MainMenu; // Such way MainMenu = PlatformTriggerBPClass.Class Because both of they is TSubclassOf<>(); 
	//class UUserWidget* MainMenu = nullptr;  // Such way MainMenu = PlatformTriggerBPClass.Class.GetDefaultObject(); Because they are different type // But we need TSubclassOf<>() because CreateWidget() function requier it

	TSubclassOf<class UUserWidget> InGameMenu;

	class UMainMenu* MenuLaunch = nullptr;  //it's for to get value which CreateWidget() return

	class UInGameMenu* MenuGame = nullptr;

	APlayerController* PlayerController = nullptr;

private:

	// CallBack functions
	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionComplete(bool Sucess);
	void OnJoinSessionComplete(FName SessinName, EOnJoinSessionCompleteResult::Type Result);


	// Online Session Interface
	void CreateSession();

	void SetLanOrInternet();

public:

	void StartSession();

private:

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	IOnlineSessionPtr SessionInterface;

	FOnlineSessionSettings SessionSettings;

	FString DesiredServerName;

};