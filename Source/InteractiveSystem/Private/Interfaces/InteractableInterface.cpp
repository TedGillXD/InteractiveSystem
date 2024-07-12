// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InteractableInterface.h"
#include "Items/Item.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.
bool IInteractableInterface::CanInteract_Implementation(UItem* InHandItem, AActor* FromActor) const {
	return false;
}

void IInteractableInterface::Interact_Implementation(UItem* InHandItem, AActor* FromActor) { }

FString IInteractableInterface::GetInteractText_Implementation() {
	return "";
}

bool IInteractableInterface::ShouldUpdate_Implementation() const {
	return false;
}

void IInteractableInterface::Updated_Implementation() { }
