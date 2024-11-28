// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponBase.h"


AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponModel");
	SetRootComponent(WeaponStaticMesh);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fired from the weapon"));
}

