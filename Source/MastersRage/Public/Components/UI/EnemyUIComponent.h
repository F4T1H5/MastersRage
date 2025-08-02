// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

class UMastersRageWidgetBase;

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(UMastersRageWidgetBase* InWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();

private:

	TArray<UMastersRageWidgetBase*> EnemyDrawnWidgets;
};
