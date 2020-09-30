// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AlienManAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HELLO_API UAlienManAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Instance")
		float AnimPlayerSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Instance")
		FVector AnimPlayerVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Instance")
		FRotator AnimPlayerRotation;
	
	//Local isAttacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Instance")
		bool isAttacking;

	//Functions and Overrides
	UAlienManAnimInstance();
	void NativeInitializeAnimation() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;


private:

	//Store reference to owner pawn
	APawn* Owner;
};
