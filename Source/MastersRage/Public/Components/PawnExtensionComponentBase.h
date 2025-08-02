// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MASTERSRAGE_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:

	template <class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' template Parameter to GetPawn must be derived from APawn");
		return CastChecked<T>(GetOwner()); // Ensure that the owner is of type T
	}
	// Our hero pawn
	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' template Parameter to GetController must be derived from AController");
		return GetOwningPawn<APawn>()->GetController<T>();
	}
};