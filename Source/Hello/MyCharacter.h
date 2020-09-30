// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyCharacter.generated.h"

class AEnemy;

UCLASS()
class HELLO_API AMyCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;

	//Functions
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void LookUp(float Amount);
	void Turn(float Amount);
	void Attack();
	void SelectEnemy();
	void Warp();


	//Vars and Data structures
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		TArray<AEnemy*> enemies;
	float EmmissiveAdj;
	float FresnelOnOff;
	float Mat_Opacity;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Funcs
	void AddEnemy(AEnemy* enemy);


	//Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Physics")
		class UCapsuleComponent* CapsuleCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
		USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		class UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
		class USpringArmComponent* SpringArm;


	//Vars
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool canMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		AEnemy* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool isWarping;
	
};
