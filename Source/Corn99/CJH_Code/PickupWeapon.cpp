// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupWeapon.h"

void APickupWeapon::Pickup(AActor* Picker)
{
    active = false;
    SetActorHiddenInGame(true);

    // 플레이어 액터가 있는지 확인
    AActor* PlayerActor = Cast<AActor>(Picker);
    if (PlayerActor)
    {
        UE_LOG(LogTemp, Log, TEXT("Weapon Picked Up by Player"));

        // 현재 객체를 HeldObject에 설정하여 이후 던지기 시 활용
        HeldObject = this;

        // 플레이어의 Skeletal Mesh Component를 가져옴
        USkeletalMeshComponent* PlayerMesh = PlayerActor->FindComponentByClass<USkeletalMeshComponent>();
        if (PlayerMesh)
        {
            // "HandSocket"에 부착
            AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("HandSocket"));

         
            SetActorHiddenInGame(false);
        }
        active = true;
    }
}

void APickupWeapon::ThrowWeaponTest()
{
    if (HeldObject)
    {
        // 오브젝트를 손에서 분리
        DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

        // RootComponent가 물리 시뮬레이션을 지원하는지 확인하고 설정
        UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(GetRootComponent());
        if (PrimitiveComp)
        {
            // 물리 시뮬레이션 활성화
            PrimitiveComp->SetSimulatePhysics(true);

            // 전방 방향으로 힘을 가하여 던지기
            FVector ForwardVector = GetActorForwardVector();
            FVector ThrowForce = ForwardVector * 10000.0f; // 원하는 힘 크기
            PrimitiveComp->AddImpulse(ThrowForce, NAME_None, true);
        }

        // HeldObject 초기화
        HeldObject = nullptr;
    }
    active = false;
}

