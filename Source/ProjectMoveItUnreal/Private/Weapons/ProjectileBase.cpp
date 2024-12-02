// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ProjectileBase.h"

#include "MovieSceneSequenceID.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;
	if(!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>("Projectile Scene Component");
	}
	if(!StaticMeshComponent)
	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Static Mesh Component");
	}
	if(StaticMeshComponent)
	{
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if(!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>("Collision Component");
		CollisionComponent->SetSphereRadius(10.0f);
		RootComponent = CollisionComponent;
	}
	if(!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
		ProjectileMovementComponent->InitialSpeed = ProjectileStartVelocity;
		ProjectileMovementComponent->MaxSpeed = ProjectileEndVelocity;
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	}
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

void AProjectileBase::FireAtDirection(const FVector& Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

