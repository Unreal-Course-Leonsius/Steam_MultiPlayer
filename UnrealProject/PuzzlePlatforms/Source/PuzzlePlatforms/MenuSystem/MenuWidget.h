// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	IMenuInterface* GameInstanceInterface = nullptr;
	
public:

	void SetUIScreen();
	void SetUIMode();
	void SetGameMode();
	
	void SetGameInstanceInterface(IMenuInterface* GameInstaceInterface);

	IMenuInterface* GetGameInstanceInterface();
};
