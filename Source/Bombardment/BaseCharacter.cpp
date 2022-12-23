// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "BaseThrowable.h"
#include "Inventory.h"
#include "Engine/EngineTypes.h"


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

	PlayerInventory = MakeUnique<Inventory>();
	if (PlayerInventory)
	{
		ExplosiveThrowableType = PlayerInventory->ThrowableOneClass();

		if (!ExplosiveThrowableType)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Typee"));
		}
	}

	currentExplosiveThrowable = nullptr;
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
	if (currentExplosiveThrowable) 
	{
		// Detatch the throwable from the base character
		FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false);
		currentExplosiveThrowable->DetachFromActor(DetachmentRules);

		// Set the velocity of the throwables projectile component to be in the direction of the forward vector.
		FVector forwardVec = currentExplosiveThrowable->GetActorForwardVector();
		float initialSpeed = currentExplosiveThrowable->ProjectileMovementComp->InitialSpeed;
		currentExplosiveThrowable->ProjectileMovementComp->Velocity = forwardVec * initialSpeed;
		currentExplosiveThrowable->ProjectileMovementComp->SetActive(true);
	}
}

void ABaseCharacter::InputSpawnExplosive()
{
	if (ExplosiveThrowableType)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Threw An Explosive"));

		// Get the socket location and the rotation of the 
		FVector Location = GetMesh()->GetSocketLocation("SocketExplosiveThrowable");
		FRotator Rotate = FRotator(GetActorRotation());
		
		// Spawn an explosive at the socket.
		currentExplosiveThrowable = GetWorld()->SpawnActor<ABaseThrowable>(ExplosiveThrowableType, Location, Rotate);
		FAttachmentTransformRules fTransRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
		
		// Attach the Explosive throwable to the socket.
		currentExplosiveThrowable->AttachToComponent(GetMesh(), fTransRules, "SocketExplosiveThrowable");
		currentExplosiveThrowable->ThrowableStaticMesh->SetSimulatePhysics(false);
	}
}

void ABaseCharacter::EquipThrowableOne()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Equip One Explosive"));
	if (Throwables.Num() >= 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Equip One Explosive///////////"));

		ExplosiveThrowableType = Throwables[0].LoadSynchronous();
	}
}

void ABaseCharacter::EquipThrowableTwo()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Equip Two Explosive"));

	if (Throwables.Num() >= 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Equip Two Explosive/////////"));

		ExplosiveThrowableType = Throwables[1].LoadSynchronous();
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

	check(PlayerInputComponent);

	// Movement bindings
	PlayerInputComponent->BindAxis("InputMoveRight", this, &ABaseCharacter::InputMoveRight);
	PlayerInputComponent->BindAxis("InputMoveForward", this, &ABaseCharacter::InputMoveForward);

	PlayerInputComponent->BindAxis("InputLookRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("InputLookUp", this, &APawn::AddControllerPitchInput);

	// Movement Actions
	PlayerInputComponent->BindAction("InputJump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("InputJump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("InputThrowExplosive", IE_Pressed, this, &ABaseCharacter::InputSpawnExplosive);
	PlayerInputComponent->BindAction("InputThrowExplosive", IE_Released, this, &ABaseCharacter::InputThrowExplosive);

	// Just bind actions. Should probably use a 
	PlayerInputComponent->BindAction("InputEquipThrowableOne", IE_Pressed, this, &ABaseCharacter::EquipThrowableOne);
	PlayerInputComponent->BindAction("InputEquipThrowableTwo", IE_Pressed, this, &ABaseCharacter::EquipThrowableTwo);
}

