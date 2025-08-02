// Copyright Ahmet Fatih Senelmis


#include "Components/UI/EnemyUIComponent.h"
#include "Widgets/MastersRageWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidget(UMastersRageWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawnWidgets.IsEmpty())
	{
		return;
	}

	for (UMastersRageWidgetBase* DrawnWidget : EnemyDrawnWidgets)
	{
		if (DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}

	EnemyDrawnWidgets.Empty();
}
