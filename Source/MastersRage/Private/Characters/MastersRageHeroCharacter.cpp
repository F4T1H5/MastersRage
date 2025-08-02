// Copyright Ahmet Fatih Senelmis


#include "Characters/MastersRageHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/MastersRageInputComponent.h"
#include "MastersRageGameplayTags.h"
#include "AbilitySystem/MRageAbilitySystemComponent.h"
#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameModes/MastersRageBaseGameMode.h"

#include "MastersRageDebugHelper.h"

AMastersRageHeroCharacter::AMastersRageHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Disable automatic character rotation to match controller orientation.
	// This allows independent camera control while the character's rotation
	// will likely be controlled by movement direction instead.
	bUseControllerRotationPitch = false; 
	bUseControllerRotationYaw = false; 
	bUseControllerRotationRoll = false; 

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")); 
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f; // The camera follows at this distance behind the character
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true; // Rotate the spring arm (CameraBoom) based on the controller’s rotation (like mouse movement).

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); // ...at this rotation rate
	GetCharacterMovement()->MaxWalkSpeed = 400.f; // Default walking speed
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; // Braking deceleration while walking

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));

	HeroUIComponent = CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));

}

UPawnCombatComponent* AMastersRageHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUIComponent* AMastersRageHeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UHeroUIComponent* AMastersRageHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

void AMastersRageHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			int32 AbilityApplyLevel = 1; 

			if (AMastersRageBaseGameMode* BaseGameMode = GetWorld()->GetAuthGameMode<AMastersRageBaseGameMode>())
			{
				switch (BaseGameMode->GetCurrentGameDifficulty())
				{
					case EMastersRageGameDifficulty::Easy:
						AbilityApplyLevel = 4;
						//Debug::Print(TEXT("Easy difficulty detected, applying level 4 abilities."), FColor::Green);
						break;

					case EMastersRageGameDifficulty::Normal:
						AbilityApplyLevel = 3;
						//Debug::Print(TEXT("Normal difficulty detected, applying level 3 abilities."), FColor::Green);
						break;

					case EMastersRageGameDifficulty::Hard:
						AbilityApplyLevel = 2;
						//Debug::Print(TEXT("Hard difficulty detected, applying level 2 abilities."), FColor::Green);
						break;

					case EMastersRageGameDifficulty::VeryHard:
						AbilityApplyLevel = 1;
						//Debug::Print(TEXT("VeryHard difficulty detected, applying level 1 abilities."), FColor::Green);
						break;

				default:
					break;
				}
			}

			LoadedData->GiveToAbilitySystemComponent(MRageAbilitySystemComponent, AbilityApplyLevel);
		}

	}
}

void AMastersRageHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset for input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UMastersRageInputComponent* MastersRageInputComponent = CastChecked<UMastersRageInputComponent>(PlayerInputComponent);

	MastersRageInputComponent->BindNativeInputAction(InputConfigDataAsset, MastersRageGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	MastersRageInputComponent->BindNativeInputAction(InputConfigDataAsset, MastersRageGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	MastersRageInputComponent->BindNativeInputAction(InputConfigDataAsset, MastersRageGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggered);
	MastersRageInputComponent->BindNativeInputAction(InputConfigDataAsset, MastersRageGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);

	MastersRageInputComponent->BindNativeInputAction(InputConfigDataAsset, MastersRageGameplayTags::InputTag_PickUp_Stones, ETriggerEvent::Started, this, &ThisClass::Input_PickUpStonesStarted);
	MastersRageInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);

}

void AMastersRageHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMastersRageHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>(); 

	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f); 

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}


}

void AMastersRageHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMastersRageHeroCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void AMastersRageHeroCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X > 0.f ? MastersRageGameplayTags::Player_Event_SwitchTarget_Right : MastersRageGameplayTags::Player_Event_SwitchTarget_Left,
		Data
	);
}

void AMastersRageHeroCharacter::Input_PickUpStonesStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		MastersRageGameplayTags::Player_Event_ConsumeStones,
		Data
	);
}

void AMastersRageHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	MRageAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AMastersRageHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	MRageAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
