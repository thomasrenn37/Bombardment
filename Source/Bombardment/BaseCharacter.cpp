// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "BaseThrowable.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Instantiating the camera component and setting it to be a child of the Skeletal Mesh component.
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(GetMesh());

	// Enable the use of the controller to determine rotations of the player.
	bUseControllerRotationPitch = 1;
	bUseControllerRotationYaw = 1;
} 

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::InputMoveRight(float value)
{
	if (Controller && (value != 0.0f))
	{
		// Find where we are rotated
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		// Calculate the right vector
		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(direction, value);
	}
}

void ABaseCharacter::InputMoveForward(float value)
{
	if (Controller && (value != 0.0f))
	{
		// Find where we are rotated
		FRotator rotation = Controller->GetControlRotation();
		FRotator yawRotation(0, rotation.Yaw, 0);
		
		// Calculate the right vector
		FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(direction, value);
	}
}

void ABaseCharacter::InputThrowExplosive()
{
	if (ExplosiveThrowable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Threw An Explosive"));

		// Spawn an explosive at the offset.
		FTransform ExplosiveTransform = FTransform(GetTransform());
		ExplosiveTransform.AddToTranslation(GetActorForwardVector() * 100);
		GetWorld()->SpawnActor<ABaseThrowable>(ExplosiveThrowable, ExplosiveTransform);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement bindings
	PlayerInputComponent->BindAxis("InputMoveRight", this, &ABaseCharacter::InputMoveRight);
	PlayerInputComponent->BindAxis("InputMoveForward", this, &ABaseCharacter::InputMoveForward);

	PlayerInputComponent->BindAxis("InputLookRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("InputLookUp", this, &APawn::AddControllerPitchInput);

	// Movement Actions
	PlayerInputComponent->BindAction("InputJump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("InputJump", IE_Released, this, &ACharacter::StopJumping);
	//PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::BeginCrouch);
	//PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::EndCrouch);
	//PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::BeginSprint);
	//PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::EndSprint);

	PlayerInputComponent->BindAction("InputThrowExplosive", IE_Pressed, this, &ABaseCharacter::InputThrowExplosive);
}

