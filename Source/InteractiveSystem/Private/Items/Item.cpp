// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"

UItem::UItem() {
	ItemType = EItemType::Default;
	Count = 0;
	bCanStack = true;
	MaxCount = 16;
	
}

void UItem::StackWith(UItem* OtherItem) {
	// 输入是nullptr，或者输入的ItemCount是0，或者该物品无法堆叠，或者this和OtherItem的名字不同，都无法进行堆叠
	if(!OtherItem || !OtherItem->IsValidLowLevel() || !OtherItem->IsValid() || !this->bCanStack || !this->Name.IsEqual(OtherItem->Name) || this->Count >= this->MaxCount) {
		return;
	}

	int Original = this->Count;
	const int32 TotalCount = this->Count + OtherItem->Count;
	this->Count = FMath::Min(TotalCount, this->MaxCount);
	OtherItem->Count = FMath::Max(OtherItem->Count - (this->Count - Original), 0);
}
