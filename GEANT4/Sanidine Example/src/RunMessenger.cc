//
// Run Messenger
//
#include "RunMessenger.hh"

#include "RunAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunMessenger::RunMessenger(RunAction* run)
:G4UImessenger(),fRun(run),
 fRunDir(0),
 fPrintCmd(0)
{
  fRunDir = new G4UIdirectory("/testhadr/run/");
  fRunDir->SetGuidance("run commands");
    
  fPrintCmd = new G4UIcmdWithABool("/testhadr/run/printStat",this);
  fPrintCmd->SetGuidance("print list of nuclear reactions");
  fPrintCmd->SetParameterName("print",false);
  fPrintCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunMessenger::~RunMessenger()
{
  delete fPrintCmd;
  delete fRunDir;      
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{      
  if( command == fPrintCmd )
   { fRun->SetPrintFlag(fPrintCmd->GetNewBoolValue(newValue));}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
