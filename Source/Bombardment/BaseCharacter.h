// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseThrowable.h"
#include "Inventory.h"

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
	void EquipThrowableOne();
	void EquipThrowableTwo();

	// Container for throwables.
	TUniquePtr<Inventory> PlayerInventory;

	// Player follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent* CameraComp;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExplosiveThrowables")
	UClass* ExplosiveThrowableType;

	UPROPERTY(BluePrintReadWrite, EditAnywhere, Category = "Character Attributes")
		float HealthAmount = 100.0f;

	ABaseThrowable* currentExplosiveThrowable;

	UPROPERTY(BluePrintReadWrite, EditAnywhere, Category = "ExplosiveThrowables")
		TArray<TSoftClassPtr<ABaseThrowable>> Throwables;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
