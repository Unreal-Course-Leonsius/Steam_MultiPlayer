// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"

#include "PuzzlePlatformsGameInstance.h"
#include "Edit_Tools/HandTools.h"
#include "Player/PuzzlePlatformPlayerState.h"
#include "Player/PuzzlePlatformPlayerController.h"

#include "Engine/Engine.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"



ALobbyGameMode::ALobbyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//PlayerStateClass = APuzzlePlatformPlayerState::StaticClass();
	//PlayerControllerClass = APuzzlePlatformPlayerController::StaticClass();
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	++NumberOfPlayers;

	if ((NewPlayer != nullptr) & (NumberOfPlayers >= 2))
	{
		//GetWorldTimerManager().SetTimer(GameStart, this, &ALobbyGameMode::StartGame, 10.0);
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

void ALobbyGameMode::StartGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/PuzzlePlatforms/Maps/Game?listen");

	// Get GameInstance
	auto GameInstance = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance());
	GameInstance->StartSession();

	GetWorldTimerManager().ClearTimer(GameStart);

	// Get Print on the Screen
	UEngine* Engine = GetGameInstance()->GetEngine();
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));
}
