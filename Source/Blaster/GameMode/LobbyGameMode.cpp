// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"

void ALobbyGameMode::PostLogin(APlayerController *NewPlayer){
    Super::PostLogin(NewPlayer);

    int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
    if (NumberOfPlayers == 2) {   //hardcoded
        UWorld* World = GetWorld();
        if (World) {
            bUseSeamlessTravel = true; // also check it in derived BP; transition map should exist and specified in project settings
            World->ServerTravel(FString("/Game/Maps/BlasterMap?listen"));   // the map should be included into the lost of maps to package 
        }
    }
}
