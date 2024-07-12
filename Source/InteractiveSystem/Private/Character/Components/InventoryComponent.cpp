// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/InventoryComponent.h"

#include "Items/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	MaxCapacity = 30;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UInventoryComponent::AddItem(UItem* NewItem) {
	if(Inventory.Num() >= MaxCapacity || !NewItem || !NewItem->IsValid()) {
		return false;
	}

	// 1. 如果能堆叠，找到能堆叠的物品
	if(NewItem->bCanStack) {
		for(UItem* Item : Inventory) {
			if(Item->IsSameItem(NewItem)) {
				Item->StackWith(NewItem);
			}
		}
	}

	// 2. 如果在堆叠后NewItem仍然合法，则将其加入到背包的尾部
	if(NewItem->IsValid()) {
		Inventory.Add(NewItem);
	}

	OnInventoryChanged.Broadcast(Inventory);
	return true;
}

UItem* UInventoryComponent::RemoveItemByIndex(int32 Index) {
	if(Index >= Inventory.Num() || Index < 0) {
		return nullptr;
	}

	UItem* Ret = Inventory[Index];
	Inventory.RemoveAt(Index);
	OnInventoryChanged.Broadcast(Inventory);
	return Ret;
}

int32 UInventoryComponent::ContainsItem(const FName ItemName) {
	for(int32 Index = 0; Index < Inventory.Num(); Index++) {
		if(Inventory[Index]->Name.IsEqual(ItemName)) {
			return Index;
		}
	}

	return -1;
}

