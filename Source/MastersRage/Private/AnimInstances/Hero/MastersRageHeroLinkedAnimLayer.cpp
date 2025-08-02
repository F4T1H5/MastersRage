// Copyright Ahmet Fatih Senelmis


#include "AnimInstances/Hero/MastersRageHeroLinkedAnimLayer.h"
#include "AnimInstances/Hero/MastersRageHeroAnimInstance.h"

UMastersRageHeroAnimInstance* UMastersRageHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
    return Cast<UMastersRageHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
