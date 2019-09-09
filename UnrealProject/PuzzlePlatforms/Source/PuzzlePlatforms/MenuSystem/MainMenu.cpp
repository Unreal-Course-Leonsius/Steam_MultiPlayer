// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

#include "Edit_Tools/HandTools.h"
#include "PuzzlePlatformsGameInstance.h"
#include "ServerRow.h"
#include "TextBlock.h"



UMainMenu::UMainMenu()
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;

	//MainMenu = MainMenuBPClass.Class.DefaulObject();  // If MainMenu is class UUserWidget MainMenu = nullptr;

	ServerRow = ServerRowBPClass.Class;
}

void UMainMenu::SetServerList(TArray<FString> ServerNames)
{
	if (!ensure(ServerList != nullptr)) return;
	if (!ensure(ServerRow != nullptr)) return;

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	ServerList->ClearChildren(); // Clear Items befor we Add new one
	
	uint32 i = 0;
	for (const FString& serverName : ServerNames) // if ServerNames is NULL Loop don't switch on
	{
		UServerRow* ServerWidget = CreateWidget<UServerRow>(World, ServerRow);
		ServerWidget->ServerName->SetText(FText::FromString(serverName));
		ServerWidget->SetUp(this, i);
		++i;
		ServerList->AddChild(ServerWidget);
	}


}


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;


	/// MainMenu
	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	/// JoinMenu
	if (!ensure(CancleButton != nullptr)) return false;
	CancleButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(ConfirmJoinButton != nullptr)) return false;
	ConfirmJoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinToServer);

	
	LOG_S(FString("MainMenu Initilize"));

	/// Instead of it we use Interface
	//PPGameInstance = Cast<UPuzzlePlatformsGameInstance>(GetWorld()->GetGameInstance());

	return true;

}


/// We can also use this virtual function instead of SetGameMode()
/// and the code take into here from SetGameMode()
/// But I think in such way code became less readable
/*void UMainMenu::OnLevelRemovedFromWorld(ULevel * Inlevel, UWorld * InWorld)
{
	Super::OnLevelRemovedFromWorld(Inlevel, InWorld);

	LOG_S(FString("Virtual Function OnLevelRemoveFromWorld"));

	auto World = GetWorld();

	APlayerController* PlayerController = World->GetFirstPlayerController();
	this->RemoveFromViewport();

	/// This code is not work here in UUserWidget
	//this = nullptr;
	//UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	//FSlateApplication::Get().SetFocusToGameViewport();
	///

	FInputModeGameOnly Mode;
	PlayerController->SetInputMode(Mode);
	PlayerController->bShowMouseCursor = false;
}*/

void UMainMenu::HostServer()
{
	LOG_S(FString("Click Event Conneted"));

	/// Instead of it we use Interface
	//PPGameInstance->Host();

	if (GameInstanceInterface != nullptr)
	{
		GameInstanceInterface->Host();
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);

	if (GameInstanceInterface != nullptr)
	{
		GameInstanceInterface->RefreshServerList();
	}

}

void UMainMenu::QuitGame()
{
	auto World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	
	PlayerController->ConsoleCommand("quit");


}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::SetSelectIndex(uint32 index)
{
	SelectIndex = index;
}


void UMainMenu::JoinToServer()
{

	if (SelectIndex.IsSet() && GameInstanceInterface != nullptr)
	{
		LOG_I(SelectIndex.GetValue());
		//UE_LOG(LogTemp, Warning, TEXT("Index = %d"), SelectIndex.GetValue());
		GameInstanceInterface->Join(SelectIndex.GetValue());
	}
	else
	{
		LOG_S(FString("Index not Found"));
	}

}



/// We take out it in MenuWidget class for better Architectur
/*void UMainMenu::SetGameInstanceInterface(IMenuInterface * GameInstanceInterface)
{
	this->GameInstanceInterface = GameInstanceInterface;
}

void UMainMenu::SetUIMode()
{
	this->AddToViewport();

	auto World = GetWorld();

	APlayerController* PlayerController = World->GetFirstPlayerController();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(this->GetCachedWidget());
	PlayerController->SetInputMode(Mode);
	PlayerController->bShowMouseCursor = true;

	/// Sam's Code
	/*	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // without it code works fine

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;*
}

void UMainMenu::SetGameMode()
{
	auto World = GetWorld();

	APlayerController* PlayerController = World->GetFirstPlayerController();
	this->RemoveFromViewport();

	/// This code is not work here in UUserWidget
	//this = nullptr;
	//UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	//FSlateApplication::Get().SetFocusToGameViewport();
	///

	FInputModeGameOnly Mode;
	PlayerController->SetInputMode(Mode);
	PlayerController->bShowMouseCursor = false;
}*/