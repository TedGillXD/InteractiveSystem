// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryChanged, const TArray<UItem*>&, Inventory);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTIVESYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	UPROPERTY(BlueprintReadOnly, Category="Inventory Props")
	TArray<UItem*> Inventory;

	UPROPERTY(BlueprintReadOnly, Category="Inventory Props")
	int32 MaxCapacity;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category="Inventory Funcs")
	bool AddItem(UItem* NewItem);

	UFUNCTION(BlueprintCallable, Category="Inventory Funcs")
	UItem* RemoveItemByIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category="Inventory Funcs")
	int32 ContainsItem(FName ItemName);

	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Inventory Funcs")
	FOnInventoryChanged OnInventoryChanged;
};
