//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************

#ifndef H02_PRIMARY_GENERATOR_ACTION_H
#define H02_PRIMARY_GENERATOR_ACTION_H

#include <map>
#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "Detector_analysis_var.hh"

#include "TRandom.h"

class G4Event;
class G4VPrimaryGenerator;
class PrimaryGeneratorMessenger;


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event* anEvent);

  void SetGenerator(G4VPrimaryGenerator* gen);
  void SetGenerator(G4String genname);

  const G4VPrimaryGenerator* GetGenerator() const;
  G4String GetGeneratorName() const;

private:
  G4VPrimaryGenerator* fParticleGun;
  G4VPrimaryGenerator* fPythiaGen;
  G4VPrimaryGenerator* fHepMCGen;

  G4ParticleGun *fParticleGun_ ;
  G4VPrimaryGenerator* fCurrentGenerator;
  G4String fCurrentGeneratorName;
  std::map<G4String, G4VPrimaryGenerator*> fGentypeMap;

  PrimaryGeneratorMessenger* fMessenger;

};

inline void PrimaryGeneratorAction::SetGenerator(G4VPrimaryGenerator* gen)
{
  fCurrentGenerator= gen;
}

inline void PrimaryGeneratorAction::SetGenerator(G4String genname)
{
  std::map<G4String, G4VPrimaryGenerator*>::iterator
  pos = fGentypeMap.find(genname);
  if(pos != fGentypeMap.end()) {
    fCurrentGenerator= pos->second;
    fCurrentGeneratorName= genname;
  }
}

inline const G4VPrimaryGenerator* PrimaryGeneratorAction::GetGenerator() const
{
    return fGentypeMap.at(fCurrentGeneratorName);
}

inline G4String PrimaryGeneratorAction::GetGeneratorName() const
{
  return fCurrentGeneratorName;
}

#endif
