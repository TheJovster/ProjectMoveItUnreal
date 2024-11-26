// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = true;

	SpringArm->TargetArmLength = 0.0f;
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, SpringArmHeight));
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
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		
	}
}

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
		AddControllerYawInput(-InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}

}

