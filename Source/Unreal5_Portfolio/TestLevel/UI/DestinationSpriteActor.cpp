// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevel/UI/DestinationSpriteActor.h"
#include "PaperSpriteComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperSprite.h"
#include "Global/ContentsLog.h"

// Sets default values
ADestinationSpriteActor::ADestinationSpriteActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DeatinationSprite"));
	sprite->SetupAttachment(RootComponent);

	if (true == ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("/Game/Resources/TestLevel/UI/Sprite/DestIconSprite.DestIconSprite")).Succeeded())
	{
		sprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("/Game/Resources/TestLevel/UI/Sprite/DestIconSprite.DestIconSprite")).Object);
	}
	else
	{
		LOG(UILog, Fatal, TEXT("ADestinationSpriteActor::BeginPlay() > ConstructorHelpers::FObjectFinder<UPaperSprite> Error"));
	}

	sprite->bVisibleInSceneCaptureOnly = true;
	SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void ADestinationSpriteActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(-1530.f, 60836.f, 0.f));
	SetActorScale3D(FVector(4.f, 1.f, 4.f));

	FQuat Q;
	UKismetMathLibrary::Quat_SetFromEuler(Q, FVector(90.f, 0.f, -90.f));
	SetActorRotation(Q);
}

// Called every frame
void ADestinationSpriteActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
