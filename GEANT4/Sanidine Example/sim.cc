#include <iostream>

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

#include "Geometry.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"

#include "G4ParticleHPManager.hh"



int main(int argc, char** argv)
{
    G4UIExecutive* ui = 0;
    
    //construct the default run manager
  #ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
  #else
    //my Verbose output class
    G4RunManager* runManager = new G4RunManager;
  #endif
    
    // User Initialization for Geometry
    Geometry* det = new Geometry;
    runManager->SetUserInitialization(det); 
    
    // Set up physics List
    PhysicsList* phys = new PhysicsList;
    runManager->SetUserInitialization(phys);
    
    // Ste up User Actions
    runManager->SetUserInitialization(new ActionInitialization(det));
    
    // Initialize G4 kernel
    runManager->Initialize();
    
    //
    // Visualisation
    //
    if (argc == 1)
    {
        ui = new G4UIExecutive(argc, argv);
    }
    
    G4VisManager *visManager = new G4VisExecutive();
    
    // Replaced HP environmental variables with C++ calls
    G4ParticleHPManager::GetInstance()->SetSkipMissingIsotopes( false );
    G4ParticleHPManager::GetInstance()->SetDoNotAdjustFinalState( false );
    G4ParticleHPManager::GetInstance()->SetUseOnlyPhotoEvaporation( false );
    G4ParticleHPManager::GetInstance()->SetNeglectDoppler( false );
    G4ParticleHPManager::GetInstance()->SetProduceFissionFragments( false );
    G4ParticleHPManager::GetInstance()->SetUseWendtFissionModel( false );
    G4ParticleHPManager::GetInstance()->SetUseNRESP71Model( false );
    
    
    visManager -> Initialize();
    
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    if(ui)
        {
            UImanager->ApplyCommand("/control/execute vis.mac");
            ui->SessionStart();
        }
        else
        {
            G4String command = "/control/execute ";
            G4String fileName = argv[1];
            UImanager->ApplyCommand(command+fileName);
        }
    
    
    return 0;
}
