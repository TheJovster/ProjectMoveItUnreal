// Fill out your copyright notice in the Description page of Project Settings.
#include "Characters/Player/PlayerCharacter.h"

// ctor - Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);

	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, CameraHeight));
	WeaponInventory = CreateDefaultSubobject<UWeaponInventory>("Weapon Inventory");
}
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Add the input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputContext, 0);
		}
	}
	OriginalCameraPosition = Camera->GetRelativeLocation();
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//how performant is this?
	if (bInterpCrouch)
	{
		// Current height
		float CurrentHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
        
		// Interpolate height
		float NewHeight = FMath::FInterpTo(
			CurrentHeight, 
			TargetCapsuleHalfHeight, 
			DeltaTime, 
			CrouchInterpSpeed
		);

		// Update capsule height
		GetCapsuleComponent()->SetCapsuleHalfHeight(NewHeight);

		// Check if we've reached the target height
		if (FMath::IsNearlyEqual(NewHeight, TargetCapsuleHalfHeight, 1.0f))
		{
			bInterpCrouch = false;
		}
	}

	if(!GetCharacterMovement()->IsMovingOnGround())
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		UE_LOG(LogTemp, Warning, TEXT("Stopped Sprinting"));
	}
	
}
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardInput, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightInput, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRight);
		EnhancedInputComponent->BindAction(LookInput, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(JumpInput, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(CrouchInput, ETriggerEvent::Triggered, this, &APlayerCharacter::CrouchAction);
		EnhancedInputComponent->BindAction(SprintInput, ETriggerEvent::Started, this, &APlayerCharacter::SprintStarted);
		EnhancedInputComponent->BindAction(SprintInput, ETriggerEvent::Completed, this, &APlayerCharacter::SprintFinished);
		EnhancedInputComponent->BindAction(FireInput, ETriggerEvent::Triggered, this, &APlayerCharacter::Fire);
	}
}
#pragma region BasicMovement
void APlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	if(Controller != nullptr)
	{
		const FRotator Rotator = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotator.Yaw, 0.0f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector2D InputVector = Value.Get<FVector2D>();
		AddMovementInput(ForwardDirection, InputVector.Y);

		UE_LOG(LogTemp, Warning, TEXT("%f"), InputVector.Y);
	}
}

void APlayerCharacter::MoveRight(const FInputActionValue& Value)
{
	const FRotator Rotator = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotator.Yaw, 0.0f);
	
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector2D InputVector = Value.Get<FVector2D>();
	AddMovementInput(RightDirection, InputVector.X);
	
	UE_LOG(LogTemp, Warning, TEXT("%f"), InputVector.X);
}

void APlayerCharacter::Jump(const FInputActionValue& Value)
{
	Super::Jump();
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D InputVector = Value.Get<FVector2D>();
	if(bInvertedLook)
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
	else if(!bInvertedLook)
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(-InputVector.Y);
	}
}
#pragma endregion  
#pragma region  Crouching

void APlayerCharacter::CrouchAction(const FInputActionValue& Value)
{
	bIsCrouching = !bIsCrouching;
	if(bIsCrouching)
	{
		GetCharacterMovement()->bWantsToCrouch = true;
		Crouch();
	}
	else
	{
		GetCharacterMovement()->bWantsToCrouch = false;
		UnCrouch();
	}
}

void APlayerCharacter::Crouch(bool bClientSimulation)
{
	Super::Crouch(bClientSimulation);
	bInterpCrouch = true;
	TargetCapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 0.5f;
	// Optional: Reduce movement speed

	GetCharacterMovement()->MaxWalkSpeed = CrouchedSpeed;
}

void APlayerCharacter::UnCrouch(bool bClientSimulation)
{
	Super::UnCrouch(bClientSimulation);
	bInterpCrouch = true;
	TargetCapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2.0f;
	// Restore movement speed
	if(bIsSprinting)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}
#pragma endregion
#pragma region Sprinting
void APlayerCharacter::SprintStarted(const FInputActionValue& Value)
{
	if(!bIsCrouching && GetCharacterMovement()->IsMovingOnGround())
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		UE_LOG(LogTemp, Warning, TEXT("Sprinting"));
	}
}

void APlayerCharacter::SprintFinished(const FInputActionValue& Value)
{
	if(!bIsCrouching && GetCharacterMovement()->IsMovingOnGround())
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		UE_LOG(LogTemp, Warning, TEXT("Stopped Sprinting"));
	}
}
#pragma endregion 
#pragma region Firing
void APlayerCharacter::Fire(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Firing Gun from PlayerCharacter"));
	WeaponInventory->GetCurrentWeapon()->Fire();
}
#pragma endregion Firing