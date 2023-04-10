//
// Physics List
//

#include "PhysicsList.hh"

#include "NeutronHPphysics.hh"

#include "G4DecayPhysics.hh"
#include "G4IonPhysics.hh"

#include "G4LossTableManager.hh"
#include "G4EmConfigurator.hh"
#include "G4UnitsTable.hh"

#include "G4ProcessManager.hh"
#include "G4Decay.hh"

#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4UniversalFluctuation.hh"


#include "G4StoppingPhysics.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

// Particles


#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
    // protected member of the base class
    verboseLevel = 1;

    // Deacy physics and all particles
    RegisterPhysics (new G4DecayPhysics(verboseLevel));
    
    //
    RegisterPhysics (new NeutronHPphysics(verboseLevel));
    //
    RegisterPhysics (new G4StoppingPhysics(verboseLevel));
}

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------
PhysicsList::~PhysicsList()
{

}

void PhysicsList::ConstructParticle()
{
  G4BosonConstructor  pBosonConstructor;
  pBosonConstructor.ConstructParticle();

  G4LeptonConstructor pLeptonConstructor;
  pLeptonConstructor.ConstructParticle();

  G4MesonConstructor pMesonConstructor;
  pMesonConstructor.ConstructParticle();

  G4BaryonConstructor pBaryonConstructor;
  pBaryonConstructor.ConstructParticle();

  G4IonConstructor pIonConstructor;
  pIonConstructor.ConstructParticle();

  G4ShortLivedConstructor pShortLivedConstructor;
  pShortLivedConstructor.ConstructParticle();
}


//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------

