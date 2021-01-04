// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskShoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTaskShoot::UBTTaskShoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTaskShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;
	AShooterCharacter* Character = Cast<AShooterCharacter>(AIController->GetPawn());
	if (!Character) return EBTNodeResult::Failed;

	Character->Shoot();
	return EBTNodeResult::Succeeded;
}