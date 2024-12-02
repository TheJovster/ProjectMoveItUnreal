// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Static Mesh Component");
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

