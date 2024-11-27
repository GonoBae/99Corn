// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupSkill.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

void APickupSkill::Pickup(AActor* Picker)
{
    picked = true;
    SetActorHiddenInGame(true);
}

void APickupSkill::Speedup(AActor* Picker)
{
    if (picked)
    {
        ACharacter* Character = Cast<ACharacter>(Picker);
        if (Character)
        {
            UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
            float OriginalSpeed = MovementComponent->MaxWalkSpeed;

            MovementComponent->MaxWalkSpeed *= 10.0f;

            FTimerHandle SpeedResetTimerHandle;
            GetWorld()->GetTimerManager().SetTimer(SpeedResetTimerHandle, [MovementComponent, OriginalSpeed]()
                {
                    MovementComponent->MaxWalkSpeed = OriginalSpeed;
                }, 3.0f, false);
        }

    }
    picked = false;
}


void APickupSkill::SpawnWall(AActor* Picker, TSubclassOf<AActor> WallActorClass)
{
    if (picked)
    {
        if (!WallActorClass)
        {
            return;
        }

        ACharacter* Character = Cast<ACharacter>(Picker);
        if (Character)
        {
            FVector CharacterLocation = Character->GetActorLocation();
            FVector CharacterForward = Character->GetActorForwardVector();

            FVector WallLocation = CharacterLocation + CharacterForward * 100.0f;
            FRotator WallRotation = Character->GetActorRotation();

            FActorSpawnParameters SpawnParams;
            AActor* SpawnedWall = GetWorld()->SpawnActor<AActor>(WallActorClass, WallLocation, WallRotation, SpawnParams);

        }
    }
    picked = false;
}