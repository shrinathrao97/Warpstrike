#include "MyCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enemy.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;


	//Make Static Mesh for Visuals
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");

	//Capsule
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>("Capsule");

	//Make Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm")
	SpringArm->TargetArmLength = 300;
	SpringArm->bUsePawnControlRotation = true;

	//Make Camera
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->bUsePawnControlRotation = true;

	

	//Make Controller
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Controller");

	//Setup RootNode and heirarchy
	SetRootComponent(CapsuleCollider);
	SkeletalMesh->SetupAttachment(CapsuleCollider);
	SpringArm->SetupAttachment(CapsuleCollider);
	Camera->SetupAttachment(SpringArm);

	//Animation Vars
	canMove = true;

	//Yaw and Pitch off the controller to false
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	//Shader Variables
	EmmissiveAdj = 0.0;
	FresnelOnOff = 0.08f;
	Mat_Opacity = 0.0f;

	//Enemy Array Init
	enemies.Empty();

	


}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();


	//SelectEnemy();
	
}



// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Camera Free Look on StandStill
	if (FloatingPawnMovement->Velocity.Size() == 0) {
	
		bUseControllerRotationYaw = false;
	
	}

	if (FloatingPawnMovement->Velocity.Size() != 0) {
	
		bUseControllerRotationYaw = true;
	
	}

	if (isWarping == true)
	{

		Warp();
		isWarping = false;

	}

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	InputComponent->BindAction("Attack", IE_Pressed, this , &AMyCharacter::Attack);
	InputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUp);
	InputComponent->BindAxis("Turn", this, &AMyCharacter::Turn);
	InputComponent->BindAction("EnemyGrab", IE_Pressed, this, &AMyCharacter::SelectEnemy);

}

//Add enemy to list
//Called by Enemy Class
void AMyCharacter::AddEnemy(AEnemy *enemy)
{
	enemies.Add(enemy);
}

//Input Handling Functions
void AMyCharacter::MoveForward(float moveSpeed)
{

	if(canMove)
	{
		FloatingPawnMovement->AddInputVector(GetActorForwardVector() * moveSpeed);
	}
	
}

void AMyCharacter::MoveRight(float moveSpeed)
{
	if(canMove)
	{
	
		FloatingPawnMovement->AddInputVector(GetActorRightVector() * moveSpeed);
		
	}

}

void AMyCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);

}

void AMyCharacter::Turn(float Amount)
{
	if(canMove)
	{
		AddControllerYawInput(Amount);
	}
	
}

//Attacking/Warping Functions
//Actual Attack event handled by blueprints
void AMyCharacter::Attack()
{
	if (Target != nullptr) {
		isAttacking = true;
		canMove = false;


	}
	
}

//Warp Handling
void AMyCharacter::Warp()
{
	SkeletalMesh->SetScalarParameterValueOnMaterials("EmmissiveAdj", EmmissiveAdj);
	SkeletalMesh->SetScalarParameterValueOnMaterials("FresnelOnOff", FresnelOnOff);
	SetActorLocation(Target->GetActorLocation());

}

//Get nearest enemy and select it
void AMyCharacter::SelectEnemy()
{
	//Find closest
	AEnemy* closest = nullptr;
	for (int i = 0; i < enemies.Max()- 1; i++) {

		if (closest == nullptr) {
		
			closest = enemies[i];
		
		}

		if (GetDistanceTo(enemies[i]) <= GetDistanceTo(closest)) {

			closest = enemies[i];


		}

	}

	//Turn off the current target if alls gone well
	if (Target != nullptr && Target->GetName() != closest->GetName()) {
		Target->TargetArrow->SetText(" ");
	}

	//Make closest our new target
	Target = closest;
	Target->TargetArrow->SetText("^");
	Target->TargetArrow->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Target->GetName());


}



