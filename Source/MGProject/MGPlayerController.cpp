

#include "MGPlayerController.h"
#include "MGFlag.h"
#include "MGBlueprintFunctionLibrary.h"
#include "Interaction/MGInteraction_Input.h"
#include "Components/CapsuleComponent.h"
#include "UI/MGAimWidget.h"
#include "UI/MGNormalAimWidget.h"
#include "UI/MGPlayerWidget.h"
#include "Character/MGPlayerCharacter.h"
#include "Animation/MGPlayerAnimInstance.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void AMGPlayerController::InitInputSystem()
{
	Super::InitInputSystem();

	InputComponent->BindAxis(FName("MoveFront"), this, &AMGPlayerController::MoveFront);
	InputComponent->BindAxis(FName("MoveLeft"), this, &AMGPlayerController::MoveLeft);
	InputComponent->BindAxis(FName("MoveBack"), this, &AMGPlayerController::MoveBack);
	InputComponent->BindAxis(FName("MoveRight"), this, &AMGPlayerController::MoveRight);
	InputComponent->BindAxis(FName("MouseX"), this, &AMGPlayerController::MouseXMove);
	InputComponent->BindAxis(FName("MouseY"), this, &AMGPlayerController::MouseYMove);
	InputComponent->BindAxis(FName("LeftMouseButton"), this, &AMGPlayerController::LeftMouseButtonAxis);
	
	InputComponent->BindAction(FName("RightMouseButton"), EInputEvent::IE_Pressed, this, &AMGPlayerController::RightMouseButtonClick);
	InputComponent->BindAction(FName("RightMouseButton"), EInputEvent::IE_Released, this, &AMGPlayerController::RightMouseButtonRelease);
	InputComponent->BindAction(FName("SkillQ"), EInputEvent::IE_Pressed, this, &AMGPlayerController::QButtonPress);
	InputComponent->BindAction(FName("SkillQ"), EInputEvent::IE_Released, this, &AMGPlayerController::QButtonRelease);
	InputComponent->BindAction(FName("SkillE"), EInputEvent::IE_Pressed, this, &AMGPlayerController::EButtonPress);
	InputComponent->BindAction(FName("SkillE"), EInputEvent::IE_Released, this, &AMGPlayerController::EButtonRelease);
	InputComponent->BindAction(FName("Interaction"), EInputEvent::IE_Pressed, this, &AMGPlayerController::FButtonPress);
	InputComponent->BindAction(FName("Interaction"), EInputEvent::IE_Released, this, &AMGPlayerController::FButtonRelease);
	InputComponent->BindAction(FName("SetFireMode"), EInputEvent::IE_Pressed, this, &AMGPlayerController::RButtonPress);
	InputComponent->BindAction(FName("Dash"), EInputEvent::IE_Pressed, this, &AMGPlayerController::ShiftButtonPress);
	InputComponent->BindAction(FName("CheatOn"), EInputEvent::IE_Pressed, this, &AMGPlayerController::CheatKeyPress);
}

void AMGPlayerController::BeginPlay()	
{
	Super::BeginPlay();
	
	PlayerCharacter = Cast<AMGPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	PlayerQAimWidget = CreateWidget<UMGAimWidget>(this, PlayerWidget, TEXT("Player AimWidget"));
	PlayerQAimWidget->AddToViewport(9);
	PlayerQAimWidget->SetVisibility(ESlateVisibility::Hidden);

	PlayerNormalAimWidget = CreateWidget<UMGNormalAimWidget>(this, PlayerNormalAimWBP, TEXT("PlayerNormalAimWidget"));
	PlayerNormalAimWidget->AddToViewport(9);
	PlayerNormalAimWidget->SetVisibility(ESlateVisibility::Hidden);

	PlayerStatusWidget = CreateWidget<UMGPlayerWidget>(this, PlayerStatusWBP, TEXT("PlayerStatusWidget"));
	PlayerStatusWidget->AddToViewport(8);
	PlayerStatusWidget->SetVisibility(ESlateVisibility::Visible);

	PlayerStatusWidget->StageStart();
}

