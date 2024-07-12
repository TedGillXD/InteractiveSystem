// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemActorBase.h"

#include "Character/Components/InventoryComponent.h"
#include "Interfaces/InventorySystemInterface.h"

// Sets default values
AItemActorBase::AItemActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	MeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);		// Channel1 == Interactable
	Count = 1;
}

// Called when the game starts or when spawned
void AItemActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActorBase::Interact_Implementation(UItem* InHandItem, AActor* FromActor) {
	if(!FromActor || !FromActor->IsValidLowLevel()) {
		return;
	}

	if(IInventorySystemInterface* ActorWithInventory = Cast<IInventorySystemInterface>(FromActor); ActorWithInventory) {
		if(auto InventoryComp = IInventorySystemInterface::Execute_GetInventoryComponent(FromActor); InventoryComp->AddItem(GetItemRef())) {
			this->Destroy();
		} else {
			UE_LOG(LogTemp, Error, TEXT("Failed to add item into Inventory"));
		}
	}
}

bool AItemActorBase::CanInteract_Implementation(UItem* InHandItem, AActor* FromActor) const {
	if(!FromActor || !FromActor->IsValidLowLevel()) {
		return false;
	}

	return FromActor->Implements<UInventorySystemInterface>();		// 检查互动的Actor是否已经实现了Inventory接口
}

UItem* AItemActorBase::GetItemRef_Implementation() {
	return nullptr;
}

