// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class AGun;


UCLASS()
class SHOOTERASSETPACK_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	bool	IsDead() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


private:
	void MoveForward(float fAxisValue);
	void MoveRight(float fAxisValue);

	void LookUp(float fAxisValue);
	void LookRight(float fAxisValue);

	void Shoot();


	UPROPERTY(EditAnyWhere)
	float fMovePower = 30.f;

	UPROPERTY(EditAnyWhere)
	float fWheelPower = 5.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun>	GunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditDefaultsOnly)
		float	MaxHp = 100.f;

	UPROPERTY(VisibleAnywhere)
		float	CurHp = MaxHp;
};
