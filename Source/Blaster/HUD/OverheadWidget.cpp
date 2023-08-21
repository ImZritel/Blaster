// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "../Character/BlasterCharacter.h"


void UOverheadWidget::SetDisplayText(FString TextToDisplay){
    if(DisplayText) {
        DisplayText->SetText(FText::FromString(TextToDisplay));
    }
}

void UOverheadWidget::ShowPlayerNetRole(APawn *InPawn){
    ENetRole LocalRole = InPawn->GetLocalRole();  // or use GetRemoteRole for remote role
    FString Role;
    switch (LocalRole) {
        case ENetRole::ROLE_Authority:
            Role = FString("Authority");
            break;
        case ENetRole::ROLE_AutonomousProxy:
            Role = FString("AutonomousProxy");
            break;
        case ENetRole::ROLE_SimulatedProxy:
            Role = FString("SimulatedProxy");
            break;
        case ENetRole::ROLE_None:
            Role = FString("None");
            break;
    }
    FString LocalRoleString;
    GetPlayerNameFromPawn(InPawn);
    LocalRoleString = FString::Printf(TEXT("%s \n Local role: %s"), *PlayerName_, *Role);

    SetDisplayText(LocalRoleString);
}

void UOverheadWidget::GetPlayerNameFromPawn(APawn* GivenPawnPointer) {
    if (GivenPawnPointer) {
        ABlasterCharacter* Char = Cast<ABlasterCharacter>(GivenPawnPointer);
        if (Char) {
            APlayerState* PlayerState = Char->GetPlayerState();
            if (PlayerState) {
                PlayerName_ = PlayerState->GetPlayerName();
                return;
            } else {
                PlayerName_ = FString("APlayerState = nullptr");
                return;
            }
        } else {
            PlayerName_ = FString("ABlasterCharacter = nullptr");
            return;
        }
    }
    PlayerName_ = FString("GivenPawnPointer = nullptr");
    return;
}

void UOverheadWidget::NativeDestruct(){
    RemoveFromParent(); // remove widget from the viewport
    Super::NativeDestruct();
}
