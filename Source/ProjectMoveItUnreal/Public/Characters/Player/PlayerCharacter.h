// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerCharacter.generated.h"

class UEnhancedInputComponent;
class USpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class UCapsuleComponent;
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
	void CrouchAction(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;
private:
	virtual void Crouch(bool bClientSimulation = false) override;
	virtual void UnCrouch(bool bClientSimulation = false) override;
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
	UInputAction* CrouchInput;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputContext;

//actor components
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	//actor component variables
	UPROPERTY(EditAnywhere, Category = "Component Values")
	float CameraHeight = 60.0f;
	UPROPERTY(EditAnywhere, Category = "Component Values")
	bool bInvertedLook = false;
	UPROPERTY(VisibleAnywhere, Category = "Component Values")
	FVector OriginalCameraPosition;
	UPROPERTY(EditAnywhere, Category = "Component Values")
	float CameraResetLerpTime = 0.5f;

//player variables
	UPROPERTY(EditAnywhere, Category = "Player Variables/Crouch")
	bool bIsCrouching = false;
	UPROPERTY(VisibleAnywhere, Category = "Player Variables/Crouch")
	FVector EyeOffset;
protected:
private:
	//crouching
	float TargetCapsuleHalfHeight;
	float CurrentCapsuleHalfHeight;
	bool bInterpCrouch;
	UPROPERTY(EditAnywhere, Category = "Player Variables/Crouch")
	float CrouchInterpSpeed = 10.0f;
};
