#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Piste.generated.h"

class ANoteJeu;

UENUM(BlueprintType)
enum class EScoreResult : uint8
{
    Super = 0,
    Bien = 1,
    Bof = 2
};



UCLASS(Blueprintable, BlueprintType)
class MYMELOKEY_API APiste : public AActor
{
    GENERATED_BODY()

public:
    APiste();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

public:
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    EScoreResult ResultatTouche(ANoteJeu *Note);

    // Événement pour transmettre les résultats au Blueprint
    UFUNCTION(BlueprintNativeEvent, Category = "Gameplay")
    void OnScoreCalcule(EScoreResult Type, int32 ScoreToAdd, int32 ComboToAdd);

    // Variable pour stocker temporairement le temps de réaction
    UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
    float TempsReaction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    TSubclassOf<ANoteJeu> NoteClass;

    UPROPERTY()
    USplineComponent* RhythmeSpline;

private:
    // Variables internes

    UPROPERTY()
    bool bNoteCollision;

};