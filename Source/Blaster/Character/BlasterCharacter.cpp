// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"

ABlasterCharacter::ABlasterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("this->bUseControllerRotationRoll =  %f"),this->bUseControllerRotationRoll);
	//UE_LOG(LogTemp, Warning, TEXT("this->bUseControllerRotationYaw =  %f"),this->bUseControllerRotationYaw);
	//UE_LOG(LogTemp, Warning, TEXT("this->bUseControllerRotationPitch =  %f"),this->bUseControllerRotationPitch);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // CharacterMovementComponent -> bOrientRotationMovement to rotate character's mesh towards movement input

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABlasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ABlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	//UE_LOG(LogTemp, Warning, TEXT("View Pitch Min: %f"), PC->PlayerCameraManager->ViewPitchMin);
    //UE_LOG(LogTemp, Warning, TEXT("View Pitch Max: %f"), PC->PlayerCameraManager->ViewPitchMax);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ACharacter::Jump); // uses derived function Jump. Will be changed later.

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABlasterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABlasterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABlasterCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABlasterCharacter::LookUp);
}

void ABlasterCharacter::MoveForward(float Value){
	if (Controller && Value != 0.f) {
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f); // controller's rotation around Y axis
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X)); // ???
		AddMovementInput(Direction, Value);
	}
}

void ABlasterCharacter::MoveRight(float Value){
	if (Controller && Value != 0.f) {
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y)); 
		AddMovementInput(Direction, Value);
	}
}

void ABlasterCharacter::Turn(float Value){
	AddControllerYawInput(Value);
}

void ABlasterCharacter::LookUp(float Value){
	// UE_LOG(LogTemp, Warning, TEXT("AddControllerPitchInput called with value: %f"), Value);
	AddControllerPitchInput(Value);
}

void ABlasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
