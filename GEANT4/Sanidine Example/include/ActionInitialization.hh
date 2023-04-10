

#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class Geometry;
class G4VSteppingVerbose;

/// Action initialization class.
///

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization(Geometry* detector);
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
    
    virtual G4VSteppingVerbose* InitializeSteppingVerbose() const;
   
  private:
    Geometry* fDetector;
};

#endif

    
