// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupWeapon.h"

void APickupWeapon::Pickup(AActor* Picker)
{
    active = false;
    SetActorHiddenInGame(true);

    // �÷��̾� ���Ͱ� �ִ��� Ȯ��
    AActor* PlayerActor = Cast<AActor>(Picker);
    if (PlayerActor)
    {
        UE_LOG(LogTemp, Log, TEXT("Weapon Picked Up by Player"));

        // ���� ��ü�� HeldObject�� �����Ͽ� ���� ������ �� Ȱ��
        HeldObject = this;

        // �÷��̾��� Skeletal Mesh Component�� ������
        USkeletalMeshComponent* PlayerMesh = PlayerActor->FindComponentByClass<USkeletalMeshComponent>();
        if (PlayerMesh)
        {
            // "HandSocket"�� ����
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
        // ������Ʈ�� �տ��� �и�
        DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

        // RootComponent�� ���� �ùķ��̼��� �����ϴ��� Ȯ���ϰ� ����
        UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(GetRootComponent());
        if (PrimitiveComp)
        {
            // ���� �ùķ��̼� Ȱ��ȭ
            PrimitiveComp->SetSimulatePhysics(true);

            // ���� �������� ���� ���Ͽ� ������
            FVector ForwardVector = GetActorForwardVector();
            FVector ThrowForce = ForwardVector * 10000.0f; // ���ϴ� �� ũ��
            PrimitiveComp->AddImpulse(ThrowForce, NAME_None, true);
        }

        // HeldObject �ʱ�ȭ
        HeldObject = nullptr;
    }
    active = false;
}

