#pragma once

#include "CoreMinimal.h"
#include "PickupObject.h"
#include "Net/UnrealNetwork.h" 
#include "PickupWeapon.generated.h"

/**
 *
 */
UCLASS()
class CORN99_API APickupWeapon : public APickupObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    virtual void Pickup(AActor* Picker) override;

    UFUNCTION(NetMulticast, Reliable)
    void MulticastDrawDebugCone(const FVector& Origin, const FVector& Direction, float ConeAngle, float MaxDistance, const FColor& CloseRangeColor, const FColor& FarRangeColor);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable)
    void FindActorsInCone(
        const FVector& Origin,
        const FVector& Direction,
        float ConeAngle,
        float MaxDistance,
        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes,
        TArray<AActor*> IgnoreActors,
        TArray<AActor*>& CloseRangeActors,
        TArray<AActor*>& FarRangeActors,
        bool bDrawDebug
    );
};
