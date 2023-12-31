// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LAInteractableVisualizer.generated.h"

UCLASS(Blueprintable, BlueprintType)
class LA_PROTOTYPE_API ALAInteractableVisualizer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALAInteractableVisualizer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	bool bHighlighted = false;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnHighlighted(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent)
	void OnUnHighlighted(AActor* Interactor);

};
