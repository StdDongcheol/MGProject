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
* ����...
* TaskNode�� ������ ����� �����ϸ鼭 �������ϴµ� 
* Idle�� ���� �������ϴϱ� �������� 
* ��� �̰Ŵ� �׳� ��� BT���ٰ��� Alive Sequence �߰��ؼ�
* Idle�� Succeed�ϸ� �ɰŰ��ŵ�
* �ٵ� �̰� ���� ���� ���� ���������� ���ðŰ���
* ���� ABP�� TaskNode�ϰ� Decorator�� �� �����ϰ� �ִ��� �׽�Ʈ���̾�
* ABP�� �� ���۵ǵ��� ���� BT�� �ִ� TaskNode�ϰ� Decorator�� �� �߰��Ҽ� �ֵ��� �غ�.
*/