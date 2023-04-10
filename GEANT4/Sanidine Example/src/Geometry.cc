#include "Geometry.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"
#include "G4Orb.hh"
#include "G4PhysicalConstants.hh"


//---------------------------------------------------------------
//---------------------------------------------------------------
Geometry::Geometry()
{}
//---------------------------------------------------------------
//---------------------------------------------------------------
Geometry::~Geometry()
{}

//---------------------------------------------------------------
//---------------------------------------------------------------
G4VPhysicalVolume* Geometry::Construct()
{
    //-----------------------------------------------------------
    // Material Manager
    //-----------------------------------------------------------
    G4NistManager* nist = G4NistManager::Instance();
    //-----------------------------------------------------------
    // Make the World
    //-----------------------------------------------------------
    G4double len_x_world = 0.45*cm;
    G4double len_y_world = 0.45*cm;
    G4double len_z_world = 0.3*cm;

    G4Box *solidWorld = new G4Box("Solid_World",
                                  len_x_world, len_y_world,
                                  len_z_world);

    //-----------------------------------------------------------
    // Define the Logical Volume
    //-----------------------------------------------------------
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4LogicalVolume* LogicalWorld = new G4LogicalVolume(solidWorld,
                                                        worldMat,
                                                        "Logical_World");


    //-----------------------------------------------------------
    // Place the World
    //-----------------------------------------------------------
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0,
                                                     G4ThreeVector(),
                                                     LogicalWorld,
                                                     "physical_World",
                                                     0,
                                                     false,
                                                     0,
                                                     true);
    auto worldVisAtt  = new G4VisAttributes(G4Colour(2.,1.,1., 1));

    worldVisAtt ->SetVisibility(false);
    LogicalWorld ->SetVisAttributes(worldVisAtt);
    //-----------------------------------------------------------
    // Materials Needed
    //-----------------------------------------------------------
    G4int ncomponents, natoms;
    
    //
    // CLICIT
    //
    G4Material* CadMat = nist->FindOrBuildMaterial("G4_Cd");
    G4Material* AlMat = nist->FindOrBuildMaterial("G4_Al");
    
    
    
    //
    // Inner
    //
    G4Tubs* al_inner = new G4Tubs("Al_inner",
                                     0.41*mm,
                                     (1.47 + 0.41)*mm,
                                     0.22*mm,
                                     0*deg, 360*deg);
    
    G4LogicalVolume* al_inner_logic = new G4LogicalVolume(al_inner,
                                                        AlMat,
                                                        "al_inner_logic");
    
    
    G4VPhysicalVolume* al_inner_phys = new G4PVPlacement(0,
                                                       G4ThreeVector(0,0,0),
                                                       al_inner_logic,
                                                       "Alinner_phys",
                                                       LogicalWorld,
                                                       false,
                                                       0,
                                                       true);
    
    //
    // Cadmium
    //
    G4Tubs* cad_sleeve = new G4Tubs("cad_sleeve",
                                    (1.47 + 0.4105)*mm,
                                    (1.47 + 0.4105 + 0.508)*mm,
                                     0.22*mm,
                                     0*deg, 360*deg);
    
    G4LogicalVolume* cad_sleeve_logic = new G4LogicalVolume(cad_sleeve,
                                                        CadMat,
                                                        "cad_sleeve_logic");
    
    
    G4VPhysicalVolume* cad_sleeve_phys = new G4PVPlacement(0,
                                                       G4ThreeVector(0,0,0),
                                                           cad_sleeve_logic,
                                                       "cad_sleeve_phys",
                                                       LogicalWorld,
                                                       false,
                                                       0,
                                                       true);
    
    
    auto cad_sleeveVisAtt = new G4VisAttributes(G4Colour(1.,0.,0., 1));
    cad_sleeveVisAtt ->SetVisibility(true);
    cad_sleeve_logic->SetVisAttributes(cad_sleeveVisAtt);

    
    //
    // Outer
    //
    G4Tubs* al_outer = new G4Tubs("Al_outer ",
                                  (1.47 + 0.4105 + 0.508 + 0.004)*mm,
                                  (1.47 + 0.4105 + 0.508 + 0.004 + 1.45)*mm,
                                     0.22*mm,
                                     0*deg, 360*deg);
    
    G4LogicalVolume* al_outer_logic = new G4LogicalVolume(al_outer,
                                                        AlMat,
                                                        "al_outer_logic");
    
    
    G4VPhysicalVolume* al_outer_phys = new G4PVPlacement(0,
                                                       G4ThreeVector(0,0,0),
                                                       al_outer_logic,
                                                       "Alouter_phys",
                                                       LogicalWorld,
                                                       false,
                                                       0,
                                                       true);
    
    
    auto AltubesVisAtt = new G4VisAttributes(G4Colour(0.1,1.,1., 1));
    AltubesVisAtt ->SetVisibility(true);
    al_outer_logic->SetVisAttributes(AltubesVisAtt);
    al_inner_logic->SetVisAttributes(AltubesVisAtt);

    
    //-----------------------------------------------------------------------------
    // Sandine
    //-----------------------------------------------------------------------------
    //G4int ncomponents, natoms;
    G4Element* K = new G4Element("Potassium", "K", 19., 39.0983*g/mole);
    G4Element* Al = new G4Element("Aluminum", "Al", 13., 26.981539*g/mole);
    G4Element* Na = new G4Element("Sodium", "Na", 11., 22.989769*g/mole);
    G4Element* Si = new G4Element("Silicon", "Si",  14., 28.0855*g/mole);
    G4Element* O  = new G4Element("Oxygen" , "O" , 8., 16.00*g/mole);
    G4Element* Ca = new G4Element("Calcium", "Ca", 20., 40.08*g/mole);
    
    G4Material* K2O= new G4Material("K2O", 2.35*g/cm3,
                                    ncomponents = 2);
    
    K2O->AddElement(K, natoms = 2);
    K2O->AddElement(O, natoms = 1);
    
    G4Material*CaO = new G4Material("CaO", 3.34*g/cm3,
                                    ncomponents = 2);
    
    CaO->AddElement(Ca, natoms = 1);
    CaO->AddElement(O, natoms = 1);
    
    G4Material* Na2O = new G4Material("Na2O", 2.27*g/cm3,
                                      ncomponents = 2);
    
    Na2O->AddElement(Na, natoms = 2);
    Na2O->AddElement(O, natoms = 1);
    
    G4Material* Al2O3 = new G4Material("Al2O3", 3.95*g/cm3,
                                       ncomponents = 2);
    
    Al2O3->AddElement(Al, natoms = 2);
    Al2O3->AddElement(O, natoms = 3);
    
    
    G4Material* SiO2 = new G4Material("SiO2", 2.65*g/cm3,
                                      ncomponents = 2);
    
    SiO2->AddElement(Si, natoms = 1);
    SiO2->AddElement(O, natoms = 2);
    
    
    G4Material* Sanidine =
    new G4Material("Sanidine", 2.52*g/cm3,
                   ncomponents = 5);
    
    Sanidine->AddMaterial(K2O, 12*perCent);
    Sanidine->AddMaterial(Al2O3, 18.59*perCent);
    Sanidine->AddMaterial(SiO2, 65.71*perCent);
    Sanidine->AddMaterial(Na2O, 2.82*perCent);
    Sanidine->AddMaterial(CaO, 0.88*perCent);

    G4Box * San_Box = new G4Box("San_Box",
                                    0.25*mm, 0.25*mm, 0.25*mm);

    G4LogicalVolume *San_logic = new G4LogicalVolume(San_Box,
                                                     Sanidine,
                                                      "San_LV");
    
    G4VPhysicalVolume *San_phys = new G4PVPlacement(0,
                                      G4ThreeVector(),
                                      San_logic ,
                                      "San_phys",
                                      LogicalWorld,
                                      false,
                                      0,
                                      true);

    auto SanVisAtt = new G4VisAttributes(G4Colour(2,1.,1., 1));
    SanVisAtt ->SetVisibility(true);
    San_logic->SetVisAttributes(SanVisAtt);
  
   //
   // Make Scoring Volume
   //
   fDetector = San_logic;
    
    //-----------------------------------------------------------------------------
    //Always return the physical World
    //-----------------------------------------------------------------------------
    return physWorld;
    
}