void AMGPlayerController::WidgetStart()
{
	PlayerStatusWidget->StageStart();
}

void AMGPlayerController::WidgetEnd()
{
	PlayerStatusWidget->StageEnd();
}

void AMGPlayerController::PlayerDeath()
{
	PlayerStatusWidget->SetPlayerDeathWidget();
}

void AMGPlayerController::SetCursor(bool bEnable)
{
	SetShowMouseCursor(bEnable);
	bEnableClickEvents = bEnable;
	bEnableMouseOverEvents = bEnable;
}

void AMGPlayerController::MoveFront(float Value)
{	
	if (Value == 0.0f)
		return;

	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	bool bCheck = (bool)(PlayerCharacter->GetStatus());

	EPlayer_BodyAction PlayerAction = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetBodyActionState();
	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	if (bCheck ||
		PlayerAction == EPlayer_BodyAction::NormalFire ||
		ActionState == EPlayer_ActionState::Dash)
	{
		return;
	}


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

	bool bCheck = (bool)(PlayerCharacter->GetStatus());

	EPlayer_BodyAction PlayerAction = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetBodyActionState();
	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	if (bCheck ||
		PlayerAction == EPlayer_BodyAction::NormalFire ||
		ActionState == EPlayer_ActionState::Dash)
	{
		return;
	}


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

	bool bCheck = (bool)(PlayerCharacter->GetStatus());

	EPlayer_BodyAction PlayerAction = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetBodyActionState();
	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	if (bCheck ||
		PlayerAction == EPlayer_BodyAction::NormalFire ||
		ActionState == EPlayer_ActionState::Dash)
	{
		return;
	}

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

	bool bCheck = (bool)(PlayerCharacter->GetStatus());
	
	EPlayer_BodyAction PlayerAction = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetBodyActionState();
	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	if (bCheck ||
		PlayerAction == EPlayer_BodyAction::NormalFire ||
		ActionState == EPlayer_ActionState::Dash)
	{
		return;
	}

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

	bool bCheck = (bool)(PlayerCharacter->GetStatus() & ECharacter_Status::Death);

	if (bCheck)
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

	bool bCheck = (bool)(PlayerCharacter->GetStatus() & ECharacter_Status::Death);

	if (bCheck)
		return;

	FRotator Rotation = PlayerCharacter->GetSpringArmComponent()->GetRelativeRotation();
	
	Rotation.Add(Value, 0.0f, 0.0f);
	
	PlayerCharacter->GetSpringArmComponent()->SetRelativeRotation(Rotation);
}

void AMGPlayerController::LeftMouseButtonAxis(float Value)
{
	if (Value == 0.0f)
		return;

	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	bool bCheck = (bool)(PlayerCharacter->GetStatus());

	if (bCheck)
	{
		return;
	}

	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	switch (ActionState)
	{
	case EPlayer_ActionState::Aiming:
	{
		if (PlayerCharacter->IsChargeFireMode() && PlayerCharacter->IsChargeReady)
		{
			PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetBodyActionState(EPlayer_BodyAction::NormalFire);
			PlayerCharacter->UseChargeShot();
			PlayerStatusWidget->PlayChargeFire();
			break;
		}
		
		else if (!PlayerCharacter->IsChargeFireMode())
		{
			PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetBodyActionState(EPlayer_BodyAction::RapidFire);
			break;
		}

		break;
	}
	case EPlayer_ActionState::Normal:
	case EPlayer_ActionState::QAiming:
	case EPlayer_ActionState::EAiming:
	default:
		break;
	}
}

void AMGPlayerController::LeftMouseButtonClick()
{
	bool bCheck = (bool)(PlayerCharacter->GetStatus());

	if (bCheck)
	{
		return;
	}

	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	switch (ActionState)
	{
	case EPlayer_ActionState::Aiming:
	{
		PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetBodyActionState(EPlayer_BodyAction::NormalFire);
		
		// Trace debug test
		PlayerCharacter->GetTrace();
		break;
	}

	case EPlayer_ActionState::Normal:
	case EPlayer_ActionState::QAiming:
	case EPlayer_ActionState::EAiming:
	default:
		break;
	}
}

