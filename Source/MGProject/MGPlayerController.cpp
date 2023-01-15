

#include "MGPlayerController.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "MGFlag.h"
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
	
	PlayerQAimWidget = CreateWidget<UMGAimWidget>(this, PlayerWidget, TEXT("Player AimWidget"));
	PlayerQAimWidget->AddToViewport(9);
	PlayerQAimWidget->SetVisibility(ESlateVisibility::Hidden);

	PlayerNormalAimWidget = CreateWidget<UMGNormalAimWidget>(this, PlayerNormalAimWBP, TEXT("PlayerNormalAimWidget"));
	PlayerNormalAimWidget->AddToViewport(9);
	PlayerNormalAimWidget->SetVisibility(ESlateVisibility::Hidden);

	PlayerStatusWidget = CreateWidget<UMGPlayerWidget>(this, PlayerStatusWBP, TEXT("PlayerStatusWidget"));
	PlayerStatusWidget->AddToViewport(8);
	PlayerStatusWidget->SetVisibility(ESlateVisibility::Visible);
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
	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	switch (ActionState)
	{
	case EPlayer_ActionState::Normal:
	case EPlayer_ActionState::Aiming:
	{
		PlayerCharacter->GetAnimInst()->SetBodyActionState(EPlayer_BodyAction::NormalFire);

		PlayerCharacter->GetTrace();
		break;
	}

	case EPlayer_ActionState::QAiming:
	case EPlayer_ActionState::EAiming:
	default:
		break;
	}
}

void AMGPlayerController::RightMouseButtonClick()
{
	bRightMouseButtonPress = !bRightMouseButtonPress;

	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	UE_LOG(LogTemp, Log, TEXT("Pressed!!!"));
	switch (ActionState)
	{
	case EPlayer_ActionState::Normal:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();
		
		if (!ArmComponent)
			return;

		// StateMachine내 ActionState 설정 
		PlayerCharacter->GetAnimInst()->SetActionState(EPlayer_ActionState::Aiming);

		// CameraArm Length 및 SocketOffset 조정
		ArmComponent->TargetArmLength = 100.0f;
		ArmComponent->SocketOffset = FVector(0.0f, -60.0f, 30.0f);
		
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

	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	switch (ActionState)
	{
	case EPlayer_ActionState::Aiming:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;

		// StateMachine내 ActionState 설정 
		PlayerCharacter->GetAnimInst()->SetActionState(EPlayer_ActionState::Normal);

		// CameraArm Length 및 SocketOffset 조정
		ArmComponent->TargetArmLength = 250.0f;
		ArmComponent->SocketOffset = FVector(0.0f, 0.0f, 0.0f);

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
	bQButtonPress = !bQButtonPress;

	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	switch (ActionState)
	{
	case EPlayer_ActionState::Normal:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;

		// StateMachine내 ActionState 설정 
		PlayerCharacter->GetAnimInst()->SetActionState(EPlayer_ActionState::QAiming);

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
	bRightMouseButtonPress = !bRightMouseButtonPress;

	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	switch (ActionState)
	{
	case EPlayer_ActionState::QAiming:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;

		// 발사여부에 따라서 Aiming 상태를 유지할 것인지 설정해야함.
		
		
		// 발사함 : 로켓발사하는 동안 QAiming 상태를 유지.
		if (!PlayerCharacter->IsTargetEmpty())
		{
			PlayerCharacter->GetAnimInst()->SetBodyActionState(EPlayer_BodyAction::QFire);

			// CameraArm Length 및 SocketOffset 조정
			ArmComponent->TargetArmLength = 250.0f;
			ArmComponent->SocketOffset = FVector(0.0f, 0.0f, 0.0f);


			PlayerQAimWidget->SetVisibility(ESlateVisibility::Hidden);
			PlayerQAimWidget->SetScopeActivate(false);
			PlayerCharacter->SetQSkillCollision(false);

		}

		// 발사안함 : 그대로 Normal 상태로 돌아오기.
		else
		{
			// StateMachine내 ActionState 설정 
			PlayerCharacter->GetAnimInst()->SetActionState(EPlayer_ActionState::Normal);

			// CameraArm Length 및 SocketOffset 조정
			ArmComponent->TargetArmLength = 250.0f;
			ArmComponent->SocketOffset = FVector(0.0f, 0.0f, 0.0f);


			PlayerQAimWidget->SetVisibility(ESlateVisibility::Hidden);
			PlayerQAimWidget->SetScopeActivate(false);
			PlayerCharacter->SetQSkillCollision(false);
		}

		break;
	}

	case EPlayer_ActionState::Normal:
	case EPlayer_ActionState::Aiming:
	case EPlayer_ActionState::EAiming:
	default:
		break;
	}
}

void AMGPlayerController::EButtonPress()
{
	bEButtonPress = !bEButtonPress;

	if (PlayerCharacter->IsDroneReady())
	{
		EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

		switch (ActionState)
		{
		case EPlayer_ActionState::Normal:
		{
			USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

			if (!ArmComponent)
				return;

			// StateMachine내 ActionState 설정 
			PlayerCharacter->GetAnimInst()->SetActionState(EPlayer_ActionState::EAiming);

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

	EPlayer_ActionState ActionState = PlayerCharacter->GetAnimInst()->GetActionState();

	switch (ActionState)
	{
	case EPlayer_ActionState::EAiming:
	{
		USpringArmComponent* ArmComponent = PlayerCharacter->FindComponentByClass<USpringArmComponent>();

		if (!ArmComponent)
			return;

		PlayerCharacter->GetAnimInst()->SetBodyActionState(EPlayer_BodyAction::EThrowing);

		// StateMachine내 ActionState 설정 
		PlayerCharacter->GetAnimInst()->SetActionState(EPlayer_ActionState::Normal);

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
