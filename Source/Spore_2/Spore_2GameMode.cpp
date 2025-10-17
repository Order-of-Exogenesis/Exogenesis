// Copyright Epic Games, Inc. All Rights Reserved.

#include "Spore_2GameMode.h"
#include "Spore_2PlayerController.h"
#include "Spore_2Character.h"
#include "UObject/ConstructorHelpers.h"

ASpore_2GameMode::ASpore_2GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASpore_2PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}