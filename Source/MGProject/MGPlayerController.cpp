// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "MGFlag.h"
#include "MGPlayerController.h"
#include "Character/MGPlayerCharacter.h"

void AMGPlayerController::InitInputSystem()
{
	Super::InitInputSystem();

	InputComponent->BindAxis(FName("MoveFront"), this, &AMGPlayerController::MoveFront);
	InputComponent->BindAxis(FName("MoveLeft"), this, &AMGPlayerController::MoveLeft);
	InputComponent->BindAxis(FName("MoveBack"), this, &AMGPlayerController::MoveBack);
	InputComponent->BindAxis(FName("MoveRight"), this, &AMGPlayerController::MoveRight);
	InputComponent->BindAxis(FName("MouseX"), this, &AMGPlayerController::MouseXMove);
	InputComponent->BindAxis(FName("MouseY"), this, &AMGPlayerController::MouseYMove);
	
	InputComponent->BindAction(FName("LeftMouseButton"), EInputEvent::IE_Pressed, this, &AMGPlayerController::LeftMouseButtonClick);
	InputComponent->BindAction(FName("RightMouseButton"), EInputEvent::IE_Pressed, this, &AMGPlayerController::RightMouseButtonClick);
	InputComponent->BindAction(FName("RightMouseButton"), EInputEvent::IE_Released, this, &AMGPlayerController::RightMouseButtonRelease);
	InputComponent->BindAction(FName("SkillQ"), EInputEvent::IE_Pressed, this, &AMGPlayerController::QButtonPress);
	InputComponent->BindAction(FName("SkillQ"), EInputEvent::IE_Released, this, &AMGPlayerController::QButtonRelease);
	InputComponent->BindAction(FName("SkillE"), EInputEvent::IE_Pressed, this, &AMGPlayerController::EButtonPress);
	InputComponent->BindAction(FName("SkillE"), EInputEvent::IE_Released, this, &AMGPlayerController::EButtonRelease);
}

void AMGPlayerController::BeginPlay()	
{
	PlayerCharacter = Cast<AMGPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	PlayerAimWidget = CreateWidget<UMGAimWidget>(this, PlayerWidget, TEXT("Player AimWidget"));
	PlayerAimWidget->AddToViewport(0);
	PlayerAimWidget->SetVisibility(ESlateVisibility::Hidden);
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

	switch (ActionState)
	{
	case ECharacter_ActionState::Normal:
	case ECharacter_ActionState::Aiming:
	{
		PlayerCharacter->GetAnimInst()->SetBodyActionState(ECharacter_BodyAction::NormalFire);
		PlayerCharacter->GetTrace();
		break;
	}

	case ECharacter_ActionState::QAiming:
	case ECharacter_ActionState::EAiming:
	default:
		break;
	}
}

void AMGPlayerController::RightMouseButtonClick()
{
	bRightMouseButtonPress = !bRightMouseButtonPress;

	ECharacter_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	UE_LOG(LogTemp, Log, TEXT("Pressed!!!"));
	switch (ActionState)
	{
	case ECharacter_ActionState::Normal:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();
		
		if (!ArmComponent)
			return;

		// StateMachine내 ActionState 설정 
		PlayerCharacter->GetAnimInst()->SetActionState(ECharacter_ActionState::Aiming);
		
		// CameraArm Length 및 SocketOffset 조정
		ArmComponent->TargetArmLength = 100.0f;
		ArmComponent->SocketOffset = FVector(0.0f, -60.0f, 30.0f);

		break;
	}

	case ECharacter_ActionState::Aiming:
	case ECharacter_ActionState::QAiming:
	case ECharacter_ActionState::EAiming:
	default:
		break;
	}
}

void AMGPlayerController::RightMouseButtonRelease()
{
	bRightMouseButtonPress = !bRightMouseButtonPress;

	ECharacter_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	switch (ActionState)
	{
	case ECharacter_ActionState::Aiming:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;

		// StateMachine내 ActionState 설정 
		PlayerCharacter->GetAnimInst()->SetActionState(ECharacter_ActionState::Normal);

		// CameraArm Length 및 SocketOffset 조정
		ArmComponent->TargetArmLength = 250.0f;
		ArmComponent->SocketOffset = FVector(0.0f, 0.0f, 0.0f);

		break;
	}

	case ECharacter_ActionState::Normal:
	case ECharacter_ActionState::QAiming:
	case ECharacter_ActionState::EAiming:
	default:
		break;
	}
}

