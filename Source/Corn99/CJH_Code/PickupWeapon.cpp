// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupWeapon.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"  

void APickupWeapon::Pickup(AActor* Picker)
{
    Super::Pickup(Picker);

    ACharacter* Character = Cast<ACharacter>(Picker);
    if (Character)
    {
        USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
        if (CharacterMesh)
        {
            FName HandSocketName = TEXT("HandSocket"); 
            AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocketName);
        }
    }
}


void APickupWeapon::FindActorsInCone(
    const FVector& Origin,
    const FVector& Direction,
    float ConeAngle,
    float MaxDistance,
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes,
    TArray<AActor*> IgnoreActors,
    TArray<AActor*>& CloseRangeActors,
    TArray<AActor*>& FarRangeActors,
    bool bDrawDebug
)
{
    TArray<FHitResult> HitResults;

    UKismetSystemLibrary::SphereTraceMultiForObjects(
        GetWorld(),
        Origin,
        Origin + Direction * MaxDistance,
        MaxDistance,
        ObjectTypes,
        false,
        IgnoreActors,
        EDrawDebugTrace::None,
        HitResults,
        true
    );

    float HalfConeAngleRadians = FMath::DegreesToRadians(ConeAngle / 2);
    float HalfDistance = MaxDistance / 2.0f;

    if (bDrawDebug && HasAuthority()) // 서버에서 Multicast 호출
    {
        MulticastDrawDebugCone(Origin, Direction, ConeAngle, MaxDistance, FColor::Green, FColor::Red);
    }

    for (const FHitResult& Hit : HitResults)
    {
        if (AActor* HitActor = Hit.GetActor())
        {
            FVector ToTarget = HitActor->GetActorLocation() - Origin;
            float DistanceToTarget = ToTarget.Size();

            if (DistanceToTarget > MaxDistance)
            {
                continue;
            }

            ToTarget.Normalize();
            FVector NormalizedDirection = Direction.GetSafeNormal();

            float DotProduct = FVector::DotProduct(NormalizedDirection, ToTarget);
            float AngleToTarget = FMath::Acos(DotProduct);

            if (AngleToTarget <= HalfConeAngleRadians)
            {
                if (DistanceToTarget <= HalfDistance)
                {
                    CloseRangeActors.Add(HitActor);
                }
                else
                {
                    FarRangeActors.Add(HitActor);
                }
            }
        }
    }
}

void APickupWeapon::MulticastDrawDebugCone_Implementation(
    const FVector& Origin,
    const FVector& Direction,
    float ConeAngle,
    float MaxDistance,
    const FColor& CloseRangeColor,
    const FColor& FarRangeColor)
{
    if (!GetWorld())
    {
        UE_LOG(LogTemp, Error, TEXT("GetWorld() returned NULL"));
        return;
    }

    const int32 Segments = 50;
    FVector Forward = Direction.GetSafeNormal();
    FVector Right = FVector::CrossProduct(Forward, FVector::UpVector).GetSafeNormal();
    FVector Up = FVector::CrossProduct(Right, Forward).GetSafeNormal();

    FVector PrevPointClose, PrevPointFar;

    float HalfConeAngleRadians = FMath::DegreesToRadians(ConeAngle / 2);
    float HalfDistance = MaxDistance / 2.0f;

    for (int32 i = 0; i <= Segments; ++i)
    {
        float Angle = -HalfConeAngleRadians + (i * (2 * HalfConeAngleRadians / Segments));
        FVector RotatedDirection = Forward.RotateAngleAxis(FMath::RadiansToDegrees(Angle), Up);

        FVector EndPointClose = Origin + RotatedDirection * HalfDistance;
        FVector StartPointFar = EndPointClose;
        FVector EndPointFar = Origin + RotatedDirection * MaxDistance;

        if (i > 0)
        {
            DrawDebugLine(GetWorld(), Origin, EndPointClose, CloseRangeColor, false, 5.0f, 0, 3.0f);
            DrawDebugLine(GetWorld(), PrevPointClose, EndPointClose, CloseRangeColor, false, 5.0f, 0, 3.0f);

            DrawDebugLine(GetWorld(), StartPointFar, EndPointFar, FarRangeColor, false, 5.0f, 0, 3.0f);
            DrawDebugLine(GetWorld(), PrevPointFar, EndPointFar, FarRangeColor, false, 5.0f, 0, 3.0f);
        }

        PrevPointClose = EndPointClose;
        PrevPointFar = EndPointFar;
    }

}



void APickupWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

