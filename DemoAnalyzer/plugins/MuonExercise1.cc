// -*- C++ -*-
//
// Package:    CMSDASExercises/MuonExercise1
// Class:      MuonExercise1
// 
/**\class MuonExercise1 MuonExercise1.cc CMSDASExercises/MuonExercise1/plugins/MuonExercise1.cc

 Description: Short Muon exercise for CMSDAS

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Norbert Neumeister
//         Created:  Thu, 10 Dec 2016 09:31:13 GMT
//
//

// system include files
#include <memory>
#include <iomanip>

#include <TLorentzVector.h>
#include <TVector3.h>
#include <TTree.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "Math/GenVector/VectorUtil.h"



#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"


//
// class declaration
//

class MuonExercise1 : public edm::EDAnalyzer {

  public:

    explicit MuonExercise1(const edm::ParameterSet&);
    ~MuonExercise1();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  private:

    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
    //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

    // ----------member data ---------------------------
     
  edm::EDGetTokenT<pat::MuonCollection> muonCollToken;
  edm::EDGetTokenT<pat::JetCollection> jetCollToken;

  edm::EDGetTokenT<pat::PackedGenParticleCollection> genCollToken;  
  TH1D* h_genpt;
  TH1D* h_pt;
  

  TTree* tuple;

  float l1_pt,l1_eta,l1_phi;
  int l1_ch;

  float l2_pt,l2_eta,l2_phi;
  int l2_ch;

  int nj;
  int ncj;
  int nfj;
  int nbj;

  float j1_pt,j1_eta,j1_phi,j1_csv; int j1_puid;//jet with highest energy
  float fj_pt,fj_eta,fj_phi,fj_csv; int fj_puid;//most fwd jet
  float b1_pt,b1_eta,b1_phi,b1_csv; int b1_puid;//b-tagged jet with highest pt


  float deta_fj_b1;
  float deta_fj_l;
  float dphi_l1_l2;
  float dR_l1_l2;


  ///aux counters
  int nleptons;
  int njets;

};

//
// constructors and destructor
//
MuonExercise1::MuonExercise1(const edm::ParameterSet& iConfig) {

  edm::InputTag theMuonLabel("slimmedMuons");
  edm::InputTag theGenMuonLabel("packedGenParticles");

  edm::InputTag theJetLabel("slimmedJets");

  muonCollToken = consumes<pat::MuonCollection>(theMuonLabel);
  genCollToken = consumes<pat::PackedGenParticleCollection>(theGenMuonLabel);
  jetCollToken = consumes<pat::JetCollection>(theJetLabel);

  edm::Service<TFileService> fs;
  h_pt = fs->make<TH1D>("pt", "RECO pt", 100, 0.0, 200.0);
  h_genpt = fs->make<TH1D>("genpt", "GEN pt", 100, 0.0, 200.0);
  

  tuple = fs->make<TTree>("tuple","tuple");
  tuple->Branch("l1_pt",&l1_pt,"l1_pt/F");
  tuple->Branch("l1_eta",&l1_eta,"l1_eta/F");
  tuple->Branch("l1_phi",&l1_phi,"l1_phi/F");
  tuple->Branch("l1_ch",&l1_ch,"l1_ch/I");

  tuple->Branch("l2_pt",&l2_pt,"l2_pt/F");
  tuple->Branch("l2_eta",&l2_eta,"l2_eta/F");
  tuple->Branch("l2_phi",&l2_phi,"l2_phi/F");
  tuple->Branch("l2_ch",&l2_ch,"l2_ch/I");


  tuple->Branch("nj",&nj,"nj/I");
  tuple->Branch("ncj",&ncj,"ncj/I");
  tuple->Branch("nbj",&nbj,"nbj/I");
  tuple->Branch("nfj",&nfj,"nfj/I");

  tuple->Branch("j1_pt",&j1_pt,"j1_pt/F");
  tuple->Branch("j1_eta",&j1_eta,"j1_eta/F");
  tuple->Branch("j1_phi",&j1_phi,"j1_phi/F");
  tuple->Branch("j1_csv",&j1_csv,"j1_csv/F");
  tuple->Branch("j1_puid",&j1_puid,"j1_puid/I");

  tuple->Branch("b1_pt",&b1_pt,"b1_pt/F");
  tuple->Branch("b1_eta",&b1_eta,"b1_eta/F");
  tuple->Branch("b1_phi",&b1_phi,"b1_phi/F");
  tuple->Branch("b1_csv",&b1_csv,"b1_csv/F");
  tuple->Branch("b1_puid",&b1_puid,"b1_puid/I");

  tuple->Branch("fj_pt",&fj_pt,"fj_pt/F");
  tuple->Branch("fj_eta",&fj_eta,"fj_eta/F");
  tuple->Branch("fj_phi",&fj_phi,"fj_phi/F");
  tuple->Branch("fj_csv",&fj_csv,"fj_csv/F");
  tuple->Branch("fj_puid",&fj_puid,"fj_puid/I");


  tuple->Branch("deta_fj_b1",&deta_fj_b1,"deta_fj_b1/F");
  tuple->Branch("deta_fj_l",&deta_fj_l,"deta_fj_l/F");
  tuple->Branch("dphi_l1_l2",&dphi_l1_l2,"dphi_l1_l2/F");
  tuple->Branch("dR_l1_l2",&dR_l1_l2,"dR_l1_l2/F");



  nleptons=0;
  njets=0;

}


MuonExercise1::~MuonExercise1() {
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void MuonExercise1::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  using namespace edm;
  using namespace std;
  using namespace reco;
  using namespace pat;
  using namespace l1extra;

  //
  // RECO Muons
  //
  edm::Handle<vector<pat::Muon>> muons;
  iEvent.getByToken(muonCollToken, muons);
  //cout << "Number of RECO muons: " << muons->size() << endl;

  
  const pat::Muon* l1=0;
  const pat::Muon* l2=0;
  int nmuons=0;
  for (auto it = muons->cbegin(); it != muons->cend(); ++it) {
    if( it->pt()<15 ) continue;
    if( fabs(it->eta())>2.4 ) continue;
    if( not (it->isLooseMuon()) ) continue;
    if( not (it->isGlobalMuon()) ) continue;
    if( not (it->passed(reco::Muon::PFIsoMedium))  ) continue;

    nmuons++; //muons are counted after basic selections
    nleptons++;

    if(l1==0) l1=&(*it);
    else if(l2==0) l2=&(*it);
  }


  
  if(!l1 || !l2 ) return;
  if(l1->pt()<25 || l2->pt()<15 ) return;
  if(nmuons>2) return;


  
  edm::Handle<vector<pat::Jet>>  jets;
  iEvent.getByToken(jetCollToken, jets);
  const pat::Jet* j1=0;
  const pat::Jet* b1=0;
  const pat::Jet* fj=0;
  nj =0;
  ncj = 0;
  nbj = 0;
  nfj = 0;
  for (const pat::Jet &j : *jets) {
    if (j.pt() < 25) continue;
    if(deltaR(j,*l1)<0.4) continue;
    if(deltaR(j,*l2)<0.4) continue;
    if(! bool(j.userInt("pileupJetId:fullId") & (1<<2)) ) continue; //loose

    if(!j1) j1=&j;
  

    nj++;
    njets++;
    if(fabs(j.eta())<2.4)ncj++;
    if(fabs(j.eta())>2.4)nfj++;


    //non-btagged jets
    float csv = j.bDiscriminator("pfDeepCSVJetTags:probb") + j.bDiscriminator("pfDeepCSVJetTags:probbb");
    if(csv<0.4941){//medium
      if(!fj) fj=&j;
      else if(fabs(j.eta())>fabs(fj->eta())) fj=&j;
    }


    //btagged jets
    if(csv>0.4941){//medium
      nbj++;
      if(!b1) b1 = &j;
    }
    
  }

  if(!j1) return;
  if(!fj) return;
  if(!b1) return;






  ///fill tree
  l1_pt = l1->pt();
  l1_eta= l1->eta();
  l1_phi= l1->phi();
  l1_ch = l1->charge();

  l2_pt = l2->pt();
  l2_eta= l2->eta();
  l2_phi= l2->phi();
  l2_ch = l2->charge();

  j1_pt = j1->pt();
  j1_eta  = j1->eta(); 
  j1_phi  = j1->phi();
  j1_csv  = j1->bDiscriminator("pfDeepCSVJetTags:probb") + j1->bDiscriminator("pfDeepCSVJetTags:probbb");//j1->bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  j1_puid  = j1->userInt("pileupJetId:fullId") ;

  fj_pt = fj->pt();
  fj_eta  = fj->eta(); 
  fj_phi  = fj->phi();
  fj_csv  = fj->bDiscriminator("pfDeepCSVJetTags:probb") + fj->bDiscriminator("pfDeepCSVJetTags:probbb");//fj->bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  fj_puid  = fj->userInt("pileupJetId:fullId") ;

  b1_pt = b1->pt();
  b1_eta  = b1->eta(); 
  b1_phi  = b1->phi();
  b1_csv  = b1->bDiscriminator("pfDeepCSVJetTags:probb") + b1->bDiscriminator("pfDeepCSVJetTags:probbb"); //b1->bDiscriminator("combinedInclusiveSecondaryVertexV2BJetTags");
  b1_puid  = b1->userInt("pileupJetId:fullId") ;


  deta_fj_b1 = fabs(fj->eta() - b1->eta());
  deta_fj_l = fabs(fj->eta() - l1->eta()) < fabs(fj->eta() - l2->eta()) ? fabs(fj->eta() - l1->eta()) : fabs(fj->eta() - l2->eta());
  dphi_l1_l2 = l1->phi() - l2->phi();
  dR_l1_l2 = deltaR(*l1,*l2);

 

  tuple->Fill();



    // printf("jet  with pt %5.1f (raw pt %5.1f), eta %+4.2f, btag CSV %.3f, CISV %.3f, pileup mva disc %+.2f\n",
    // 	   j.pt(), j.pt()*j.jecFactor("Uncorrected"), j.eta(), 
    // 	   std::max(0.f,j.bDiscriminator("combinedSecondaryVertexBJetTags")), 
    // 	   std::max(0.f,j.bDiscriminator("combinedInclusiveSecondaryVertexBJetTags")), 
    // 	   j.userFloat("pileupJetId:fullDiscriminant"));
    
    // if ((++ijet) == 1) { // for the first jet, let's print the leading constituents
    //   std::vector daus(j.daughterPtrVector());
    //   std::sort(daus.begin(), daus.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) { return p1->pt() > p2->pt(); }); // the joys of C++11
    //   for (unsigned int i2 = 0, n = daus.size(); i2 < n && i2 <= 3; ++i2) {
    // 	const pat::PackedCandidate &cand = dynamic_cast<const pat::PackedCandidate &>(*daus[i2]);
    // 	printf("         constituent %3d: pt %6.2f, dz(pv) %+.3f, pdgId %+3d\n", i2,cand.pt(),cand.dz(PV.position()),cand.pdgId());
    //   }
    // }


  // edm::Handle vertices;
  // iEvent.getByToken(vtxToken_, vertices);
  // if (vertices->empty()) return; // skip the event if no PV found
  // const reco::Vertex &PV = vertices->front();

  // edm::Handle muons;
  // iEvent.getByToken(muonToken_, muons);
  // for (const pat::Muon &mu : *muons) {
  //   if (mu.pt() < 5 || !mu.isLooseMuon()) continue;
  //   printf("muon with pt %4.1f, dz(PV) %+5.3f, POG loose id %d, tight id %d\n",
  // 	   mu.pt(), mu.muonBestTrack()->dz(PV.position()), mu.isLooseMuon(), mu.isTightMuon(PV));
  // }

  // edm::Handle electrons;
  // iEvent.getByToken(electronToken_, electrons);
  // for (const pat::Electron &el : *electrons) {
  //   if (el.pt() < 5) continue;
  //   printf("elec with pt %4.1f, supercluster eta %+5.3f, sigmaIetaIeta %.3f (%.3f with full5x5 shower shapes), lost hits %d, pass conv veto %d\n",
  // 	   el.pt(), el.superCluster()->eta(), el.sigmaIetaIeta(), el.full5x5_sigmaIetaIeta(), el.gsfTrack()->trackerExpectedHitsInner().numberOfLostHits(), el.passConversionVeto());
  // }

  // edm::Handle photons;
  // iEvent.getByToken(photonToken_, photons);
  // for (const pat::Photon &pho : *photons) {
  //   if (pho.pt() < 20 or pho.chargedHadronIso()/pho.pt() > 0.3) continue;
  //   printf("phot with pt %4.1f, supercluster eta %+5.3f, sigmaIetaIeta %.3f (%.3f with full5x5 shower shapes)\n",
  // 	   pho.pt(), pho.superCluster()->eta(), pho.sigmaIetaIeta(), pho.full5x5_sigmaIetaIeta());
  // }

  // edm::Handle taus;
  // iEvent.getByToken(tauToken_, taus);
  // for (const pat::Tau &tau : *taus) {
  //   if (tau.pt() < 20) continue;
  //   printf("tau  with pt %4.1f, dxy signif %.1f, ID(byMediumCombinedIsolationDeltaBetaCorr3Hits) %.1f, lead candidate pt %.1f, pdgId %d \n",
  // 	   tau.pt(), tau.dxy_Sig(), tau.tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits"), tau.leadCand()->pt(), tau.leadCand()->pdgId());
  // }

  


//  //
//  // GEN Muons
//  edm::Handle <pat::PackedGenParticleCollection> genColl;
//  iEvent.getByToken(genCollToken, genColl);
//  int n = 0;
//  for (auto it = genColl->cbegin(); it != genColl->cend(); ++it) if ( abs((*it).pdgId()) == 13 && fabs((*it).eta()) < 2.4 && (*it).pt() > 1.5 ) n++;
//  //cout << "Number of GEN muons: " << n << endl;
//
//  for (auto it = genColl->cbegin(); it != genColl->cend(); ++it) {
//
//    // put your code here
//    
//  }




}


// ------------ method called once each job just before starting event loop  ------------
void MuonExercise1::beginJob() {
}

// ------------ method called once each job just after ending the event loop  ------------
void MuonExercise1::endJob() {

  std::cout<<"Events selected: "<<tuple->GetEntries()<<std::endl;
  std::cout<<"leptons selected: "<<nleptons<<std::endl;
  std::cout<<"jets selected: "<<njets<<std::endl;

}


// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void MuonExercise1::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  // The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuonExercise1);
