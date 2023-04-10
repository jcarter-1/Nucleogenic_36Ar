//
// Generator Program cc
//
#include "globals.hh"

#include "G4Event.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Neutron.hh"
#include "G4ParticleGun.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4VPhysicalVolume.hh"
#include "Randomize.hh"
#include "G4PhysicalConstants.hh"



#include "generator.hh"


MyPrimaryGenerator::MyPrimaryGenerator()
{
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);
    fParticleGun->SetParticleDefinition(G4Neutron::Neutron());
    
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
    
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{

    //
    // Intial Position of Particle
    //
    G4double theta = G4UniformRand()*twopi;


    
    
    //
    // Define Momentum Direction
    // Neutrons that always point to the centre
    //

    G4double phi = cos(theta/2);
    G4double phi2 = cos(theta);
    
    fParticleGun->SetParticlePosition(G4ThreeVector(0.4, 0.26*(2*G4UniformRand()-1), 0.26*(2*G4UniformRand()-1)));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1, 0, 0));

    //-----------------------------
    // Watt Fission Spectrum (Energy Spectrum)
    //-----------------------------

    G4double a = 0.95;
    G4double b = 1.05;
    G4double K = 1 + (b/8*a);
    G4double LL = (K + std::sqrt(K*K - 1))/a;
    
    G4double xx = - std::log(G4UniformRand());
    G4double Energy_watt = LL * xx;
    
    G4double thermals  = G4UniformRand()*G4UniformRand()*0.3*MeV/1e9;
    
    if (Energy_watt >20*MeV) {
        Energy_watt = thermals;
    }
    
    if(G4UniformRand() < 0.0025) {
        Energy_watt = thermals;
    }
    
    fParticleGun->SetParticleEnergy(Energy_watt);
    
    //
    // Generate
    //
    fParticleGun->GeneratePrimaryVertex(anEvent);

}


