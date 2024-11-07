// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Corn99/PickupSystem.h"
#include "PickupObject.generated.h"


UCLASS()
class CORN99_API APickupObject : public AActor, public IPickupSystem
{
	GENERATED_BODY()
	
public:	
	APickupObject();

	virtual void Tick(float DeltaTime) override;

	void Pickup(AActor* Picker) override;

	UFUNCTION(BlueprintCallable)
	bool GetActive();

protected:
	virtual void BeginPlay() override;
	UPROPERTY()
	bool active;

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* mesh;
};
