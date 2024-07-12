// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Global/MainGameBlueprintFunctionLibrary.h"
#include "Global/DataTable/BossDataRow.h"
#include "Global/ContentsEnum.h"

#include "BTTaskNode_BossMonster.generated.h"

/**
 * BossMonster TaskNode 부모 클래스
 */
UCLASS()
class UNREAL5_PORTFOLIO_API UBTTaskNode_BossMonster : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_BossMonster();

	template<typename OwnerType>
	OwnerType* GetActor(UBehaviorTreeComponent& _OwnerComponent)
	{
		return Cast<OwnerType>(GetActor(_OwnerComponent));
	}

	AActor* GetActor(UBehaviorTreeComponent& _OwnerComponent);
	
	template<typename EnumType>
	EnumType GetCurState(UBehaviorTreeComponent& _OwnerComponent)
	{
		return static_cast<EnumType>(GetCurState(_OwnerComponent));
	}

	uint8 GetCurState(UBehaviorTreeComponent& _OwnerComponent);

	template<typename EnumType>
	void StateChange(UBehaviorTreeComponent& _OwnerComponent, EnumType _StateChange)
	{
		StateChange(_OwnerComponent, static_cast<uint8>(_StateChange));
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

	FORCEINLINE FVector GetValueAsVector(UBehaviorTreeComponent& _OwnerComp, FName _Name)
	{
		return _OwnerComp.GetBlackboardComponent()->GetValueAsVector(_Name);
	}

	FORCEINLINE void SetValueAsVector(UBehaviorTreeComponent& _OwnerComp, FName _Name, const FVector& _Value)
	{
		_OwnerComp.GetBlackboardComponent()->SetValueAsVector(_Name, _Value);
	}
	
};
