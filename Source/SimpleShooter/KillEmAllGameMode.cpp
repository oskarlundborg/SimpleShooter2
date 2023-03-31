// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GunAIController.h"
#include "ShooterPlayerController.h"

void AKillEmAllGameMode::PawnKilled(APawn* pawnKilled)
{
	Super::PawnKilled(pawnKilled);
	
	APlayerController* pc = Cast<APlayerController>(pawnKilled->GetController());
	if(pc)
	{
		EndGame(false);
	}
	
	for(AGunAIController* aiController : TActorRange<AGunAIController>(GetWorld()))
	{
		if(!aiController->IsDead()) return;
	}
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bPlayerWon)
{
	for(AController* controller : TActorRange<AController>(GetWorld()))
	{
		controller->GameHasEnded(controller->GetPawn(), controller->IsPlayerController() == bPlayerWon); 
	}
}

