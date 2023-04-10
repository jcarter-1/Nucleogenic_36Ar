//
// Run Aciton
//

#include "RunAction.hh"
#include "Run.hh"
#include "RunMessenger.hh"
#include "Geometry.hh"
#include "generator.hh"
//#include "HistoManager.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(Geometry* det, MyPrimaryGenerator* prim)
  : G4UserRunAction(),
    fDetector(det), fPrimary(prim), fRun(0),
    fRunMessenger(0), fPrint(true)    
{
 //fHistoManager = new HistoManager();
 fRunMessenger = new RunMessenger(this);
    
    auto analysisManager = G4AnalysisManager::Instance();
    //
    // Make N tuples
    //
    analysisManager->CreateNtuple("Ar", "Ar");
    analysisManager->CreateNtupleDColumn("Neutron_En");
    analysisManager->CreateNtupleDColumn("Target Z");
    analysisManager->CreateNtupleDColumn("Target A");
    analysisManager->CreateNtupleDColumn("Result Z");
    analysisManager->CreateNtupleDColumn("Result A");
    analysisManager->CreateNtupleDColumn("Nucleus_en");
    analysisManager->CreateNtupleDColumn("time");
    analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
 delete G4AnalysisManager::Instance();
 delete fRunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* RunAction::GenerateRun()
{ 
  fRun = new Run(fDetector); 
  return fRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* run)
{    
  // show Rndm status
  if (isMaster) G4Random::showEngineStatus();
    
  // keep run condition
  if (fPrimary) { 
    G4ParticleDefinition* particle 
      = fPrimary->GetParticleGun()->GetParticleDefinition();
    G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
    fRun->SetPrimary(particle, energy);
  }
       
  //N tuples
  //
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4int runID = run->GetRunID();
    
    std::stringstream strRunID;
    strRunID << runID;
    
    analysisManager->OpenFile("Sanidine_Irradiation"+strRunID.str());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*)
{
  if (isMaster) fRun->EndOfRun(fPrint);    
  
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    //Save the File and Close
    analysisManager->Write();
    analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::SetPrintFlag(G4bool flag)
{ 
  fPrint = flag;
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
