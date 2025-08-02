// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "MastersRageTypes/MastersRageEnumTypes.h"

class FMastersRageCountDownAction : public FPendingLatentAction
{
public:
	FMastersRageCountDownAction(float InTotalCountDownTime, float InUpdateInterval, float& InOutRemainingTime, EMastersRageCountDownActionOutput& InCountDownOutput, const FLatentActionInfo& LatentInfo)
		: bNeedToCancel(false)
		, TotalCountDownTime(InTotalCountDownTime)
		, UpdateInterval(InUpdateInterval)
		, OutRemainingTime(InOutRemainingTime)
		, CountDownOutput(InCountDownOutput)
		, ExecutionFunction(LatentInfo.ExecutionFunction)
		, OutputLink(LatentInfo.Linkage)
		, CallbackTarget(LatentInfo.CallbackTarget)
		, ElapsedInterval(0.0f)
		, ElapsedTimeSinceStart(0.0f)
	{
	}

	virtual void UpdateOperation(FLatentResponse& Response) override;

	void CancelAction();

private:
	bool bNeedToCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	EMastersRageCountDownActionOutput& CountDownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;

};