void AMGPlayerController::QButtonPress()
{
	bQButtonPress = !bQButtonPress;

	ECharacter_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	switch (ActionState)
	{
	case ECharacter_ActionState::Normal:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;

		// StateMachine내 ActionState 설정 
		PlayerCharacter->GetAnimInst()->SetActionState(ECharacter_ActionState::QAiming);

		// CameraArm Length 및 SocketOffset 조정
		ArmComponent->TargetArmLength = 100.0f;
		ArmComponent->SocketOffset = FVector(0.0f, -60.0f, 30.0f);

		PlayerAimWidget->SetVisibility(ESlateVisibility::Visible);

		break;
	}

	case ECharacter_ActionState::Aiming:
	case ECharacter_ActionState::QAiming:
	case ECharacter_ActionState::EAiming:
	default:
		break;
	}
}

void AMGPlayerController::QButtonRelease()
{
	bRightMouseButtonPress = !bRightMouseButtonPress;

	ECharacter_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	switch (ActionState)
	{
	case ECharacter_ActionState::QAiming:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;

		// 발사여부에 따라서 Aiming 상태를 유지할 것인지 설정해야함.
		
		
		// 발사함 : 로켓발사하는 동안 QAiming 상태를 유지.
		if (!PlayerCharacter->IsTargetEmpty())
		{
			PlayerCharacter->GetAnimInst()->SetBodyActionState(ECharacter_BodyAction::QFire);

			// CameraArm Length 및 SocketOffset 조정
			ArmComponent->TargetArmLength = 250.0f;
			ArmComponent->SocketOffset = FVector(0.0f, 0.0f, 0.0f);


			PlayerAimWidget->SetVisibility(ESlateVisibility::Hidden);
			PlayerAimWidget->SetScopeActivate(false);
			PlayerCharacter->SetQSkillCollision(false);

		}

		// 발사안함 : 그대로 Normal 상태로 돌아오기.
		else
		{
			// StateMachine내 ActionState 설정 
			PlayerCharacter->GetAnimInst()->SetActionState(ECharacter_ActionState::Normal);

			// CameraArm Length 및 SocketOffset 조정
			ArmComponent->TargetArmLength = 250.0f;
			ArmComponent->SocketOffset = FVector(0.0f, 0.0f, 0.0f);


			PlayerAimWidget->SetVisibility(ESlateVisibility::Hidden);
			PlayerAimWidget->SetScopeActivate(false);
			PlayerCharacter->SetQSkillCollision(false);
		}

		break;
	}

	case ECharacter_ActionState::Normal:
	case ECharacter_ActionState::Aiming:
	case ECharacter_ActionState::EAiming:
	default:
		break;
	}
}

void AMGPlayerController::EButtonPress()
{
	bEButtonPress = !bEButtonPress;

	ECharacter_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	switch (ActionState)
	{
	case ECharacter_ActionState::Normal:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;

		// StateMachine내 ActionState 설정 
		PlayerCharacter->GetAnimInst()->SetActionState(ECharacter_ActionState::EAiming);

		// CameraArm Length 및 SocketOffset 조정
		ArmComponent->TargetArmLength = 100.0f;
		ArmComponent->SocketOffset = FVector(0.0f, -60.0f, 30.0f);

		

		// ParticleSystem Off
		PlayerCharacter->GetDroneParticleSystem()->SetVisibility(true);
		PlayerCharacter->GetDroneParticleSystem()->ActivateSystem();

		break;
	}
	default:
		break;
	}
}

void AMGPlayerController::EButtonRelease()
{
	bEButtonPress = !bEButtonPress;

	ECharacter_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	switch (ActionState)
	{
	case ECharacter_ActionState::EAiming:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;

		PlayerCharacter->GetAnimInst()->SetBodyActionState(ECharacter_BodyAction::EThrowing);

		// StateMachine내 ActionState 설정 
		PlayerCharacter->GetAnimInst()->SetActionState(ECharacter_ActionState::Normal);

		// CameraArm Length 및 SocketOffset 조정
		ArmComponent->TargetArmLength = 250.0f;
		ArmComponent->SocketOffset = FVector(0.0f, 0.0f, 0.0f);

		PlayerCharacter->GetDroneParticleSystem()->SetVisibility(false);
		PlayerCharacter->GetDroneParticleSystem()->DeactivateSystem();
		break;
	}
	default:
		break;
	}
}
