// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponBase.h"


AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>("Muzzle");
	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponModel");
	MuzzleLocation->SetupAttachment(WeaponStaticMesh);
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
	UE_LOG(LogTemp, Warning, TEXT("Fired"));
}

