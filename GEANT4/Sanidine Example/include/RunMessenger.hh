

#ifndef RunMessenger_h
#define RunMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class RunAction;
class G4UIdirectory;
class G4UIcmdWithABool;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RunMessenger: public G4UImessenger
{
public:
  RunMessenger(RunAction*);
  virtual ~RunMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  RunAction*        fRun;
    
  G4UIdirectory*    fRunDir;
  G4UIcmdWithABool* fPrintCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
