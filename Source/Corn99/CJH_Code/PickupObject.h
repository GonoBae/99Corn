// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Corn99/CJH_Code/PickupSystem.h"
#include "PickupObject.generated.h"


UCLASS()
class CORN99_API APickupObject : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupObject();

	virtual void Tick(float DeltaTime) override;

	virtual void Pickup(AActor* Picker);

	UFUNCTION(BlueprintCallable)
	bool GetIsPicked();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool itemUse;

protected:
	virtual void BeginPlay() override;
	UPROPERTY()
	bool picked;

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* mesh;
};
