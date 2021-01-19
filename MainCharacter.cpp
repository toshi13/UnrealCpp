// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Don't rotate when the controller rotates. let that just affect the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Character moves in the direction of input ...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 1000.0f);

	// Create a camera boom (pulls towards  the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;  // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; //Rotate the arm based on the controller

	//Create a follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); //Attach the camera to the end of the boom and let the boom adjust to match the Controller orientation
	FollowCamera->bUsePawnControlRotation = false; //Camera does not rotate relative to arm

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released, this, &ACharacter::StopJumping);


}


void AMainCharacter::MoveForward(float Value) {
	if ((Controller != NULL) && (Value != 0.0f)) {
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}


void AMainCharacter::MoveRight(float Value) {
	if ((Controller != NULL) && (Value != 0.0f)) {
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward right
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}



