#ifndef GEOMETRY_HH
#define GEOMETRY_HH


#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSTrackLength.hh"
#include "G4PSCellFlux.hh"
#include "G4SDManager.hh"


class G4VPhysicalVolume;

//-----------------------------------------------------------------------------
class Geometry: public G4VUserDetectorConstruction
//-----------------------------------------------------------------------------

{
public:
    Geometry();
    ~Geometry();
    
    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetScoringVolume() const {return fDetector; }

protected:
    G4LogicalVolume* fDetector;
};
#endif
