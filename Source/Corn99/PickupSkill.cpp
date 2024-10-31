// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupSkill.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

void APickupSkill::Pickup(AActor* Picker)
{
    active = true;
    SetActorHiddenInGame(true);


}
void APickupSkill::Speedup(AActor* Picker)
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
