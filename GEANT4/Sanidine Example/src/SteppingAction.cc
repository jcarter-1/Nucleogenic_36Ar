#include "SteppingAction.hh"
#include "Run.hh"
//#include "HistoManager.hh"
#include "Analysis.hh"
#include "G4ParticleTypes.hh"
#include "G4RunManager.hh"
#include "G4HadronicProcess.hh"
                           
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction()
: G4UserSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
 Run* run
   = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
         
  // count processes
  //
  const G4StepPoint* endPoint = aStep->GetPostStepPoint();
  G4VProcess* process   =
                   const_cast<G4VProcess*>(endPoint->GetProcessDefinedStep());
  run->CountProcesses(process);
  
  // check that an real interaction occured (eg. not a transportation)
  G4StepStatus stepStatus = endPoint->GetStepStatus();
  G4bool transmit = (stepStatus==fGeomBoundary || stepStatus==fWorldBoundary);
  if (transmit) return;
                      
  //real processes : sum track length
  //
  G4double stepLength = aStep->GetStepLength();
  run->SumTrack(stepLength);
  
  //energy-momentum balance initialisation
  //
  const G4StepPoint* prePoint = aStep->GetPreStepPoint();
  G4double Q             = - prePoint->GetKineticEnergy();
  G4ThreeVector Pbalance = - prePoint->GetMomentum();
  
  //initialisation of the nuclear channel identification
  //
  G4ParticleDefinition* particle = aStep->GetTrack()->GetDefinition();
  G4String partName = particle->GetParticleName();
  G4String nuclearChannel = partName;
  G4HadronicProcess* hproc = dynamic_cast<G4HadronicProcess*>(process);
  const G4Isotope* target = NULL;
  if (hproc) target = hproc->GetTargetIsotope();
  G4String targetName = "XXXX";
  if (target) targetName = target->GetName();
  nuclearChannel += " + " + targetName + " --> ";
  if (targetName == "XXXX") run->SetTargetXXX(true);
    
  //scattered primary particle (if any)
  //
  G4AnalysisManager* analysis = G4AnalysisManager::Instance();
  if (aStep->GetTrack()->GetTrackStatus() == fAlive) {
    G4double energy = endPoint->GetKineticEnergy();
    //
    G4ThreeVector momentum = endPoint->GetMomentum();
    Q        += energy;
    Pbalance += momentum;
    //
    nuclearChannel += partName + " + ";
  }
    //
    // Time
    //
  
    G4double time = aStep->GetTrack()->GetGlobalTime();
  //secondaries
  //
  const std::vector<const G4Track*>* secondary
                                    = aStep->GetSecondaryInCurrentStep();
  for (size_t lp=0; lp<(*secondary).size(); lp++) {
    particle = (*secondary)[lp]->GetDefinition();
    G4String name   = particle->GetParticleName();
    G4String type   = particle->GetParticleType();
    G4double energy = (*secondary)[lp]->GetKineticEnergy();
    G4double neutron_en = aStep->GetTrack()->GetKineticEnergy();
      
      if (type == "nucleus") {
          G4int Z = particle->GetAtomicNumber();
          G4int A = particle->GetAtomicMass();
          
          if (Z >= 17 and Z <= 19) {
                  if (hproc) target = hproc->GetTargetIsotope();
              
              G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
              analysisManager->FillNtupleDColumn(0, neutron_en);
              analysisManager->FillNtupleDColumn(1, target->GetZ());
              analysisManager->FillNtupleDColumn(2, target->GetN());
              analysisManager->FillNtupleDColumn(3, Z);
              analysisManager->FillNtupleDColumn(4, A);
              analysisManager->FillNtupleDColumn(5, energy);
              analysisManager->FillNtupleDColumn(6, time);
              analysisManager->AddNtupleRow();

          }
      }
    run->ParticleCount(name,energy);

    //energy-momentum balance
    G4ThreeVector momentum = (*secondary)[lp]->GetMomentum();
    Q        += energy;
    Pbalance += momentum;
    //count e- from internal conversion together with gamma
    if (particle == G4Electron::Electron()) particle = G4Gamma::Gamma();
    //particle flag
    fParticleFlag[particle]++;
  }
  
  //energy-momentum balance
  G4double Pbal = Pbalance.mag();
  run->Balance(Pbal);
  
  // nuclear channel
  const G4int kMax = 16;
  const G4String conver[] = {"0","","2 ","3 ","4 ","5 ","6 ","7 ","8 ","9 ",
                             "10 ","11 ","12 ","13 ","14 ","15 ","16 "};
  std::map<G4ParticleDefinition*,G4int>::iterator ip;
  for (ip = fParticleFlag.begin(); ip != fParticleFlag.end(); ip++) {
    particle = ip->first;
    G4String name = particle->GetParticleName();
    G4int nb = ip->second;
    if (nb > kMax) nb = kMax;
    G4String Nb = conver[nb];
    if (particle == G4Gamma::Gamma()) {
     run->CountGamma(nb);
     Nb = "N ";
     name = "gamma or e-";
    }
    if (ip != fParticleFlag.begin()) nuclearChannel += " + ";
    nuclearChannel += Nb + name;
  }
 
  ///G4cout << "\n nuclear channel: " << nuclearChannel << G4endl;
  run->CountNuclearChannel(nuclearChannel, Q);
    
  fParticleFlag.clear();
              
  // kill event after first interaction
  //
  G4RunManager::GetRunManager()->AbortEvent();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

