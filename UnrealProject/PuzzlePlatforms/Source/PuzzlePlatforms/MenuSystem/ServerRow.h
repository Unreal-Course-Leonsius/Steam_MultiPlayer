// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "MenuWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UServerRow : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HostUserName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ConnectionFraction;

	UPROPERTY(meta = (BindWidget))
	class UButton* RowButton;

	UPROPERTY(BlueprintReadOnly)
	bool IsSelect = false;

protected:

	UFUNCTION()
	void ClickedEvent();

private:

	class UMainMenu* Parent;
	uint32 Index;

public:

	void SetUp(class UMainMenu* Parent, uint32 Index);


};
