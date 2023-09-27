// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Interactable/LAInteractableVisualizer.h"
#include "LAPlayerInteractComponent.generated.h"

class ALAInteractableVisualizer;
UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LA_PROTOTYPE_API ULAPlayerInteractComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	ULAPlayerInteractComponent();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	void InteractWithActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ALAInteractableVisualizer> InteractableVisualizerClass;

private:
	UFUNCTION()
	void GetClosestOverlappingActor(TMap<AActor*, ALAInteractableVisualizer*> ActorsMap);

	UFUNCTION(Blueprintable)
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, 
		bool bFromSweep,
		const FHitResult& SweepResult
		);

	UFUNCTION(Blueprintable)
	void OnEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
		);

	UPROPERTY()
	TMap<AActor*, ALAInteractableVisualizer*> OverlappingActorsMap;

	UPROPERTY()
	AActor* ClosestOverlappingActor;
};
