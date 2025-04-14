#pragma once

#include "CoreMinimal.h"  // Contient les inclusions de base d'Unreal Engine
#include "GameFramework/Actor.h"  // Classe parente dont hérite ANoteJeu
#include "Components/SplineComponent.h"  // Pour utiliser USplineComponent
#include "Kismet/GameplayStatics.h"  // Utilitaires de gameplay
#include "Components/TimelineComponent.h"
#include "Piste.h"  // Classe APiste utilisée comme référence
#include "NoteJeu.generated.h"  // Généré automatiquement par Unreal

/*
 * Classe gérant le comportement d'une note musicale dans un jeu de rythme
 * La note glisse le long d'une spline suivant une timeline
 */

UCLASS(Blueprintable, BlueprintType)
class ANoteJeu : public AActor
{
	GENERATED_BODY()

public:
	ANoteJeu();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	/*
	* Initialise la note avec une piste spécifique
	* @param PisteSelectionnee La piste à laquelle cette note appartient
	*/
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void InitialiserNote(APiste* PisteSelectionnee);

	/** Démarre l'animation de déplacement de la note le long de la spline */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void CreerNote();

	// Composant spline qui définit le trajet de la note
	UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
	USplineComponent* RhythmeSpline;
	
	// Référence à la piste associée à cette note
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	APiste* PisteSelectionnee;

	// Temps nécessaire pour atteindre la fin de la spline 
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Par d�faut")
	double TempsCompletion = 5.0;

	UPROPERTY(BlueprintReadWrite, Category = "Timeline")
	UTimelineComponent* TimelineComponent;

	// Timestamp de création de la note
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Par d�faut")
	double TempsCreation;

	UFUNCTION(BlueprintNativeEvent, Category = "Gameplay")
	void OnNoteCreee();
};
