// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

Inventory::Inventory()
{
	// Default class
	ThrowableOne = TSoftClassPtr<ABaseThrowable>(FSoftObjectPath(TEXT("/Game/Blueprints/Explosives/Grenade.Grenade_C")));
	
	 if (!ThrowableOne)
	 { 
		UE_LOG(LogTemp, Warning, TEXT("Could not load Grenade blueprint."));
	 }
	ThrowableTwo = TSoftClassPtr<ABaseThrowable>(FSoftObjectPath(TEXT("/Game/Blueprints/NonExplosives/SpearThrowable.SpearThrowable_C")));
	if (!ThrowableTwo)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not load SpearThrowable blueprint."));
	}
}

Inventory::~Inventory()
{
}

void Inventory::GetPlayerInventory(TArray<TSoftClassPtr<ABaseThrowable>>& arr)
{
	if (!arr.IsEmpty())
	{
		arr.Empty();
	}

	arr.Append(Throwables);
}

UClass* Inventory::ThrowableOneClass()
{
	return ThrowableOne.LoadSynchronous();
}

UClass* Inventory::ThrowableTwoClass()
{
	return ThrowableTwo.LoadSynchronous();
}
