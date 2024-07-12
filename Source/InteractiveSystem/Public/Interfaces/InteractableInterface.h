// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INTERACTIVESYSTEM_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	bool CanInteract(UItem* InHandItem, AActor* FromActor) const;							// 获取当前的Actor是否能互动
	virtual bool CanInteract_Implementation(UItem* InHandItem, AActor* FromActor) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void Interact(UItem* InHandItem, AActor* FromActor);				// 与Actor互动
	virtual void Interact_Implementation(UItem* InHandItem, AActor* FromActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	FString GetInteractText();											// 获取当前Actor的互动数据
	virtual FString GetInteractText_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	bool ShouldUpdate() const;												// 检查当前所指向的物体是否需要主动更新
	virtual bool ShouldUpdate_Implementation() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void Updated();
	virtual void Updated_Implementation();
};