void AMGPlayerController::RightMouseButtonClick()
{
	bool bCheck = (bool)(PlayerCharacter->GetStatus());

	if (bCheck)
	{
		return;
	}

	bRightMouseButtonPress = !bRightMouseButtonPress;

	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	switch (ActionState)
	{
	case EPlayer_ActionState::Normal:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();
		UCameraComponent* CamComponent = PlayerCharacter->GetCameraComponent();
		
		if (!ArmComponent || !CamComponent)
			return;

		// StateMachine내 ActionState 설정 
		PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetActionState(EPlayer_ActionState::Aiming);

		// CameraArm Length 및 SocketOffset 조정
		if (PlayerCharacter->IsChargeFireMode())
		{
			if (PlayerCharacter->IsChargeEnable())
				PlayerNormalAimWidget->SetBossWeakpointWidget(true);

			PlayerNormalAimWidget->SwtichAimWidget(true);
			ArmComponent->TargetArmLength = 100.0f;
			ArmComponent->SocketOffset = FVector(0.0f, 60.0f, 10.0f);
		}

		else
		{
			ArmComponent->TargetArmLength = 200.0f;
			ArmComponent->SocketOffset = FVector(10.0f, 90.0f, 20.0f);
		}

		// NormalAimWidget off
		PlayerNormalAimWidget->SetVisibility(ESlateVisibility::Visible);

		// Set MoveSpeed while aiming
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->GetMoveSpeed() * 0.7f;
		break;
	}

	case EPlayer_ActionState::Aiming:
	case EPlayer_ActionState::QAiming:
	case EPlayer_ActionState::EAiming:
	default:
		break;
	}
}

void AMGPlayerController::RightMouseButtonRelease()
{
	bRightMouseButtonPress = !bRightMouseButtonPress;

	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	switch (ActionState)
	{
	case EPlayer_ActionState::Aiming:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();
		UCameraComponent* CamComponent = PlayerCharacter->GetCameraComponent();

		if (!ArmComponent || !CamComponent)
			return;

		// StateMachine내 ActionState 설정 
		PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetActionState(EPlayer_ActionState::Normal);

		// CameraArm Length 및 SocketOffset 조정
		ArmComponent->TargetArmLength = 250.0f;
		ArmComponent->SocketOffset = FVector(0.0f, 0.0f, 10.0f);

		// NormalAimWidget off
		PlayerNormalAimWidget->SetVisibility(ESlateVisibility::Hidden);
		PlayerNormalAimWidget->SetBossWeakpointWidget(false);

		break;
	}

	case EPlayer_ActionState::Normal:
	case EPlayer_ActionState::QAiming:
	case EPlayer_ActionState::EAiming:
	default:
		break;
	}

	// Set MoveSpeed while aiming
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->GetMoveSpeed();
}

void AMGPlayerController::QButtonPress()
{
	bool bCheck = (bool)(PlayerCharacter->GetStatus());

	if (bCheck)
	{
		return;
	}

	bQButtonPress = !bQButtonPress;

	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	switch (ActionState)
	{
	case EPlayer_ActionState::Normal:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;

		// StateMachine내 ActionState 설정 
		PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetActionState(EPlayer_ActionState::QAiming);

		// CameraArm Length 및 SocketOffset 조정
		ArmComponent->TargetArmLength = 100.0f;
		ArmComponent->SocketOffset = FVector(0.0f, -60.0f, 30.0f);

		PlayerQAimWidget->SetVisibility(ESlateVisibility::Visible);

		break;
	}

	case EPlayer_ActionState::Aiming:
	case EPlayer_ActionState::QAiming:
	case EPlayer_ActionState::EAiming:
	default:
		break;
	}
}

