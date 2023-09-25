// Copyright Epic Games, Inc. All Rights Reserved.

#include "LA_PrototypeGameMode.h"
#include "LA_PrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALA_PrototypeGameMode::ALA_PrototypeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
