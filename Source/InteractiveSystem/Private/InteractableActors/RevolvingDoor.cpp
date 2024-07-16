// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActors/RevolvingDoor.h"

#include "InteractableActors/Lever.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ARevolvingDoor::ARevolvingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	SetRootComponent(Root);
	Base->SetupAttachment(Root);
	Door->SetupAttachment(Root);

	PhysicsConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Door Axis"));
	PhysicsConstraintComponent->SetupAttachment(Root);
	PhysicsConstraintComponent->SetAngularSwing1Limit(ACM_Free, 45);
	PhysicsConstraintComponent->SetAngularSwing2Limit(ACM_Locked, 45);
	PhysicsConstraintComponent->SetAngularTwistLimit(ACM_Locked, 360);
	PhysicsConstraintComponent->SetAngularVelocityDrive(true, false);
}

void ARevolvingDoor::OnLeverStatusChanged(bool bIsOn) {
	if(bIsOn) {
		Door->SetSimulatePhysics(true);
		PhysicsConstraintComponent->SetAngularVelocityTarget({0.f, 0.f, 0.2f});
		Door->WakeRigidBody();
	} else {
		Door->SetSimulatePhysics(false);
		PhysicsConstraintComponent->SetAngularVelocityTarget({0.f, 0.f, 0.f});
	}
}

// Called when the game starts or when spawned
void ARevolvingDoor::BeginPlay()
{
	Super::BeginPlay();

	// 绑定开关事件
	if(RelatedLever) {
		RelatedLever->OnLeverStatusChanged.AddDynamic(this, &ARevolvingDoor::OnLeverStatusChanged);
		OnLeverStatusChanged(RelatedLever->bIsOn);
	}
}