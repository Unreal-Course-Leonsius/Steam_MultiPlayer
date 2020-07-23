// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PuzzlePlatformsGameMode.generated.h"

UCLASS(minimalapi)
class APuzzlePlatformsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APuzzlePlatformsGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	//virtual void BeginPlay() override;

private:

	//static int32 GetObjectReferanceCount(TArray<UObject*>* OutReferredToObjects);
};



