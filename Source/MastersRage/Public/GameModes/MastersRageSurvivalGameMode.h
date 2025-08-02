// Copyright Ahmet Fatih Senelmis

#pragma once

#include "CoreMinimal.h"
#include "GameModes/MastersRageBaseGameMode.h"
#include "MastersRageSurvivalGameMode.generated.h"

class AMastersRageEnemyCharacter;

UENUM(BlueprintType)
enum class EMastersRageSurvivalGameModeState : uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWavesDone,
	PlayerDied
};

USTRUCT(BlueprintType)
struct FMastersRageEnemyWaveSpawnerInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AMastersRageEnemyCharacter> SoftEnemyClassToSpawn;

	UPROPERTY(EditAnywhere)
	int32 MinPerSpawnCount = 1;

	UPROPERTY(EditAnywhere)
	int32 MaxPerSpawnCount = 3;
};

USTRUCT(BlueprintType)
struct FMastersRageEnemyWaveSpawnerTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FMastersRageEnemyWaveSpawnerInfo> EnemyWaveSpawnerDefinitions;

	UPROPERTY(EditAnywhere)
	int32 TotalEnemyToSpawnThisWave = 1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvivalGameModeStateChanged, EMastersRageSurvivalGameModeState, CurrentState);

/**
 * 
 */
UCLASS()
class MASTERSRAGE_API AMastersRageSurvivalGameMode : public AMastersRageBaseGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SetCurrentSurvivalGameModeState(EMastersRageSurvivalGameModeState InState);
	bool HasFinishedAllWaves() const;
	void PreLoadNextWaveEnemies();
	FMastersRageEnemyWaveSpawnerTableRow* GetCurrentWaveSpawnerTableRow() const;
	int32 TrySpawnWaveEnemies();
	bool ShouldKeepSpawnEnemies() const;

	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);

	UPROPERTY()
	EMastersRageSurvivalGameModeState CurrentSurvivalGameModeState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvivalGameModeStateChanged OnSurvivalGameModeStateChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	UDataTable* EnemyWaveSpawnerDataTable;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	int32 TotalWavesToSpawn;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	int32 CurrentWaveCount = 1;

	UPROPERTY()
	int32 CurrentSpawnedEnemiesCounter = 0;

	UPROPERTY()
	int32 TotalSpawnedEnemiesThisWaveCounter = 0;

	UPROPERTY()
	TArray<AActor*> TargetPointsArray;

	UPROPERTY()
	float TimePassedSinceStart = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float SpawnNewWaveWaitTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float SpawnEnemiesDelayTime = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float WaveCompletedWaitTime = 5.0f;

	UPROPERTY()
	TMap<TSoftClassPtr<AMastersRageEnemyCharacter>, UClass*> PreLoadedEnemyClassMap;

public:
	UFUNCTION(BlueprintCallable)
	void RegisterSpawnedEnemies(const TArray<AMastersRageEnemyCharacter*>& InEnemiesToRegister);
};
