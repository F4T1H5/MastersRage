#pragma once

UENUM()
enum class EMastersRageConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EMastersRageValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EMastersRageSuccessType : uint8
{
	Successful,
	Failed
};

UENUM()
enum class EMastersRageCountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class EMastersRageCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};

UENUM(BlueprintType)
enum class EMastersRageGameDifficulty : uint8
{
	Easy,
	Normal,
	Hard,
	VeryHard
};

UENUM(BlueprintType)
enum class EMastersRageInputMode : uint8
{
	GameOnly,
	UIOnly
};