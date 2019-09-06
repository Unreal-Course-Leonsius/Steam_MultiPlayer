// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UServerRow : public UMenuWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ServerButton;


	UFUNCTION()
	void SelectSessionID();
	
protected:

	virtual bool Initialize() override;
	

};
