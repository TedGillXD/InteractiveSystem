// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RevolvingDoor.generated.h"

class UPhysicsConstraintComponent;
class ALever;

UCLASS()
class INTERACTIVESYSTEM_API ARevolvingDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARevolvingDoor();

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	ALever* RelatedLever;		// 用来绑定状态的Lever

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	USceneComponent* Root;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaticMeshComponent* Base;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaticMeshComponent* Door;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UPhysicsConstraintComponent* PhysicsConstraintComponent;

	UFUNCTION()
	void OnLeverStatusChanged(bool bIsOn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
};
