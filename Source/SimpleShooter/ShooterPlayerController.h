// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> loseScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> winScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> crosshairClass;

	class UUserWidget* crosshair;
	
	UPROPERTY(EditAnywhere)
	float restartDelay = 5.f;

	FTimerHandle th;
	
};
