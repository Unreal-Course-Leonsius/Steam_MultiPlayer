// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformPlayerState.h"




void APuzzlePlatformPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	APuzzlePlatformPlayerState* PS = Cast<APuzzlePlatformPlayerState>(PlayerState);
	if (PS)
	{
		PS->OwnerPlayerName = this->OwnerPlayerName;
	}
}

void APuzzlePlatformPlayerState::OverrideWith(APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);

	APuzzlePlatformPlayerState* PS = Cast<APuzzlePlatformPlayerState>(PlayerState);
	if (PS)
	{
		this->OwnerPlayerName = PS->OwnerPlayerName;
	}

}

void APuzzlePlatformPlayerState::SetOwnPlayerName(FString name)
{
	SetPlayerName(name);
	OwnerPlayerName = name;
}
