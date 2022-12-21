// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayerController.h"
#include "Character/MGCharacter.h"
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
}

void AMGPlayerController::MoveFront(float Value)
{	
	if (Value == 0.0f)
		return;

	ACharacter* pCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!pCharacter || !pCharacter->IsValidLowLevel())
		return;

	USpringArmComponent* ArmComponent = Cast<USpringArmComponent>(pCharacter->FindComponentByClass(USpringArmComponent::StaticClass()));

	if (!ArmComponent || !ArmComponent->IsValidLowLevel())
		return;

	FVector ForwardVector = ArmComponent->GetForwardVector();

	pCharacter->AddMovementInput(ForwardVector);
}

void AMGPlayerController::MoveLeft(float Value)
{
	if (Value == 0.0f)
		return;

	ACharacter* pCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!pCharacter || !pCharacter->IsValidLowLevel())
		return;

	USpringArmComponent* ArmComponent = Cast<USpringArmComponent>(pCharacter->FindComponentByClass(USpringArmComponent::StaticClass()));

	if (!ArmComponent || !ArmComponent->IsValidLowLevel())
		return;

	FVector RightVector = ArmComponent->GetRightVector();

	pCharacter->AddMovementInput(-RightVector);
}

void AMGPlayerController::MoveRight(float Value)
{
	if (Value == 0.0f)
		return;

	ACharacter* pCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!pCharacter || !pCharacter->IsValidLowLevel())
		return;

	USpringArmComponent* ArmComponent = Cast<USpringArmComponent>(pCharacter->FindComponentByClass(USpringArmComponent::StaticClass()));

	if (!ArmComponent || !ArmComponent->IsValidLowLevel())
		return;

	pCharacter->AddMovementInput(ArmComponent->GetRightVector());
}

void AMGPlayerController::MoveBack(float Value)
{
	if (Value == 0.0f)
		return;

	ACharacter* pCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!pCharacter || !pCharacter->IsValidLowLevel())
		return;
	
	USpringArmComponent* ArmComponent = Cast<USpringArmComponent>(pCharacter->FindComponentByClass(USpringArmComponent::StaticClass()));

	if (!ArmComponent || !ArmComponent->IsValidLowLevel())
		return;

	FVector ForwardVector = ArmComponent->GetForwardVector();
	
	pCharacter->AddMovementInput(-ForwardVector);
}

void AMGPlayerController::MouseXMove(float Value)
{
	if (Value == 0.0f)
		return;

	AMGPlayerCharacter* pPlayerCharacter = Cast<AMGPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!pPlayerCharacter || !pPlayerCharacter->IsValidLowLevel())
		return;

	FRotator Rotation = pPlayerCharacter->GetSpringArmComponent()->GetRelativeRotation();

	Rotation.Add(0.0f, Value, 0.0f);

	pPlayerCharacter->GetSpringArmComponent()->SetRelativeRotation(Rotation);

}

void AMGPlayerController::MouseYMove(float Value)
{
	if (Value == 0.0f)
		return;

	AMGPlayerCharacter* pPlayerCharacter = Cast<AMGPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!pPlayerCharacter || !pPlayerCharacter->IsValidLowLevel())
		return;

	FRotator Rotation = pPlayerCharacter->GetSpringArmComponent()->GetRelativeRotation();
	
	Rotation.Add(Value, 0.0f, 0.0f);
	
	pPlayerCharacter->GetSpringArmComponent()->SetRelativeRotation(Rotation);
}
