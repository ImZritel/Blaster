// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SphereComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true; // to replicate on the server

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	//WeaponMesh->SetupAttachment(RootComponent);
	SetRootComponent(WeaponMesh);
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block); // to make mesh collide woth objects...
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);  // but ignore collision with Pawn
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // when the weapon spawns it doesn't collide with anything until it's picked up and thrown

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore); // make AreaSphere ignored by default...
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision); // to make it detectable only on Server changing its state in BeginPlay
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	if(HasAuthority()) // we are on server (GetLocalRole() == ENetRole::ROLE_Authority)
	{
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

