// -*- C++ -*-
//
// Package:    PatJetVertexCorrector
// Class:      PatJetVertexCorrector
//
/**\class PatJetVertexCorrector PatJetVertexCorrector.cc MyAnalysis/PatJetVertexCorrector/src/PatJetVertexCorrector.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Dinko Ferencek,8 R-004,+41227676479,
//         Created:  Thu Aug 15 03:46:25 CEST 2013
// $Id: PatJetVertexCorrector.cc,v 1.1 2013/08/15 03:21:16 ferencek Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "DataFormats/PatCandidates/interface/Jet.h"

//
// class declaration
//

class PatJetVertexCorrector : public edm::EDProducer {
   public:
      explicit PatJetVertexCorrector(const edm::ParameterSet&);
      ~PatJetVertexCorrector();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
      const edm::InputTag  vertexSource;
      const edm::InputTag  jetSource;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
PatJetVertexCorrector::PatJetVertexCorrector(const edm::ParameterSet& iConfig) :

  vertexSource(iConfig.getParameter<edm::InputTag>("VertexSource")),
  jetSource(iConfig.getParameter<edm::InputTag>("JetSource"))

{
  //register your products
  produces< std::vector< pat::Jet > >();

  //now do what ever other initialization is needed

}


PatJetVertexCorrector::~PatJetVertexCorrector()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
PatJetVertexCorrector::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<reco::VertexCollection> primaryVertices;
  iEvent.getByLabel(vertexSource,primaryVertices);

  edm::Handle<std::vector<pat::Jet > > jets;
  iEvent.getByLabel(jetSource, jets);

  std::auto_ptr< std::vector<pat::Jet> > centeredJets( new std::vector<pat::Jet> (*jets) );

  for( std::vector<pat::Jet>::iterator it = centeredJets->begin(); it != centeredJets->end(); ++it )
    it->setVertex(primaryVertices->front().position());

  // put jets into event
  iEvent.put(centeredJets);
}

// ------------ method called once each job just before starting event loop  ------------
void
PatJetVertexCorrector::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
PatJetVertexCorrector::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void
PatJetVertexCorrector::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void
PatJetVertexCorrector::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void
PatJetVertexCorrector::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void
PatJetVertexCorrector::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PatJetVertexCorrector::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PatJetVertexCorrector);
