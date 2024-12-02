// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class PROJECTMOVEITUNREAL_API AProjectileBase : public AActor
{
	GENERATED_BODY()

#pragma region Methods
public:	
	AProjectileBase();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void FireAtDirection(const FVector& Direction);
protected:
	virtual void BeginPlay() override;
private:	
#pragma endregion Methods
#pragma region Variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* CollisionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Variables")
	float ProjectileStartVelocity = 3000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Variables")
	float ProjectileEndVelocity = 3000.f;

protected:
private:
#pragma endregion 
};
