// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "Lever.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeverStatusChanged, bool, IsOn);

class UPhysicsConstraintComponent;

UCLASS()
class INTERACTIVESYSTEM_API ALever : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALever();

	UPROPERTY()
	USceneComponent* Root;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaticMeshComponent* Base;			// 开关的底座

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaticMeshComponent* Lever;		// 开关上面的那个杆子

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UPhysicsConstraintComponent* PhysicsConstraintComponent;		// 用来控制Lever位置的物理约束

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString NoticeStringOnOpen;		// 开关打开时互动的文字

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString NoticeStringOnClose;		// 开关关闭时互动的文字

	UPROPERTY(BlueprintReadOnly)
	bool bIsOn;			// 是否是开启状态

	UPROPERTY(BlueprintReadOnly, BlueprintAssignable)
	FOnLeverStatusChanged OnLeverStatusChanged;		// 当Lever状态改变时进行广播

private:
	bool bShouldUpdate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual FString GetInteractText_Implementation() override;
	virtual void Interact_Implementation(UItem* InHandItem, AActor* FromActor) override;
	virtual bool CanInteract_Implementation(UItem* InHandItem, AActor* FromActor) const override;
	virtual bool ShouldUpdate_Implementation() const override;
	virtual void Updated_Implementation() override;
};
