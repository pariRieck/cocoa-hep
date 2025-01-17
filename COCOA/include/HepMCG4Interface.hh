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


#ifndef HEPMC_G4_INTERFACE_H
#define HEPMC_G4_INTERFACE_H
#include "TruthRecordGraph.hh"
#include "G4VPrimaryGenerator.hh"
#include "HepMC3/GenEvent.h"
#include "Config_reader_var.hh"


class HepMCG4Interface : public G4VPrimaryGenerator {

	TruthRecordGraph &m_truthrecordgraph = TruthRecordGraph::GetInstance();

private:
    Config_reader_var& config_json_var = Config_reader_var::GetInstance();

protected:
	// Note that the life of HepMC event object must be handled by users.
	// In the default implementation, a current HepMC event will be
	// deleted at GeneratePrimaryVertex() in the next event.
	HepMC3::GenEvent* hepmcEvent; // (care for single event case only)


	// We  have to take care for the position of primaries because
	// primary vertices outside the world voulme give rise to G4Execption.
	// If the default implementation is not adequate, an alternative
	// can be implemented in your own class.
	virtual G4bool CheckVertexInsideWorld(const G4ThreeVector& pos) const;

	void HepMC2G4(const HepMC3::GenEvent* hepmcevt, G4Event* g4event);

	virtual HepMC3::GenEvent* GenerateHepMCEvent();

	public:
		HepMCG4Interface();
		virtual ~HepMCG4Interface();

		// set/get methods
		HepMC3::GenEvent* GetHepMCGenEvent() const;

		// The default behavior is that a single HepMC event generated by
		// GenerateHepMCEvent() will be converted to G4Event through HepMC2G4().
		virtual void GeneratePrimaryVertex(G4Event* anEvent);
};

inline HepMC3::GenEvent* HepMCG4Interface::GetHepMCGenEvent() const
{
	return hepmcEvent;
}


#endif
