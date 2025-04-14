#include "Piste.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "NoteJeu.h"
#include "Kismet/GameplayStatics.h"

APiste::APiste()
{
    PrimaryActorTick.bCanEverTick = true;

    // Valeurs par d�faut
    bNoteCollision = false;
    TempsReaction = 0.5f;
}

void APiste::BeginPlay()
{
    Super::BeginPlay();
}

void APiste::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

EScoreResult APiste::ResultatTouche(ANoteJeu *Note)
{
    // Récupération du temps actuel
    float CurrentTime = GetWorld()->GetTimeSeconds();

    // Calcul du temps de réaction si Note est valide
    if (!Note)
    {
        UE_LOG(LogTemp, Warning, TEXT("ResultatTouche: Note invalide"));
        return EScoreResult::Bof;
    }

    TempsReaction = CurrentTime - Note->GetTempsCreation();

    // Variables pour stocker le score et le combo à ajouter
    int32 ScoreToAdd = 0;
    int32 ComboToAdd = 0;
    EScoreResult ResultType = EScoreResult::Bof;

    // Vérification des conditions pour déterminer le résultat
    if (TempsReaction >= 2.7f && TempsReaction <= 3.6f)
    {
        // Condition 1 vraie
        if (TempsReaction >= 3.2f && TempsReaction <= 3.6f)
        {
            // Condition 2 vraie - "SUPER"
            ScoreToAdd = 300;
            ComboToAdd = 2;
            ResultType = EScoreResult::Super;
        }
        else
        {
            // Condition 2 fausse - "BIEN"
            ScoreToAdd = 150;
            ComboToAdd = 1;
            ResultType = EScoreResult::Bien;
        }
    }
    else
    {
        // Condition 1 fausse - "BOF"
        ScoreToAdd = 50;
        ComboToAdd = 0;
        ResultType = EScoreResult::Bof;
    }

    // Envoyer les résultats au Blueprint via un événement
    OnScoreCalcule(ResultType, ScoreToAdd, ComboToAdd);

    return ResultType;
}

void APiste::OnScoreCalcule_Implementation(EScoreResult Type, int32 ScoreToAdd, int32 ComboToAdd)
{
    // Code d'implémentation par défaut
    // Par exemple, vous pourriez envoyer un événement global que le GameMode pourrait écouter
    if (UWorld *World = GetWorld())
    {
        // Utiliser le système d'événements d'Unreal pour communiquer avec le GameMode
        FString ResultName;
        switch (Type)
        {
        case EScoreResult::Super:
            ResultName = TEXT("SUPER");
            break;
        case EScoreResult::Bien:
            ResultName = TEXT("BIEN");
            break;
        case EScoreResult::Bof:
            ResultName = TEXT("BOF");
            break;
        }

        UE_LOG(LogTemp, Display, TEXT("Résultat: %s, Score+: %d, Combo+: %d"),
               *ResultName, ScoreToAdd, ComboToAdd);

        // Vous pourriez également utiliser le système d'événements Blueprint pour communiquer
        // avec votre GameMode Blueprint, mais cela nécessiterait du code Blueprint supplémentaire
    }
}

void APiste::MAJCollisionNotes()
{
}