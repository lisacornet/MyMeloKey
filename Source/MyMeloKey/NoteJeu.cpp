#include "NoteJeu.h"
#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Piste.h" 
#include "Curves/CurveFloat.h"

ANoteJeu::ANoteJeu()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ANoteJeu::BeginPlay()
{
	Super::BeginPlay();

	InitialiserNote(PisteSelectionnee);
}

void ANoteJeu::InitialiserNote(APiste* NouvellePiste)
{
    if (NouvellePiste && NouvellePiste->RhythmeSpline)
    {
        this->PisteSelectionnee = NouvellePiste;
        RhythmeSpline = NouvellePiste->RhythmeSpline;
    } 
    
    // Recupere temps de creation en fonction du temps de jeu
    TempsCreation = UGameplayStatics::GetTimeSeconds(GetWorld());
}

void ANoteJeu::CreerNote()
{
  
    //Obtenir la longueur de la spline, la piste

    float SplineLength = RhythmeSpline->GetSplineLength();

    // Obtenir la position au point de départ
    const float DistanceInitiale = 0.0f; // Début de la spline
    FVector Location = RhythmeSpline->GetLocationAtDistanceAlongSpline(DistanceInitiale, ESplineCoordinateSpace::World);

    //  Obtenir la rotation au point de départ
    FRotator Rotation = RhythmeSpline->GetRotationAtDistanceAlongSpline(DistanceInitiale, ESplineCoordinateSpace::World);

    // Définir la transformation de l'acteur
    FTransform NewTransform;
    NewTransform.SetLocation(Location);
    NewTransform.SetRotation(Rotation.Quaternion());
    NewTransform.SetScale3D(FVector(0.8f, 0.8f, 0.8f)); // taille de la flèche

    SetActorTransform(NewTransform, false);

    // Signaler au Blueprint que la note a été créée pour qu'il puisse lancer la Timeline
    OnNoteCreee();
}

void ANoteJeu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ANoteJeu::OnNoteCreee()
{
    //Détermine la vitesse de déplacement
    if (TimelineComponent)
    {
        TimelineComponent->SetPlayRate(1.0f / TempsCompletion);
        TimelineComponent->PlayFromStart();
    }
}