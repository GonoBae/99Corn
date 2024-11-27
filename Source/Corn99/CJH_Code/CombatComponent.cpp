// Fill out your copyright notice in the Description page of Project Settings.


#include "Corn99/CJH_Code/CombatComponent.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();	
}



#pragma region test
void UCombatComponent::CallFireRPC()
{
    if (GetOwner()->HasAuthority())
    {
        Server_HandleFire();
    }
    else
    {
        Server_HandleFire();
    }
}


void UCombatComponent::CallHitRPC(FVector ImpactPoint)
{
    Server_HandleHit(ImpactPoint);
}


void UCombatComponent::Multicast_PlayExplosion_Implementation(FVector ImpactPoint)
{
    //폭발 효과 재생
}

void UCombatComponent::Server_HandleHit_Implementation(FVector ImpactPoint)
{
    Multicast_PlayExplosion(ImpactPoint);
}

bool UCombatComponent::Server_HandleHit_Validate(FVector ImpactPoint)
{
    return true;
}

void UCombatComponent::Server_HandleFire_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("Server: Weapon fired!"));
}
bool UCombatComponent::Server_HandleFire_Validate()
{
    return true;
}
void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


#pragma endregion

