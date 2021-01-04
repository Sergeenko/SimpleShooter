// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName(TEXT("Mesh")));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) return;

	FHitResult Hit;
	FVector ShotDirection;
	if (GunTrace(OwnerController, ShotDirection, OwnerPawn, Hit))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFlash, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		FPointDamageEvent GunHitEvent(InDamage, Hit, ShotDirection, nullptr);
		AActor* HitActor = Hit.GetActor();
		if (!HitActor) return;
		HitActor->TakeDamage(InDamage, GunHitEvent, OwnerController, this);
	}
}

bool AGun::GunTrace(AController* OwnerController, FVector& ShotDirection, APawn* OwnerPawn, FHitResult& Hit)
{
	FVector ViewLocation;
	FRotator ViewRotation;
	OwnerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
	ShotDirection = -ViewRotation.Vector();

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActors(TArray<AActor*>({ OwnerPawn, this }));
	FVector LineTraceEnd = ViewLocation + ViewRotation.Vector() * MaxRange;
	return GetWorld()->LineTraceSingleByChannel(Hit, ViewLocation, LineTraceEnd, ECollisionChannel::ECC_GameTraceChannel1, CollisionQueryParams);
}

