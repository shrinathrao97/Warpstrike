// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "MyCharacter.h"
#include "Components/TextRenderComponent.h"
#include "Math/Color.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//This will hold whether the enemy has been selected by player or not
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	TargetArrow = CreateDefaultSubobject<UTextRenderComponent>("TextArrow");
	TargetArrow->SetText(" ");

	SetRootComponent(mesh);
	TargetArrow->SetupAttachment(mesh);

	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{

	Super::BeginPlay();
	
	//On spawn add this enemy to a datastructure on the player
	APawn *mypawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(mypawn);
	MyCharacter->AddEnemy(this);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