void AMGPlayerController::QButtonRelease()
{
	bQButtonPress = !bQButtonPress;

	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	switch (ActionState)
	{
	case EPlayer_ActionState::QAiming:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;

		int MissileCount = PlayerCharacter->GetMissileCount();
		
		// 발사하는 동안 QAiming 상태를 유지.
		if (!PlayerCharacter->IsTargetEmpty() && MissileCount > 0)
		{
			PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetBodyActionState(EPlayer_BodyAction::QFire);

			PlayerQAimWidget->SetVisibility(ESlateVisibility::Hidden);
			PlayerQAimWidget->SetScopeActivate(false);
			PlayerCharacter->SetQSkillCollision(false);

		}

		// 그대로 Normal 상태로 돌아오기.
		else
		{
			// StateMachine내 ActionState 설정 
			PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetActionState(EPlayer_ActionState::Normal);

			// CameraArm Length 및 SocketOffset 조정
			ArmComponent->TargetArmLength = 250.0f;
			ArmComponent->SocketOffset = FVector(0.0f, 0.0f, 0.0f);


			PlayerQAimWidget->SetVisibility(ESlateVisibility::Hidden);
			PlayerQAimWidget->SetScopeActivate(false);
			PlayerCharacter->SetQSkillCollision(false);
		}

		break;
	}

	default:
		break;
	}
}

void AMGPlayerController::EButtonPress()
{
	bool bCheck = (bool)(PlayerCharacter->GetStatus());

	if (bCheck)
	{
		return;
	}

	bEButtonPress = !bEButtonPress;

	if (PlayerCharacter->IsDroneReady())
	{
		EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

		switch (ActionState)
		{
		case EPlayer_ActionState::Normal:
		{
			USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

			if (!ArmComponent)
				return;

			// StateMachine내 ActionState 설정 
			PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetActionState(EPlayer_ActionState::EAiming);

			// CameraArm Length 및 SocketOffset 조정
			ArmComponent->TargetArmLength = 100.0f;
			ArmComponent->SocketOffset = FVector(0.0f, -60.0f, 30.0f);

			// ParticleSystem On
			PlayerCharacter->GetDroneParticleSystem()->SetVisibility(true);
			PlayerCharacter->GetDroneParticleSystem()->ActivateSystem();

			break;
		}
		default:
			break;
		}
	}
}

void AMGPlayerController::EButtonRelease()
{
	bEButtonPress = !bEButtonPress;

	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	switch (ActionState)
	{
	case EPlayer_ActionState::EAiming:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;

		PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetBodyActionState(EPlayer_BodyAction::EThrowing);

		// StateMachine내 ActionState 설정 
		PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetActionState(EPlayer_ActionState::Normal);

		// CameraArm Length 및 SocketOffset 조정
		ArmComponent->TargetArmLength = 250.0f;
		ArmComponent->SocketOffset = FVector(0.0f, 0.0f, 0.0f);

		// ParticleSystem off
		PlayerCharacter->GetDroneParticleSystem()->SetVisibility(false);
		PlayerCharacter->GetDroneParticleSystem()->DeactivateSystem();

		// UseDrone check
		PlayerCharacter->UseDroneReady();
		break;
	}
	default:
		break;
	}
}

void AMGPlayerController::FButtonPress()
{
	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	bool bCheck = (bool)(PlayerCharacter->GetStatus());

	if (bCheck)
	{
		return;
	}

	TArray<TObjectPtr<AActor>> ActorsArray;

	UCapsuleComponent* Component = PlayerCharacter->FindComponentByClass<UCapsuleComponent>();
	Component->GetOverlappingActors(ActorsArray, AMGInteraction_Input::StaticClass());

	if (ActorsArray.IsEmpty())
		return;

	AMGInteraction_Input* InteractionInput = Cast<AMGInteraction_Input>(ActorsArray[0]);

	if (InteractionInput)
	{
		PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetActionState(EPlayer_ActionState::Interaction);
		InteractionInput->SetProgressing(true);
	}
}

