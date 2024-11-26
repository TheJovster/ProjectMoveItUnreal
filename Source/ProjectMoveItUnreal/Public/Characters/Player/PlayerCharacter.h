// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.generated.h"

class UEnhancedInputComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PROJECTMOVEITUNREAL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
//functions
public:
	//ctor
	APlayerCharacter();
	//default functions
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//custom functions
	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
protected:
	virtual void BeginPlay() override;
private:

//variables
public:
//input assets
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveForwardInput;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveRightInput;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookInput;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpInput;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputContext;

//actor components
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	//actor component variables
	UPROPERTY(EditAnywhere, Category = "Component Values")
	float SpringArmHeight = 60.0f;
	UPROPERTY(EditAnywhere, Category = "Component Values")
	bool bInvertedLook = false;
protected:
private:
};
