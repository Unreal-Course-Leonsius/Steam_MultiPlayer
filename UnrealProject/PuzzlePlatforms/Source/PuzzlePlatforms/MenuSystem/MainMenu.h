// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
//#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

		/// Don't work in this Section

public:

	UMainMenu();

private:

	TSubclassOf<class UUserWidget> ServerRow;
	//class UServerRow* ServerWidget = nullptr;

	TOptional<uint32> SelectIndex;

public:

	void SetServerList(TArray<FString> ServerNames);

	void SetSelectIndex(uint32 index);

protected:

	virtual bool Initialize() override;

	/// We can also use this virtual function instead of SetGameMode()
	//virtual void OnLevelRemovedFromWorld(ULevel* Inlevel, UWorld* InWorld) override;

	// MainMenu
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void QuitGame();

	// JoinMenu
	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void JoinToServer();


public:

	/// Blueprint Buttons
	// MainMenu
	UPROPERTY(meta = (BindWidget))
		class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitButton;

	// JoinMenu
	UPROPERTY(meta = (BindWidget))
		class UButton* CancleButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* ConfirmJoinButton;


	/// Blueprint Widgets
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
		class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
		class UPanelWidget* ServerList;

	/*UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* IPAddressField;*/


	/// We all take it out in MenuWidget class for better Architectur
	/*private:

		/// Instead of it we use Interface
		//class UPuzzlePlatformsGameInstance* PPGameInstance = nullptr;

		IMenuInterface* GameInstanceInterface = nullptr;

	public:  // Works only public section

		void SetGameInstanceInterface(IMenuInterface* GameInstaceInterface);

		void SetUIMode();
		void SetGameMode();*/

};