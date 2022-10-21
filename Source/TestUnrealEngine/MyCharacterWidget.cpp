// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterWidget.h"
#include "MyStatComponent.h"
#include "Components/ProgressBar.h"

void UMyCharacterWidget::BindHP(class UMyStatComponent* StatComp)
{
	UE_LOG(LogTemp, Error, TEXT("BindHP"));
	CurrentStatComp = StatComp;
	StatComp->OnHpChanged.AddUObject(this,&UMyCharacterWidget::UpdateHp);
}

void UMyCharacterWidget::UpdateHp()
{
	UE_LOG(LogTemp, Error , TEXT("UpdateHP"));
	if (CurrentStatComp.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("IsValidUpdateHP"));
		PB_HpBar->SetPercent(CurrentStatComp->GetHpRatio());
	}
}

