// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
	// ...
	Level = 1;
}


// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(Level);
}

void UMyStatComponent::SetLevel(int32 Levels)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (MyGameInstance)
	{	
		auto StatData = MyGameInstance->GetStatData(Levels);
		{
			Level = StatData->Level;
			SetHp(StatData->MaxHP);
			MaxHp = StatData->MaxHP;
			Attack = StatData->Attack;
		}
	}
}

void UMyStatComponent::OnAttacked(float DamageAmount)
{
	int32 NewHp = Hp-DamageAmount;

	SetHp(NewHp);

	Hp -= DamageAmount;

}

void UMyStatComponent::SetHp(int32 NewHp)
{
	UE_LOG(LogTemp, Error, TEXT("SetHp"));
	Hp = NewHp;
	if (Hp < 0)
	{
		Hp = 0;
	}
	OnHpChanged.Broadcast();
}

