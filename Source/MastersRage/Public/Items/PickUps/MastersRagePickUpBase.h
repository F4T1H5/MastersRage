// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MastersRagePickUpBase.generated.h"

class USphereComponent;

UCLASS()
class MASTERSRAGE_API AMastersRagePickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AMastersRagePickUpBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pick UP Interaction")
	USphereComponent* PickUpCollisionSphere;

	UFUNCTION()
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
