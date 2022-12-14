// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "BaseThrowable.generated.h"

UCLASS()
class BOMBARDMENT_API ABaseThrowable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseThrowable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ThrowableStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UProjectileMovementComponent* ProjectileMovementComp;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
