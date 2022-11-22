// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "BaseThrowable.h"


#include "BaseCharacter.generated.h"

UCLASS()
class BOMBARDMENT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Player movement inputs
	void InputMoveRight(float value);
	void InputMoveForward(float value);

	// Player input actions.
	void InputThrowExplosive();
	void InputSpawnExplosive();

	// Player follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		FVector throwableOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExplosiveThrowables")
		TSubclassOf<ABaseThrowable> ExplosiveThrowable;

	UPROPERTY(EditDefaultsOnly, Category = "ExplosiveThrowables")
		float ThrowStrength = 100.0f;

	UPROPERTY(BluePrintReadWrite, EditAnywhere, Category = "Character Attributes")
		float HealthAmount = 100.0f;


	ABaseThrowable* currentExplosiveThrowable;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
