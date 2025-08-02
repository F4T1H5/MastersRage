// Copyright Ahmet Fatih Senelmis


#include "Items/MastersRageProjectileBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MastersRageFunctionLibrary.h"
#include "MastersRageGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "MastersRageDebugHelper.h"

AMastersRageProjectileBase::AMastersRageProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollisionBox"));
	SetRootComponent(ProjectileCollisionBox);
	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileCollisionBox->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnProjectileHit);
	ProjectileCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnProjectileBeginOverlap);

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagaraComponent"));
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComp->InitialSpeed = 700.0f;
	ProjectileMovementComp->MaxSpeed = 900.0f;
	ProjectileMovementComp->Velocity = FVector(1.0f, 0.0f, 0.0f);
	ProjectileMovementComp->ProjectileGravityScale = 0.0f; // No gravity for this projectile

	InitialLifeSpan = 4.0f; // Default lifespan for the projectile
}

void AMastersRageProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (ProjectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlap)
	{
		ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}

void AMastersRageProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);

	APawn* HitPawn = Cast<APawn>(OtherActor);

	if (!HitPawn || !UMastersRageFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
	{
		Destroy();
		return;
	}

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UMastersRageFunctionLibrary::NativeDoesActorHaveTag(HitPawn, MastersRageGameplayTags::Player_Status_Blocking);

	if (bIsPlayerBlocking)
	{
		bIsValidBlock = UMastersRageFunctionLibrary::IsValidBlock(this, HitPawn);
	}

	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = HitPawn;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitPawn,
			MastersRageGameplayTags::Player_Event_SuccessfulBlock,
			Data
		);
	}
	else
	{
		HandleApplyProjectileDamage(HitPawn, Data);
	}

	Destroy();
}

void AMastersRageProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedActors.Contains(OtherActor))
	{
		return; // Already processed this actor
	}

	OverlappedActors.AddUnique(OtherActor);

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		FGameplayEventData Data;
		Data.Instigator = GetInstigator();
		Data.Target = HitPawn;

		if (UMastersRageFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
		{
			HandleApplyProjectileDamage(HitPawn, Data);
		}
	}

}

void AMastersRageProjectileBase::HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload)
{
	checkf(ProjectileDamageEffectSpecHandle.IsValid(), TEXT("Forgot to assign a valid spec handle to the projectile: %s"), *GetActorNameOrLabel());

	const bool bWasApplied = UMastersRageFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), InHitPawn, ProjectileDamageEffectSpecHandle);

	if (bWasApplied)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			InHitPawn,
			MastersRageGameplayTags::Shared_Event_HitReact,
			InPayload
		);
	}


}
