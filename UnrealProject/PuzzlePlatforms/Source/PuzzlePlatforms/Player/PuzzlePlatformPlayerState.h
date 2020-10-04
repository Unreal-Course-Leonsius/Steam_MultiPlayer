// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PuzzlePlatformPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API APuzzlePlatformPlayerState : public APlayerState
{
	GENERATED_BODY()

public:


	virtual void CopyProperties(APlayerState* PlayerState) override;

	virtual void OverrideWith(APlayerState* PlayerState) override;

	UPROPERTY(BlueprintReadOnly, Category = "PlayerName")
	FString OwnerPlayerName;

	UFUNCTION(BlueprintCallable, Category = "PlayerName")
	void SetOwnPlayerName(FString name);

	UFUNCTION(BlueprintCallable, Category = "PlayerName")
	FString GetOwnPlayerName() { return OwnerPlayerName; }
	
	
	
};
