// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseThrowable.h"

/**
 * 
 */
class BOMBARDMENT_API Inventory
{
private:
	TArray< TSubclassOf<ABaseThrowable> > Throwables;
	TSoftClassPtr<ABaseThrowable> ThrowableOne;
	TSoftClassPtr<ABaseThrowable> ThrowableTwo;

public:
	Inventory();
	~Inventory();

	void GetPlayerInventory(TArray<TSoftClassPtr<ABaseThrowable>>& arr);

	UClass* ThrowableOneClass();
	UClass* ThrowableTwoClass();
};
