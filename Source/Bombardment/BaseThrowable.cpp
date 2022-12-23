// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseThrowable.h"

// Sets default values
ABaseThrowable::ABaseThrowable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ThrowableStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThrowableStaticMesh"));
	ThrowableStaticMesh->SetupAttachment(RootComponent);

	// Do not want the mesh to block player.
	ThrowableStaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	// Set up the projectile movement component.
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->SetAutoActivate(false);
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->InitialSpeed = 1000.f;
	ProjectileMovementComp->MaxSpeed = 1000.f;
	SetActorTickEnabled(false);
}

// Called when the game starts or when spawned
void ABaseThrowable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseThrowable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

