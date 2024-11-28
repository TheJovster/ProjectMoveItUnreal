// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class USceneComponent;
class UStaticMeshComponent;


UCLASS()
class PROJECTMOVEITUNREAL_API AWeaponBase : public AActor
{
	GENERATED_BODY()

#pragma region Methods	
//methods
public:
	AWeaponBase();
	virtual void Tick(float DeltaTime) override;
	static void Fire();
protected:
	virtual void BeginPlay() override;
private:

#pragma endregion Methods


#pragma region Variables	
//variables
public:
private:
protected:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	int Damage;
	UPROPERTY(EditAnywhere,Category="Weapon")
	int MaxAmmoInMag = 30.0f; //30 default. How many bullets you have in the mag right now.
	UPROPERTY(EditAnywhere,Category="Weapon")
	bool bIsSemiAuto = false;
	UPROPERTY(EditAnywhere,Category="Weapon")
	float RateOfFire = 1.0f; //How fast the weapon fires. Default is 1.0f. The larger the value, the more time between shots
	UPROPERTY(EditAnywhere,Category="Weapon")
	UStaticMeshComponent* WeaponStaticMesh;
#pragma endregion 	
};
