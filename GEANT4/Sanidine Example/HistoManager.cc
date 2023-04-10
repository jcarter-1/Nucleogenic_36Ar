//
// HistoManager
//

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  : fFileName("Sanidine")
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  //  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);     //enable inactivation of histograms
  
  // Define histograms start values
  const G4int kMaxHisto = 14;
  const G4String id[] = {"0","1","2","3","4","5","6","7","8","9",
                         "10","11","12","13"};
  const G4String title[] = 
                { "dummy",                                          //0
                  "kinetic energy of scattered primary particle",   //1
                  "kinetic energy of gamma",                        //2
                  "kinetic energy of electrons",                    //3
                  "kinetic energy of neutrons",                     //4	  
                  "kinetic energy of protons",                      //5
                  "kinetic energy of deuterons",                    //6
                  "kinetic energy of alphas",                       //7
                  "kinetic energy of nuclei",                       //8
                  "kinetic energy of mesons",                       //9
                  "kinetic energy of baryons",                      //10
                  "Q = Ekin out - Ekin in",                         //11
                  "Pbalance = mag(P_out - P_in)",                   //12
                  "atomic mass of nuclei"                           //13
                 };  

  // Default values (to be reset via /analysis/h1/set command)               
  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;

  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  for (G4int k=0; k<kMaxHisto; k++) {
    G4int ih = analysisManager->CreateH1(id[k], title[k], nbins, vmin, vmax);
    analysisManager->SetH1Activation(ih, true);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
