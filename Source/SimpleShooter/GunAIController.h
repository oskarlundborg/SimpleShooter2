// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GunAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AGunAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;
	bool IsDead() const;
	
protected:
	void BeginPlay() override;

private:
	class APawn* pawn;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* bt;

};
