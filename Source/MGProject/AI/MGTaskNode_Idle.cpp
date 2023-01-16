// Fill out your copyright notice in the Description page of Project Settings.


#include "MGTaskNode_Idle.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Character/MGEnemyCharacter.h"

UMGTaskNode_Idle::UMGTaskNode_Idle()
{
    bNotifyTick = true;
}

EBTNodeResult::Type UMGTaskNode_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    
    AMGEnemyCharacter* Enemy = Cast<AMGEnemyCharacter>(OwnerComp.GetOwner());
    
    UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetObject"));

    if (Target)
    {
        return EBTNodeResult::Failed;
    }

    return EBTNodeResult::InProgress;
}

void UMGTaskNode_Idle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
    FinishLatentTask(_OwnerComp, ExecuteTask(_OwnerComp, _pNodeMemory));
}
