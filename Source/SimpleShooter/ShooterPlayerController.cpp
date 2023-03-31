// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	crosshair = CreateWidget(this, crosshairClass);
	if(crosshair != nullptr)
	{
		crosshair->AddToViewport();
	}
	
}


void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	
	if(bIsWinner)
	{
		UUserWidget* winScreen = CreateWidget(this, winScreenClass);
		if(winScreen != nullptr)
		{
			winScreen->AddToViewport();
		}
	} else
	{
		UUserWidget* loseScreen = CreateWidget(this, loseScreenClass);
		if(loseScreen != nullptr)
		{
			loseScreen->AddToViewport();
		}
	}

	crosshair->RemoveFromParent();
	GetWorldTimerManager().SetTimer(th, this, &APlayerController::RestartLevel, restartDelay, false);
}
