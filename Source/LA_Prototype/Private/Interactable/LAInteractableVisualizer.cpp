// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/LAInteractableVisualizer.h"

// Sets default values
ALAInteractableVisualizer::ALAInteractableVisualizer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALAInteractableVisualizer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALAInteractableVisualizer::OnHighlighted_Implementation(AActor* Interactor)
{
	bHighlighted = true;
}

void ALAInteractableVisualizer::OnUnHighlighted_Implementation(AActor* Interactor)
{
	bHighlighted = false;
}



