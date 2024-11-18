// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORN99_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

	UFUNCTION(BlueprintCallable, Category = "Weapon|RPC")
	void CallFireRPC();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_HandleFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon|RPC")
	void CallHitRPC(FVector ImpactPoint);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_HandleHit(FVector ImpactPoint);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlayExplosion(FVector ImpactPoint);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
