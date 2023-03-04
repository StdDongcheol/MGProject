

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
	
	//InputComponent->BindAction(FName("LeftMouseButton"), EInputEvent::IE_Pressed, this, &AMGPlayerController::LeftMouseButtonClick);
	InputComponent->BindAction(FName("RightMouseButton"), EInputEvent::IE_Pressed, this, &AMGPlayerController::RightMouseButtonClick);
	InputComponent->BindAction(FName("RightMouseButton"), EInputEvent::IE_Released, this, &AMGPlayerController::RightMouseButtonRelease);
	InputComponent->BindAction(FName("SkillQ"), EInputEvent::IE_Pressed, this, &AMGPlayerController::QButtonPress);
	InputComponent->BindAction(FName("SkillQ"), EInputEvent::IE_Released, this, &AMGPlayerController::QButtonRelease);
	InputComponent->BindAction(FName("SkillE"), EInputEvent::IE_Pressed, this, &AMGPlayerController::EButtonPress);
	InputComponent->BindAction(FName("SkillE"), EInputEvent::IE_Released, this, &AMGPlayerController::EButtonRelease);
	InputComponent->BindAction(FName("Interaction"), EInputEvent::IE_Pressed, this, &AMGPlayerController::FButtonPress);
	InputComponent->BindAction(FName("Interaction"), EInputEvent::IE_Released, this, &AMGPlayerController::FButtonRelease);
	InputComponent->BindAction(FName("SetFireMode"), EInputEvent::IE_Pressed, this, &AMGPlayerController::RButtonPress);
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

void AMGPlayerController::MoveFront(float Value)
{	
	if (Value == 0.0f)
		return;

	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	bool bCheck = (bool)(PlayerCharacter->GetStatus());

	EPlayer_BodyAction PlayerAction = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetBodyActionState();

	if (bCheck || PlayerAction == EPlayer_BodyAction::NormalFire)
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

	if (bCheck || PlayerAction == EPlayer_BodyAction::NormalFire)
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

	if (bCheck || PlayerAction == EPlayer_BodyAction::NormalFire)
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
	
	if (bCheck || PlayerAction == EPlayer_BodyAction::NormalFire)
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
		if (PlayerCharacter->IsChargeFireMode())
			PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetBodyActionState(EPlayer_BodyAction::NormalFire);
		else
			PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->SetBodyActionState(EPlayer_BodyAction::RapidFire);

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

	UE_LOG(LogTemp, Log, TEXT("Pressed!!!"));
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
		ArmComponent->TargetArmLength = 200.0f;
		ArmComponent->SocketOffset = FVector(10.0f, 150.0f, 20.0f);

		// NormalAimWidget off
		PlayerNormalAimWidget->SetVisibility(ESlateVisibility::Visible);

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

		break;
	}

	case EPlayer_ActionState::Normal:
	case EPlayer_ActionState::QAiming:
	case EPlayer_ActionState::EAiming:
	default:
		break;
	}
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

		// 발사여부에 따라서 Aiming 상태를 유지할 것인지 설정해야함.
		
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
			ArmComponent->TargetArmLength = 200.0f;
			ArmComponent->SocketOffset = FVector(10.0f, 90.0f, 20.0f);
		}

		else
		{
			ArmComponent->TargetArmLength = 100.0f;
			ArmComponent->SocketOffset = FVector(0.0f, 60.0f, 10.0f);
		}
	}
}
