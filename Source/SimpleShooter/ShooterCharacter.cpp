// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "Gun.h"
#include "SimpleShooterGameModeBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	gun = GetWorld()->SpawnActor<AGun>(gunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GunSocket"));
	gun->SetOwner(this);
	health = maxHealth;
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

void AShooterCharacter::Shoot()
{
	gun->PullTrigger();
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageApp = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	damageApp = FMath::Min(health, damageApp);
	health -= damageApp;
	UE_LOG(LogTemp, Display, TEXT("health: %f"), health);

	if(IsDead())
	{
		ASimpleShooterGameModeBase* gm = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if(gm)
		{
			gm->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	return damageApp;
}

bool AShooterCharacter::IsDead() const
{
	return health <= 0;
}

float AShooterCharacter::GetHealthPercent() const
{
	return health/maxHealth;
}

void AShooterCharacter::MoveForward(float axisVal)
{
	AddMovementInput(GetActorForwardVector() * axisVal);
}

void AShooterCharacter::MoveRight(float axisVal)
{
	AddMovementInput(GetActorRightVector() * axisVal);
}
