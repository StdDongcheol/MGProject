// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayerController.h"
#include "MGFlag.h"
#include "Character/MGPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

void AMGPlayerController::InitInputSystem()
{
	Super::InitInputSystem();

	InputComponent->BindAxis(FName("MoveFront"), this, &AMGPlayerController::MoveFront);
	InputComponent->BindAxis(FName("MoveLeft"), this, &AMGPlayerController::MoveLeft);
	InputComponent->BindAxis(FName("MoveBack"), this, &AMGPlayerController::MoveBack);
	InputComponent->BindAxis(FName("MoveRight"), this, &AMGPlayerController::MoveRight);
	InputComponent->BindAxis(FName("MouseX"), this, &AMGPlayerController::MouseXMove);
	InputComponent->BindAxis(FName("MouseY"), this, &AMGPlayerController::MouseYMove);
	//InputComponent->BindAxis(FName("RightMouseButton"), this, &AMGPlayerController::RightMouseButtonAxis);

	InputComponent->BindAction(FName("LeftMouseButton"), EInputEvent::IE_Pressed, this, &AMGPlayerController::LeftMouseButtonClick);
	InputComponent->BindAction(FName("RightMouseButton"), EInputEvent::IE_Pressed, this, &AMGPlayerController::RightMouseButtonClick);
	InputComponent->BindAction(FName("RightMouseButton"), EInputEvent::IE_Released, this, &AMGPlayerController::RightMouseButtonRelease);
}

void AMGPlayerController::BeginPlay()
{
	PlayerCharacter = Cast<AMGPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AMGPlayerController::MoveFront(float Value)
{	
	if (Value == 0.0f)
		return;

	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	USpringArmComponent* ArmComponent = Cast<USpringArmComponent>(PlayerCharacter->FindComponentByClass(USpringArmComponent::StaticClass()));

	if (!ArmComponent || !ArmComponent->IsValidLowLevel())
		return;

	FVector ForwardVector = ArmComponent->GetForwardVector();

	PlayerCharacter->AddMovementInput(ForwardVector);
}

void AMGPlayerController::MoveLeft(float Value)
{
	if (Value == 0.0f)
		return;

	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	USpringArmComponent* ArmComponent = Cast<USpringArmComponent>(PlayerCharacter->FindComponentByClass(USpringArmComponent::StaticClass()));

	if (!ArmComponent || !ArmComponent->IsValidLowLevel())
		return;

	FVector RightVector = ArmComponent->GetRightVector();

	PlayerCharacter->AddMovementInput(-RightVector);
}

void AMGPlayerController::MoveRight(float Value)
{
	if (Value == 0.0f)
		return;

	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	USpringArmComponent* ArmComponent = Cast<USpringArmComponent>(PlayerCharacter->FindComponentByClass(USpringArmComponent::StaticClass()));

	if (!ArmComponent || !ArmComponent->IsValidLowLevel())
		return;

	PlayerCharacter->AddMovementInput(ArmComponent->GetRightVector());
}

void AMGPlayerController::MoveBack(float Value)
{
	if (Value == 0.0f)
		return;

	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;
	
	USpringArmComponent* ArmComponent = Cast<USpringArmComponent>(PlayerCharacter->FindComponentByClass(USpringArmComponent::StaticClass()));

	if (!ArmComponent || !ArmComponent->IsValidLowLevel())
		return;

	FVector ForwardVector = ArmComponent->GetForwardVector();
	
	PlayerCharacter->AddMovementInput(-ForwardVector);
}

void AMGPlayerController::MouseXMove(float Value)
{
	if (Value == 0.0f)
		return;

	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	FRotator Rotation = PlayerCharacter->GetSpringArmComponent()->GetRelativeRotation();

	Rotation.Add(0.0f, Value, 0.0f);

	PlayerCharacter->GetSpringArmComponent()->SetRelativeRotation(Rotation);

}

void AMGPlayerController::MouseYMove(float Value)
{
	if (Value == 0.0f)
		return;

	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	FRotator Rotation = PlayerCharacter->GetSpringArmComponent()->GetRelativeRotation();
	
	Rotation.Add(Value, 0.0f, 0.0f);
	
	PlayerCharacter->GetSpringArmComponent()->SetRelativeRotation(Rotation);
}

void AMGPlayerController::LeftMouseButtonClick()
{
	ECharacter_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	PlayerCharacter->GetAnimInst()->SetFire(true);
}

void AMGPlayerController::RightMouseButtonClick()
{
	ECharacter_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();
	UE_LOG(LogTemp, Log, TEXT("Pressed!!!"));
	switch (ActionState)
	{
	case ECharacter_ActionState::Normal:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();
		
		if (!ArmComponent)
			return;

		PlayerCharacter->GetAnimInst()->SetActionState(ECharacter_ActionState::Aiming);
		
		// CameraArm Length 및 SocketOffset 조정
		ArmComponent->TargetArmLength = 150.0f;
		ArmComponent->SocketOffset = FVector(0.0f, -40.0f, 0.0f);

		break;
	}

	case ECharacter_ActionState::Aiming:
	default:
		break;
	}
}

void AMGPlayerController::RightMouseButtonAxis(float Value)
{
	if (Value == 0.0f)
		return;

	ECharacter_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();
	UE_LOG(LogTemp, Log, TEXT("Pressed!!!"));
	switch (ActionState)
	{
	case ECharacter_ActionState::Normal:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;

		PlayerCharacter->GetAnimInst()->SetActionState(ECharacter_ActionState::Aiming);

		// CameraArm Length 및 SocketOffset 조정
		ArmComponent->TargetArmLength = 150.0f;
		ArmComponent->SocketOffset = FVector(0.0f, -40.0f, 0.0f);

		break;
	}

	case ECharacter_ActionState::Aiming:
	default:
		break;
	}

}

void AMGPlayerController::RightMouseButtonRelease()
{
	ECharacter_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	switch (ActionState)
	{
	case ECharacter_ActionState::Aiming:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;
		
		PlayerCharacter->GetAnimInst()->SetActionState(ECharacter_ActionState::Normal);

		// CameraArm Length 및 SocketOffset 조정
		ArmComponent->TargetArmLength = 250.0f;
		ArmComponent->SocketOffset = FVector(0.0f, 0.0f, 0.0f);

		break;
	}

	case ECharacter_ActionState::Normal:
	default:
		break;
	}
}
