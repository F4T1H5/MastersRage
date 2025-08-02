// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FMastersRageInputActionConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;
	//UInputAction* InputAction;

	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction;
	}

};
/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	//UInputMappingContext* DefaultMappingContext; // Default input mapping context.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FMastersRageInputActionConfig> NativeInputActions; // Array of input actions with their corresponding tags.

	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const; // Finds a native input action by its tag.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FMastersRageInputActionConfig> AbilityInputActions; // Array of input actions with their corresponding tags.

};
