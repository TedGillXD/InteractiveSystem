// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

class AItemActorBase;

UENUM(BlueprintType)
enum EItemType : uint8 {
	Default = 0
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class INTERACTIVESYSTEM_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();

public:			// 物品的基本属性
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Item Props")
	FName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Item Props")
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Item Props")
	TEnumAsByte<EItemType> ItemType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Item Props", meta=(ExposeOnSpawn = true))
	int Count;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Item Props")
	int MaxCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Item Props")
	bool bCanStack;
	
public:			// 物品的表现
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Item Props")
	UStaticMesh* Mesh;		// 物品的网格体

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Item Props")
	UTexture2D* Icon;		// 物品的Icon

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Item Props")
	TSubclassOf<AItemActorBase> ItemActor;		// 物品在世界中的表示形式

public:
	UFUNCTION(BlueprintPure, Category="Item Funcs")
	bool IsSameItem(const UItem* OtherItem) const { return this->Name.IsEqual(OtherItem->Name); }
	
	UFUNCTION(BlueprintPure, Category="Item Funcs")
	bool IsValid() const { return Count != 0 && Count <= MaxCount; }

	UFUNCTION(BlueprintCallable, Category="Item Funcs")
	void StackWith(UItem* OtherItem);
};
