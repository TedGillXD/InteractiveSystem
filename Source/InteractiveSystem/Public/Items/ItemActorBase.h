// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "ItemActorBase.generated.h"

class UItem;

UCLASS()
class INTERACTIVESYSTEM_API AItemActorBase : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActorBase();

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="ItemActor Props")
	UStaticMeshComponent* MeshComponent;		// 物体的Mesh

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="ItemActor Props")
	int32 Count;		// 物品的数量
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(UItem* InHandItem, AActor* FromActor) override;

	virtual bool CanInteract_Implementation(UItem* InHandItem, AActor* FromActor) const override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="ItemActor Funcs")
	UItem* GetItemRef();
	virtual UItem* GetItemRef_Implementation();
};
