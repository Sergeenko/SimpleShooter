// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

private:
	bool GunTrace(AController* OwnerController, FVector& ShotDirection, APawn* OwnerPawn, FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere)
	float MaxRange = 10000;

	UPROPERTY(EditAnywhere)
	float InDamage = 23;


};
