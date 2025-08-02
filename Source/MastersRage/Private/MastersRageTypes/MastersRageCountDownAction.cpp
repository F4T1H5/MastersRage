// Copyright Ahmet Fatih Senelmis


#include "MastersRageTypes/MastersRageCountDownAction.h"

void FMastersRageCountDownAction::UpdateOperation(FLatentResponse& Response)
{
	if (bNeedToCancel)
	{
		CountDownOutput = EMastersRageCountDownActionOutput::Cancelled;

		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);

		return;
	}

	if (ElapsedTimeSinceStart >= TotalCountDownTime)
	{
		CountDownOutput = EMastersRageCountDownActionOutput::Completed;
	
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);

		return;
	}

	if (ElapsedInterval < UpdateInterval)
	{
		ElapsedInterval += Response.ElapsedTime();
	}
	else
	{
		ElapsedTimeSinceStart += UpdateInterval > 0.f ? UpdateInterval : Response.ElapsedTime();

		OutRemainingTime = TotalCountDownTime - ElapsedTimeSinceStart;

		CountDownOutput = EMastersRageCountDownActionOutput::Updated;

		Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);

		ElapsedInterval = 0.0f; // Reset the interval after triggering the update
	}
}

void FMastersRageCountDownAction::CancelAction()
{
	bNeedToCancel = true;
}
