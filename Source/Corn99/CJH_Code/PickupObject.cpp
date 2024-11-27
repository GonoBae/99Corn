// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupObject.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APickupObject::APickupObject()
{
	PrimaryActorTick.bCanEverTick = true;

	picked = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh;
}

void APickupObject::BeginPlay()
{
	
}

void APickupObject::Tick(float DeltaTime)
{

}

void APickupObject::Pickup(AActor* Picker)
{

	if (picked == false) 
	{
		picked = true;
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);

	}
}

bool APickupObject::GetIsPicked()
{
	return picked;
}