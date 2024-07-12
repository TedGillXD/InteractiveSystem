// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "Door.generated.h"

class UPhysicsConstraintComponent;

UCLASS()
class INTERACTIVESYSTEM_API ADoor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	USceneComponent* Root;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaticMeshComponent* Base;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaticMeshComponent* Door;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UPhysicsConstraintComponent* DoorAxis;		// 门轴

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bIsOpen;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Door Props")
	FString NoticeStringOnOpen;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Door Props")
	FString NoticeStringOnClose;

private:
	bool bShouldUpdate;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual bool CanInteract_Implementation(UItem* InHandItem, AActor* FromActor) const override;
	virtual void Interact_Implementation(UItem* InHandItem, AActor* FromActor) override;
	virtual FString GetInteractText_Implementation() override;
	virtual bool ShouldUpdate_Implementation() const override;
	virtual void Updated_Implementation() override;
};
