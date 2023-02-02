// Fill out your copyright notice in the Description page of Project Settings.


#include "MGTaskNode_TurnToTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Animation/MGEnemyAnimInstance.h"

UMGTaskNode_TurnToTarget::UMGTaskNode_TurnToTarget()
{
	bNotifyTick = true;
	TurnAnimTimeAcc = 0.0f;
}

EBTNodeResult::Type UMGTaskNode_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMGEnemyController* EnemyController = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* EnemyCharacter = EnemyController->GetPawn<AMGEnemyCharacter>();
	UMGEnemyAnimInstance* AnimInst = EnemyCharacter->GetAnimInst<UMGEnemyAnimInstance>();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetObject"));

	AActor* ActorTarget = Cast<AActor>(Target);

	if (!ActorTarget)
	{
		TurnAnimTimeAcc = 0.0f;
		return EBTNodeResult::Succeeded;
	}

	int32 RotateStateIndex = AnimInst->GetInstanceAssetPlayerIndex(TEXT("Locomotion"), TEXT("Rotate"));
	float RotateLength = AnimInst->GetInstanceAssetPlayerLength(RotateStateIndex);


	if (RotateLength >= TurnAnimTimeAcc)
	{
		// keep progress turning.
		AnimInst->SetAIAnimState(EAIAnimState::Rotate);
		EnemyCharacter->SetLookAt(ActorTarget);

		return EBTNodeResult::InProgress;
	}

	else
	{
		// turning ended.
		TurnAnimTimeAcc -= TurnAnimTimeAcc;

		AnimInst->SetAIAnimState(EAIAnimState::Attack);

		return EBTNodeResult::Succeeded;
	}
}

void UMGTaskNode_TurnToTarget::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	FinishLatentTask(_OwnerComp, ExecuteTask(_OwnerComp, _pNodeMemory));

	AMGEnemyController* EnemyController = Cast<AMGEnemyController>(_OwnerComp.GetAIOwner());
	AMGEnemyCharacter* EnemyCharacter = EnemyController->GetPawn<AMGEnemyCharacter>();
	UMGEnemyAnimInstance* AnimInst = EnemyCharacter->GetAnimInst<UMGEnemyAnimInstance>();

	if (AnimInst->GetAIAnimState() == EAIAnimState::Rotate)
	{
		TurnAnimTimeAcc += _DeltaSeconds;
	}
}

/*
* 지금...
* TaskNode를 보스도 잡몹도 공유하면서 쓰려고하는데 
* Idle만 같이 쓰려고하니까 개지랄남 
* 사실 이거는 그냥 잡몹 BT에다가도 Alive Sequence 추가해서
* Idle을 Succeed하면 될거같거든
* 근데 이거 말고도 존나 많은 에러사항이 나올거같아
* 보스 ABP를 TaskNode하고 Decorator가 잘 조종하고 있는지 테스트중이야
* ABP가 잘 동작되도록 보스 BT에 있는 TaskNode하고 Decorator를 잘 추가할수 있도록 해봐.
*/