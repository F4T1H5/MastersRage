// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MastersRageWidgetBase.generated.h"

class UHeroUIComponent;
class UEnemyUIComponent;

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API UMastersRageWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	

protected:

	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Hero UI Component Initialized"))
	void BP_OnOwningHeroUIComponentInitialized(UHeroUIComponent* OwningHeroUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Enemy UI Component Initialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* OwningEnemyUIComponent);

public:

	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);

};
