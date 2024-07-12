// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActors/Door.h"

#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Base->SetupAttachment(Root);
	Door->SetupAttachment(Root);

	DoorAxis = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("DoorAxis"));
	DoorAxis->SetupAttachment(Root);
	DoorAxis->SetConstrainedComponents(Base, FName{}, Door, FName{});
	
	bShouldUpdate = false;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ADoor::CanInteract_Implementation(UItem* InHandItem, AActor* FromActor) const {
	return true;
}

void ADoor::Interact_Implementation(UItem* InHandItem, AActor* FromActor) {
	if(bIsOpen) {
		// 关门
		DoorAxis->SetAngularOrientationTarget({0.f, 0.f, 0.f});
		Door->WakeRigidBody();
	} else {
		// 开门
		DoorAxis->SetAngularOrientationTarget({0.f, 75.f, 0.f});
		Door->WakeRigidBody();
	}
	bIsOpen = !bIsOpen;
	bShouldUpdate = true;
}

FString ADoor::GetInteractText_Implementation() {
	return bIsOpen ? NoticeStringOnOpen : NoticeStringOnClose;
}

bool ADoor::ShouldUpdate_Implementation() const {
	return bShouldUpdate;
}

void ADoor::Updated_Implementation() {
	bShouldUpdate = false;
}

