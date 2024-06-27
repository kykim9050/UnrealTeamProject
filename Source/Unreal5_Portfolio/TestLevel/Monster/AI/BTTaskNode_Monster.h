// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/MonsterDataRow.h"
#include "Global/ContentsEnum.h"
#include "BTTaskNode_Monster.generated.h"


// 몬스터 BT 부모 Task 노드
UCLASS()
class UNREAL5_PORTFOLIO_API UBTTaskNode_Monster : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_Monster();

	template<typename OwnerType>
	OwnerType* GetActor(UBehaviorTreeComponent& _OwnerComp)
	{
		return Cast<OwnerType>(GetActor(_OwnerComp));
	}

	AActor* GetActor(UBehaviorTreeComponent& _OwnerComp);
	
	template<typename EnumType>
	EnumType GetCurState(UBehaviorTreeComponent& _OwnerComp)
	{
		return static_cast<EnumType>(GetCurState(_OwnerComp));
	}

	uint8 GetCurState(UBehaviorTreeComponent& _OwnerComp);

	template<typename EnumType>
	void StateChange(UBehaviorTreeComponent& _OwnerComp, EnumType _StateChange)
	{
		StateChange(_OwnerComp, static_cast<uint8>(_StateChange));
	}

	void StateChange(UBehaviorTreeComponent& _OwnerComp, uint8 _StateChange);

	template<typename ObjectType>
	ObjectType* GetValueAsObject(UBehaviorTreeComponent& _OwnerComp, FName _Name)
	{
		return Cast<ObjectType>(GetValueAsObject(_OwnerComp, _Name));
	}

	FORCEINLINE UObject* GetValueAsObject(UBehaviorTreeComponent& _OwnerComp, FName _Name)
	{
		return _OwnerComp.GetBlackboardComponent()->GetValueAsObject(_Name);
	}

	FORCEINLINE void SetValueAsObject(UBehaviorTreeComponent& _OwnerComp, FName _Name, UObject* _Value)
	{
		_OwnerComp.GetBlackboardComponent()->SetValueAsObject(_Name, _Value);
	}

};
