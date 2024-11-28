// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponBase.h"
#include "WeaponInventory.generated.h"

class AWeaponBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMOVEITUNREAL_API UWeaponInventory : public UActorComponent
{
	GENERATED_BODY()

#pragma region Methods
	//methods
public:	
	// Sets default values for this component's properties
	UWeaponInventory();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AddWeapon(AWeaponBase* WeaponToAdd);
	AWeaponBase* GetCurrentWeapon() {return CurrentWeapon;}
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:	
	// Called every frame
	#pragma endregion Methods

#pragma region Variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<AWeaponBase*> Weapons;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	AWeaponBase* CurrentWeapon;
private:
	
#pragma endregion 
		
};