void AMGPlayerController::FButtonRelease()
{
	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	bool bCheck = (bool)(PlayerCharacter->GetStatus());

	if (bCheck)
	{
		return;
	}

	TArray<TObjectPtr<AActor>> ActorsArray;

	UCapsuleComponent* Component = PlayerCharacter->FindComponentByClass<UCapsuleComponent>();
	Component->GetOverlappingActors(ActorsArray, AMGInteraction_Input::StaticClass());

	if (ActorsArray.IsEmpty())
		return;

	AMGInteraction_Input* InteractionInput = Cast<AMGInteraction_Input>(ActorsArray[0]);

	if (!InteractionInput)
		return;

	PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetActionState(EPlayer_ActionState::Normal);
	InteractionInput->SetProgressing(false);
}

void AMGPlayerController::RButtonPress()
{
	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	bool bCheck = (bool)(PlayerCharacter->GetStatus());

	if (bCheck)
	{
		return;
	}
		
	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	if (ActionState == EPlayer_ActionState::Aiming)
	{
		bool CurrentFireMode = PlayerCharacter->IsChargeFireMode();

		PlayerCharacter->SetChargeFireMode(!CurrentFireMode);

		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (CurrentFireMode)
		{
			PlayerNormalAimWidget->SwtichAimWidget(false);
			ArmComponent->TargetArmLength = 200.0f;
			ArmComponent->SocketOffset = FVector(10.0f, 90.0f, 20.0f);
		}

		else
		{
			PlayerNormalAimWidget->SwtichAimWidget(true);
			ArmComponent->TargetArmLength = 100.0f;
			ArmComponent->SocketOffset = FVector(0.0f, 60.0f, 10.0f);
		}

		PlayerNormalAimWidget->SetBossWeakpointWidget(!CurrentFireMode);
		PlayerStatusWidget->PlayChangeWeaponMode();
	}
}

void AMGPlayerController::ShiftButtonPress()
{
	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	bool bCheck = (bool)(PlayerCharacter->GetStatus()) || !PlayerCharacter->IsDashCharged();

	if (bCheck)
	{
		return;
	}

	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	if (ActionState == EPlayer_ActionState::Normal)
	{
		// 전후좌우 판단.
		UCharacterMovementComponent* MovementComponent = PlayerCharacter->GetCharacterMovement();

		if (!MovementComponent || !MovementComponent->IsValidLowLevel())
			return;

		FVector MoveDir = PlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration().GetSafeNormal();
		MoveDir.Z += 0.4f;
		
		float YawValue = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetMovementYawValue();

		bool bKeyPushedW = IsInputKeyDown("W");
		bool bKeyPushedS = IsInputKeyDown("S");
		
		if (!(bKeyPushedW || bKeyPushedS))
		{
			FRotator MeshRot = PlayerCharacter->GetMesh()->GetRelativeRotation();
			MeshRot.Yaw = YawValue - 90.0f;

			PlayerCharacter->GetMesh()->SetRelativeRotation(MeshRot);
		}

		PlayerCharacter->GetCapsuleComponent()->SetSimulatePhysics(true);
		PlayerCharacter->GetCapsuleComponent()->AddImpulse(MoveDir * 1000.f, NAME_None, true);
		PlayerCharacter->GetAnimInst()->SetFalling(true);

		// 대시 키로 State 변환
		PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetActionState(EPlayer_ActionState::Dash);
		PlayerCharacter->GetAnimInst()->SetStatus(ECharacter_Status::Dodge);

		// UseDash check
		PlayerCharacter->UseDash();
	}
}

void AMGPlayerController::CheatKeyPress()
{
	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	PlayerCharacter->SetMaxHP(99999999.0);
	PlayerCharacter->SetCurrentHP(99999999.0);
	PlayerCharacter->SetMinAttack(9999.0);
	PlayerCharacter->SetMaxAttack(9999.0);
	PlayerCharacter->SetMoveSpeed(9999.0);
}
