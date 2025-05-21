// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Gun.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

bool AMyCharacter::IsDead() const
{

	return CurHp <= 0.f;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AMyCharacter::LookRight);

	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AMyCharacter::Shoot);
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(CurHp, DamageApplied);
	CurHp -= DamageApplied;

	UE_LOG(LogTemp, Warning, TEXT("Player HP: %.2f / %.2f"), CurHp, MaxHp);

	return DamageApplied;
}

void AMyCharacter::MoveForward(float fAxisValue)
{
	AddMovementInput(GetActorForwardVector() * fAxisValue * fMovePower * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::MoveRight(float fAxisValue)
{
	AddMovementInput(GetActorRightVector() * fAxisValue * fMovePower * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::LookUp(float fAxisValue)
{
	APawn::AddControllerPitchInput(fAxisValue * fWheelPower * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::LookRight(float fAxisValue)
{
	APawn::AddControllerYawInput(fAxisValue * fWheelPower * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::Shoot()
{
	Gun->PullTrigger();
}

