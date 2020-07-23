// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatformsGameMode.h"
#include "PuzzlePlatformsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"

#include "Edit_Tools/HandTools.h"


APuzzlePlatformsGameMode::APuzzlePlatformsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));

	//auto Test = PlayerPawnBPClass; // We get here ConstructorHelpers::FClassFinder<APawn> Not actual Class
	//auto Test = PlayerPawnBPClass.Class; // We get here TSubclassOf<APawn> actual Class Pointer

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}



void APuzzlePlatformsGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	

}

/*void APuzzlePlatformsGameMode::BeginPlay()
{
	
	//UEngine* Engine = GetGameInstance()->GetEngine();

	LOG_S(FString("PuzzlePlatformsGameMode"));

	TArray<UObject*> ReferredToObjs;
	GetObjectReferanceCount(&ReferredToObjs);

	for (UObject* Each : ReferredToObjs)
	{
		if (Each)
		{
			//UE_LOG(YourLog, Warning, TEXT("%s"), *Each->GetName());
			LOG_S(FString::Printf(TEXT("Object Reference Name = %s"), *Each->GetName()));
		}
	}

}

int32 APuzzlePlatformsGameMode::GetObjectReferanceCount(TArray<UObject*>* OutReferredToObjects)
{

	TArray<UObject*> ReferredToObjects;				//req outer, ignore archetype, recursive, ignore transient
	FReferenceFinder ObjectReferenceCollector(ReferredToObjects, false, true, true, false);
	//ObjectReferenceCollector.FindReferences(Obj);

	if (OutReferredToObjects)
	{
		OutReferredToObjects->Append(ReferredToObjects);
	}


	return OutReferredToObjects->Num();

}*/
