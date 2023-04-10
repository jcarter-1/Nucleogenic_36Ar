//
// RunAction
//

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4VProcess.hh"
#include "globals.hh"
#include <map>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class Geometry;
class Run;
class RunMessenger;
class MyPrimaryGenerator;
class HistoManager;
class G4Run;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RunAction : public G4UserRunAction
{
  public:
    RunAction(Geometry*, MyPrimaryGenerator*);
   ~RunAction();

  public:
    virtual G4Run* GenerateRun();   
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
    
    void SetPrintFlag(G4bool);
                                
  private:
    Geometry*                  fDetector;
    MyPrimaryGenerator*        fPrimary;
    Run*                       fRun;        
    HistoManager*              fHistoManager;
    RunMessenger*              fRunMessenger;
     
    G4bool   fPrint;      //optional printing           
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

