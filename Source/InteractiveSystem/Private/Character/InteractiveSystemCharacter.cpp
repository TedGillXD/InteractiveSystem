// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/InteractiveSystemCharacter.h"
#include "../InteractiveSystemProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Character/Components/InventoryComponent.h"
#include "Engine/LocalPlayer.h"
#include "Interfaces/InteractableInterface.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AInteractiveSystemCharacter

AInteractiveSystemCharacter::AInteractiveSystemCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));


	InHandItem = nullptr;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComp"));
}

void AInteractiveSystemCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

void AInteractiveSystemCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	// 通过射线检测检测前方是否有能互动的物体
	FHitResult Result;
	FVector Start = GetFirstPersonCameraComponent()->GetComponentLocation();
	static const float DetectionLength = 500.f;
	FVector End = Start + GetFirstPersonCameraComponent()->GetForwardVector() * DetectionLength;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	if(GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECC_GameTraceChannel2, Params)) {
		// 当检测到的Actor需要更新状态的时候
		if(Result.GetActor()->Implements<UInteractableInterface>() && IInteractableInterface::Execute_ShouldUpdate(Result.GetActor())) {
			IInteractableInterface::Execute_Updated(Result.GetActor());
			OnDetectedActorChanged.Broadcast(Result.GetActor());
		}
		if(DetectedActor != Result.GetActor()) {		// 当检测到的Actor产生变化的时候
			OnDetectedActorChanged.Broadcast(Result.GetActor());
		}
		DetectedActor = Result.GetActor();
	} else {
		if(DetectedActor != Result.GetActor()) {		// 当没有检测到Actor的时候
			OnDetectedActorChanged.Broadcast(Result.GetActor());
		}
		DetectedActor = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AInteractiveSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInteractiveSystemCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AInteractiveSystemCharacter::Look);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &AInteractiveSystemCharacter::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

UInventoryComponent* AInteractiveSystemCharacter::GetInventoryComponent_Implementation() const {
	return InventoryComponent;
}


void AInteractiveSystemCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AInteractiveSystemCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AInteractiveSystemCharacter::Interact() {
	if(!DetectedActor) {
		return;
	}
	
	if(DetectedActor->Implements<UInteractableInterface>() && IInteractableInterface::Execute_CanInteract(DetectedActor, InHandItem, this)) {
		IInteractableInterface::Execute_Interact(DetectedActor, InHandItem, this); // 可以互动
	}
}

void AInteractiveSystemCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AInteractiveSystemCharacter::GetHasRifle()
{
	return bHasRifle;
}