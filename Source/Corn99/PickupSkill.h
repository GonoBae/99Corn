// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupObject.h"
#include "PickupSkill.generated.h"

/**
 * 
 */
UCLASS()
class CORN99_API APickupSkill : public APickupObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Pickup(AActor* Picker) override;

	UFUNCTION(BlueprintCallable)
	void Speedup(AActor* Picker);
};

