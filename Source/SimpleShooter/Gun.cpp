// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(root);

	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(root);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(muzzleFlash, mesh, TEXT("MuzzleFlashSocket"));
	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if(ownerPawn)
	{
		AController* ownerController = ownerPawn->GetController();
		if(ownerController)
		{
			FVector location;
			FRotator rotation;
			ownerController->GetPlayerViewPoint(location, rotation);
			FVector end = location + rotation.Vector() * maxRange;

			FCollisionQueryParams params;
			params.AddIgnoredActor(this);
			params.AddIgnoredActor(GetOwner());
			FHitResult hitResult;
			if(!GetWorld()->LineTraceSingleByChannel(hitResult, location, end, ECollisionChannel::ECC_GameTraceChannel1, params)) return;
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), impactEffect, hitResult.ImpactPoint);
			AActor* hitActor = hitResult.GetActor();
			if(hitActor)
			{
				FPointDamageEvent damageEvent(damage, hitResult, -rotation.Vector(), nullptr);
				hitActor->TakeDamage(damage, damageEvent, GetOwner()->GetInstigatorController(), this);
			}
		}
	}
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

