// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupObject.h"

// Sets default values
APickupObject::APickupObject()
{
	PrimaryActorTick.bCanEverTick = true;

	active = false;

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
	active = true;
	SetActorHiddenInGame(true);
	
	AActor* PlayerActor = Cast<AActor>(Picker);
	if (PlayerActor)
	{

		SetActorHiddenInGame(false);
		
	}
	
}

bool APickupObject::GetActive()
{
	return active;
}