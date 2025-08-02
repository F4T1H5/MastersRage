// Copyright Ahmet Fatih Senelmis


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/MRageAttributeSet.h"
#include "MastersRageGameplayTags.h"

#include "MastersRageDebugHelper.h"

struct FMastersRageDamageCaptrue
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FMastersRageDamageCaptrue()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMRageAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMRageAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMRageAttributeSet, DamageTaken, Target, false)
	}
};

static const FMastersRageDamageCaptrue& GetMastersRageDamageCapture()
{
	static FMastersRageDamageCaptrue MastersRageDamageCapture;
	return MastersRageDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	/* Slow Way of Doing Capture*/
	//FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	//	UMRageAttributeSet::StaticClass(),
	//	GET_MEMBER_NAME_CHECKED(UMRageAttributeSet, AttackPower)
	//);
	//
	//FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
	//	AttackPowerProperty,
	//	EGameplayEffectAttributeCaptureSource::Source,
	//	false
	//);
	//
	//RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);

	RelevantAttributesToCapture.Add(GetMastersRageDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetMastersRageDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetMastersRageDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	
	//EffectSpec.GetContext().GetSourceObject();
	//EffectSpec.GetContext().GetAbility();
	//EffectSpec.GetContext().GetInstigator();
	//EffectSpec.GetContext().GetEffectCauser();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetMastersRageDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	//Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);

	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(MastersRageGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			//Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}

		if (TagMagnitude.Key.MatchesTagExact(MastersRageGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);
		}

		if (TagMagnitude.Key.MatchesTagExact(MastersRageGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
		}
	}

	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetMastersRageDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	//Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);

	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05f + 1.f;
		BaseDamage *= DamageIncreasePercentLight;
		//Debug::Print(TEXT("BaseDamage after Light Combo"), BaseDamage);
	}

	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
		BaseDamage *= DamageIncreasePercentHeavy;
		//Debug::Print(TEXT("BaseDamage after Heavy Combo"), BaseDamage);
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	//Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone);

	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetMastersRageDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}
}
