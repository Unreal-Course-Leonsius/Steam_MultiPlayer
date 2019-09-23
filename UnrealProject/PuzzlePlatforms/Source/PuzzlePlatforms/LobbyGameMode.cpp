// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"

#include "Edit_Tools/HandTools.h"

#include "Engine/Engine.h"



void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	++NumberOfPlayers;

	if ((NewPlayer != nullptr) & (NumberOfPlayers >= 3))
	{
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		
		UEngine* Engine = GetGameInstance()->GetEngine();
		if (!ensure(Engine != nullptr)) return;

		Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));
		bUseSeamlessTravel = true;
		World->ServerTravel("/Game/PuzzlePlatforms/Maps/Game?listen");
		
	}
	else
	{
		LOG_S(FString("PostLogin Function GameMode"));
	}


}

void ALobbyGameMode::Logout(AController * Exiting)
{
	Super::Logout(Exiting);
	--NumberOfPlayers;
}
