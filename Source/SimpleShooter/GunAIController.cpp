// Fill out your copyright notice in the Description page of Project Settings.


#include "GunAIController.h"

#include "ShooterCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AGunAIController::BeginPlay() 
{
	Super::BeginPlay();

	pawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if(bt) RunBehaviorTree(bt);
	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerStartLocation"), pawn->GetActorLocation());
	GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), this->GetPawn()->GetActorLocation());
	
}

void AGunAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

bool AGunAIController::IsDead() const
{
	AShooterCharacter* controlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if(controlledCharacter)
	{
		return controlledCharacter->IsDead();
	}

	return true;
}


