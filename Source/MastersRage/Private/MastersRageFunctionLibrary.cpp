// Copyright Ahmet Fatih Senelmis


#include "MastersRageFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/MRageAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "MastersRageGameplayTags.h"
#include "MastersRageTypes/MastersRageCountDownAction.h"
#include "MastersRageGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/MastersRageSaveGame.h"

#include "MastersRageDebugHelper.h"

UMRageAbilitySystemComponent* UMastersRageFunctionLibrary::NativeGetMRageASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UMRageAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UMastersRageFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UMRageAbilitySystemComponent* ASC = NativeGetMRageASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UMastersRageFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UMRageAbilitySystemComponent* ASC = NativeGetMRageASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UMastersRageFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UMRageAbilitySystemComponent* ASC = NativeGetMRageASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UMastersRageFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EMastersRageConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EMastersRageConfirmType::Yes : EMastersRageConfirmType::No;
}

UPawnCombatComponent* UMastersRageFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UMastersRageFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EMastersRageValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EMastersRageValidType::Valid : EMastersRageValidType::Invalid;

	return CombatComponent;
}

bool UMastersRageFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

float UMastersRageFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UMastersRageFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);

	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);

	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return MastersRageGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return MastersRageGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference < -135.f || OutAngleDifference > 135.f)
	{
		return MastersRageGameplayTags::Shared_Status_HitReact_Back;
	}
	else if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
	{
		return MastersRageGameplayTags::Shared_Status_HitReact_Right;
	}
	
	return MastersRageGameplayTags::Shared_Status_HitReact_Front;
}

bool UMastersRageFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());

	/*const FString DebugString = FString::Printf(TEXT("Dot Product: %f"), DotResult, DotResult < -0.1f ? TEXT("Valid Block!") : TEXT("Invalid Block!"));

	Debug::Print(DebugString, DotResult < -0.1f ? FColor::Green: FColor::Red);*/

	return DotResult < -0.1f; // If the dot product is negative, the defender is facing away from the attacker, indicating a valid block.
}

bool UMastersRageFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UMRageAbilitySystemComponent* SourceASC = NativeGetMRageASCFromActor(InInstigator);
	UMRageAbilitySystemComponent* TargetASC = NativeGetMRageASCFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UMastersRageFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, EMastersRageCountDownActionInput CountDownInput, UPARAM(DisplayName = "Output") EMastersRageCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo)
{
	UWorld* World = nullptr;

	if (GEngine)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	}

	if (!World)
	{
		return;
	}

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

	FMastersRageCountDownAction* FoundAction = LatentActionManager.FindExistingAction<FMastersRageCountDownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);

	if (CountDownInput == EMastersRageCountDownActionInput::Start)
	{
		if (!FoundAction)
		{
			LatentActionManager.AddNewAction(
				LatentInfo.CallbackTarget,
				LatentInfo.UUID,
				new FMastersRageCountDownAction(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutput, LatentInfo)
			);
		}
	}

	if (CountDownInput == EMastersRageCountDownActionInput::Cancel)
	{
		if (FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}

UMastersRageGameInstance* UMastersRageFunctionLibrary::GetMastersRageGameInstance(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return World->GetGameInstance<UMastersRageGameInstance>();
		}
	}

	return nullptr;
}

void UMastersRageFunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, EMastersRageInputMode InInputMode)
{
	APlayerController* PlayerController = nullptr;

	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			PlayerController = World->GetFirstPlayerController();
		}
	}

	if (!PlayerController)
	{
		return;
	}

	FInputModeGameOnly GameOnlyMode;
	FInputModeUIOnly UIOnlyMode;

	switch (InInputMode)
	{
	case EMastersRageInputMode::GameOnly:

		PlayerController->SetInputMode(GameOnlyMode);
		PlayerController->bShowMouseCursor = false;

		break;
	case EMastersRageInputMode::UIOnly:

		PlayerController->SetInputMode(UIOnlyMode);
		PlayerController->bShowMouseCursor = true;

		break;
	default:
		break;
	}
}

void UMastersRageFunctionLibrary::SaveCurrentGameDifficulty(EMastersRageGameDifficulty InDifficultyToSave)
{
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(UMastersRageSaveGame::StaticClass());

	if (UMastersRageSaveGame* MastersRageSaveGameObject = Cast<UMastersRageSaveGame>(SaveGameObject))
	{
		MastersRageSaveGameObject->SavedCurrentGameDifficulty = InDifficultyToSave;

		const bool bWasSaved = UGameplayStatics::SaveGameToSlot(MastersRageSaveGameObject, MastersRageGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0);

		//Debug::Print(bWasSaved ? TEXT("Difficulty Saved." : TEXT("Not Saved")));
	}
}

bool UMastersRageFunctionLibrary::TryLoadSavedGameDifficulty(EMastersRageGameDifficulty& OutSavedDifficulty)
{
	if (UGameplayStatics::DoesSaveGameExist(MastersRageGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0))
	{
		USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(MastersRageGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0);

		if (UMastersRageSaveGame* MastersRageSaveGameObject = Cast<UMastersRageSaveGame>(SaveGameObject))
		{
			OutSavedDifficulty = MastersRageSaveGameObject->SavedCurrentGameDifficulty;

			//Debug::Print(TEXT("Loading Successful"), FColor::Green);

			return true;
		}
	}

	return false;
}
