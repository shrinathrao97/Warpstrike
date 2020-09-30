// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienManAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/FloatingPawnMovement.h"


UAlienManAnimInstance::UAlienManAnimInstance() 
{
	AnimPlayerSpeed = 0.0f;
	Owner = nullptr;
}

void UAlienManAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Owner = TryGetPawnOwner();
}

void UAlienManAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Owner) { return; }


	if (Owner->IsA(AMyCharacter::StaticClass())) {
	
		AMyCharacter* PC = Cast<AMyCharacter>(Owner);

		//Set required animation variables for use in blueprints
		AnimPlayerVelocity = PC->FloatingPawnMovement->Velocity;
		AnimPlayerSpeed = AnimPlayerVelocity.Size();
		AnimPlayerRotation = PC->GetActorRotation();
	
		//Sync isAttacking with MyCharacter.cpp
		isAttacking = PC->isAttacking;

	}

}


