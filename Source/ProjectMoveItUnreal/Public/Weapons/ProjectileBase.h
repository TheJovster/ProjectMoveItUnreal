// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class PROJECTMOVEITUNREAL_API AProjectileBase : public AActor
{
	GENERATED_BODY()

#pragma region Methods
public:	
	AProjectileBase();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
private:	
#pragma endregion Methods
#pragma region Variables
public:
	UPROPERTY()
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Variables")
	float ProjectileStartVelocity = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Variables")
	float ProjectileEndVelocity = 3000.f;

protected:
private:
#pragma endregion 
};
