// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActors/Lever.h"

#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ALever::ALever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	Lever = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever"));
	Base->SetupAttachment(Root);
	Lever->SetupAttachment(Root);
	Lever->SetSimulatePhysics(true);

	PhysicsConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("LeverAsix"));
	PhysicsConstraintComponent->SetupAttachment(Root);
	PhysicsConstraintComponent->SetConstrainedComponents(Base, FName{}, Lever, FName{});
	PhysicsConstraintComponent->SetAngularSwing2Limit(ACM_Limited, 50);
	
	bIsOn = false;
	PhysicsConstraintComponent->SetAngularOrientationTarget({-50.f, 0.f, 0.f});			// 关闭状态的默认旋转
	PhysicsConstraintComponent->SetAngularOrientationDrive(true, false);
	PhysicsConstraintComponent->SetAngularVelocityTarget({0.f, 0.f, 0.f});
	PhysicsConstraintComponent->SetAngularVelocityDrive(true, false);

	bShouldUpdate = false;
}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();
	
}

FString ALever::GetInteractText_Implementation() {
	return bIsOn ? NoticeStringOnOpen : NoticeStringOnClose;
}

void ALever::Interact_Implementation(UItem* InHandItem, AActor* FromActor) {
	bIsOn = !bIsOn;
	if(bIsOn) {
		PhysicsConstraintComponent->SetAngularOrientationTarget({50.f, 0.f, 0});
		Lever->WakeRigidBody();
	} else {
		PhysicsConstraintComponent->SetAngularOrientationTarget({-50.f, 0.f, 0});
		Lever->WakeRigidBody();
	}
	bShouldUpdate = true;
	OnLeverStatusChanged.Broadcast(bIsOn);
}

bool ALever::CanInteract_Implementation(UItem* InHandItem, AActor* FromActor) const {
	return true;
}

bool ALever::ShouldUpdate_Implementation() const {
	return bShouldUpdate;
}

void ALever::Updated_Implementation() {
	bShouldUpdate = false;
}
