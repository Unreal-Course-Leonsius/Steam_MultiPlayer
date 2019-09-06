// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"

#include "Edit_Tools/HandTools.h"
#include "TextBlock.h"
#include "Components/Button.h"


/*bool UServerRow::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(ServerButton != nullptr)) return false;
	ServerButton->OnClicked.AddDynamic(this, &UServerRow::SelectSessionID);

	return true;
}

void UServerRow::SelectSessionID()
{
	SetUIScreen();
	LOG_S(FString("ServerRow Click Button"));
	if (GameInstanceInterface)
	{
		GameInstanceInterface->Join(ServerName->GetText().ToString());
	}
}*/