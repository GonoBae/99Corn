// Copyright Epic Games, Inc. All Rights Reserved.

#include "Corn99GameMode.h"
#include "Corn99Character.h"
#include "UObject/ConstructorHelpers.h"

ACorn99GameMode::ACorn99GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
