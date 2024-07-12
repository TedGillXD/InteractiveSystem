// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InventorySystemInterface.h"

// Add default functionality here for any IInventorySystem functions that are not pure virtual.
UInventoryComponent* IInventorySystemInterface::GetInventoryComponent_Implementation() const {
	return nullptr;
}
