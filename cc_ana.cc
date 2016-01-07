// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/FastJets.hh"

#include "Rivet/Projections/LeadingParticlesFinalState.hh"

namespace Rivet {


  class cc_ana : public Analysis {
  public:

    /// Constructor
    cc_ana()
      : Analysis("cc_ana")
    {    }


    /// Book histograms and initialise projections before the run
    void init() {
      const FastJets jets(FinalState(-10, 10, 0.0*GeV), FastJets::ANTIKT, 0.5);
      addProjection(jets, "Jets");
   
      LeadingParticlesFinalState photonfs(FinalState(-5, 5, 30.0*GeV));
      photonfs.addParticleId(PID::PHOTON);
      addProjection(photonfs, "LeadingPhoton");


      _h_h_1 = bookHisto1D("h_low_eta_high_pt_beta", 18, 0, M_PI);
      _h_h_2 = bookHisto1D("h_low_eta_high_pt_jet1_pt", 30, 0, 2500);
      _h_h_3 = bookHisto1D("h_low_eta_high_pt_jet2_pt", 30, 0, 2500);
      _h_h_4 = bookHisto1D("h_low_eta_high_pt_jet3_pt", 30, 0, 2500);
      _h_h_5 = bookHisto1D("h_low_eta_high_pt_del_eta", 30, -3.0, 3.0);
      _h_h_6 = bookHisto1D("h_low_eta_high_pt_del_phi", 30, -3.0, 3.0);

      _h_h_7 = bookHisto1D("h_medium_eta_high_pt_beta", 18, 0, M_PI);
      _h_h_8 = bookHisto1D("h_medium_eta_high_pt_jet1_pt", 30, 0, 2500);
      _h_h_9 = bookHisto1D("h_medium_eta_high_pt_jet2_pt", 30, 0, 2500);
      _h_h_10 = bookHisto1D("h_medium_eta_high_pt_jet3_pt", 30, 0, 2500);
      _h_h_11 = bookHisto1D("h_medium_eta_high_pt_del_eta", 30, -3.0, 3.0);
      _h_h_12 = bookHisto1D("h_medium_eta_high_pt_del_phi", 30, -3.0, 3.0);

      _h_h_13 = bookHisto1D("h_high_eta_high_pt_beta", 18, 0, M_PI);
      _h_h_14 = bookHisto1D("h_high_eta_high_pt_jet1_pt", 30, 0, 2500);
      _h_h_15 = bookHisto1D("h_high_eta_high_pt_jet2_pt", 30, 0, 2500);
      _h_h_16 = bookHisto1D("h_high_eta_high_pt_jet3_pt", 30, 0, 2500);
      _h_h_17 = bookHisto1D("h_high_eta_high_pt_del_eta", 30, -3.0, 3.0);
      _h_h_18 = bookHisto1D("h_high_eta_high_pt_del_phi", 30, -3.0, 3.0);


      _h_m_1 = bookHisto1D("h_low_eta_medium_pt_beta", 18, 0, M_PI);
      _h_m_2 = bookHisto1D("h_low_eta_medium_pt_jet1_pt", 30, 0, 2500);
      _h_m_3 = bookHisto1D("h_low_eta_medium_pt_jet2_pt", 30, 0, 2500);
      _h_m_4 = bookHisto1D("h_low_eta_medium_pt_jet3_pt", 30, 0, 2500);
      _h_m_5 = bookHisto1D("h_low_eta_medium_pt_del_eta", 30, -3.0, 3.0);
      _h_m_6 = bookHisto1D("h_low_eta_medium_pt_del_phi", 30, -3.0, 3.0);

      _h_m_7 = bookHisto1D("h_medium_eta_medium_pt_beta", 18, 0, M_PI);
      _h_m_8 = bookHisto1D("h_medium_eta_medium_pt_jet1_pt", 30, 0, 2500);
      _h_m_9 = bookHisto1D("h_medium_eta_medium_pt_jet2_pt", 30, 0, 2500);
      _h_m_10 = bookHisto1D("h_medium_eta_medium_pt_jet3_pt", 30, 0, 2500);
      _h_m_11 = bookHisto1D("h_medium_eta_medium_pt_del_eta", 30, -3.0, 3.0);
      _h_m_12 = bookHisto1D("h_medium_eta_medium_pt_del_phi", 30, -3.0, 3.0);

      _h_m_13 = bookHisto1D("h_high_eta_medium_pt_beta", 18, 0, M_PI);
      _h_m_14 = bookHisto1D("h_high_eta_medium_pt_jet1_pt", 30, 0, 2500);
      _h_m_15 = bookHisto1D("h_high_eta_medium_pt_jet2_pt", 30, 0, 2500);
      _h_m_16 = bookHisto1D("h_high_eta_medium_pt_jet3_pt", 30, 0, 2500);
      _h_m_17 = bookHisto1D("h_high_eta_medium_pt_del_eta", 30, -3.0, 3.0);
      _h_m_18 = bookHisto1D("h_high_eta_medium_pt_del_phi", 30, -3.0, 3.0);


      _h_l_1 = bookHisto1D("h_low_eta_low_pt_beta", 18, 0, M_PI);
      _h_l_2 = bookHisto1D("h_low_eta_low_pt_jet1_pt", 30, 0, 2500);
      _h_l_3 = bookHisto1D("h_low_eta_low_pt_jet2_pt", 30, 0, 2500);
      _h_l_4 = bookHisto1D("h_low_eta_low_pt_jet3_pt", 30, 0, 2500);
      _h_l_5 = bookHisto1D("h_low_eta_low_pt_del_eta", 30, -3.0, 3.0);
      _h_l_6 = bookHisto1D("h_low_eta_low_pt_del_phi", 30, -3.0, 3.0);

      _h_l_7 = bookHisto1D("h_medium_eta_low_pt_beta", 18, 0, M_PI);
      _h_l_8 = bookHisto1D("h_medium_eta_low_pt_jet1_pt", 30, 0, 2500);
      _h_l_9 = bookHisto1D("h_medium_eta_low_pt_jet2_pt", 30, 0, 2500);
      _h_l_10 = bookHisto1D("h_medium_eta_low_pt_jet3_pt", 30, 0, 2500);
      _h_l_11 = bookHisto1D("h_medium_eta_low_pt_del_eta", 30, -3.0, 3.0);
      _h_l_12 = bookHisto1D("h_medium_eta_low_pt_del_phi", 30, -3.0, 3.0);

      _h_l_13 = bookHisto1D("h_high_eta_low_pt_beta", 18, 0, M_PI);
      _h_l_14 = bookHisto1D("h_high_eta_low_pt_jet1_pt", 30, 0, 2500);
      _h_l_15 = bookHisto1D("h_high_eta_low_pt_jet2_pt", 30, 0, 2500);
      _h_l_16 = bookHisto1D("h_high_eta_low_pt_jet3_pt", 30, 0, 2500);
      _h_l_17 = bookHisto1D("h_high_eta_low_pt_del_eta", 30, -3.0, 3.0);
      _h_l_18 = bookHisto1D("h_high_eta_low_pt_del_phi", 30, -3.0, 3.0);


    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {
      const Jets& jets = applyProjection<FastJets>(event, "Jets").jetsByPt(30.0*GeV);
      if (jets.size() < 3) vetoEvent;
      const FourMomentum jet1 = jets[0].momentum();
      const FourMomentum jet2 = jets[1].momentum();
      const FourMomentum jet3 = jets[2].momentum();
      
      //const FinalState& photonfs = applyProjection<FinalState>(event, "LeadingPhoton");
      //if (photonfs.particles().size() < 1) vetoEvent;
      //const Particle& photon = photonfs.particles().front();
      //const FourMomentum jet3 = photon.momentum();

      // Cut on lead jet pT and lead/sublead jet centrality
      if (jet1.pT() < 100*GeV) vetoEvent;
      if (jet1.abseta() > 2.5 || jet2.abseta() > 2.5) vetoEvent;

      double dPhi12 = jet2.phi() - jet1.phi();
      if (dPhi12 > M_PI)  dPhi12 -= 2*M_PI; ///< @todo Use mapTo... functions?
      if (dPhi12 < -M_PI) dPhi12 += 2*M_PI; ///< @todo Use mapTo... functions?
      if (abs(abs(dPhi12) - M_PI) > 1.0) vetoEvent;

      // Construct eta & phi distances between 2nd and 3rd jets
      double dEta23 = jet3.eta() - jet2.eta(); ///< Note not abs
      double dPhi23 = jet3.phi() - jet2.phi(); ///< Note not abs
      if (dPhi23 > M_PI)  dPhi23 -= 2*M_PI; ///< @todo Use mapTo... functions?
      if (dPhi23 < -M_PI) dPhi23 += 2*M_PI; ///< @todo Use mapTo... functions?

      // Cut on distance between 2nd and 3rd jets
      const double R23 = add_quad(dPhi23, dEta23);
      if (!inRange(R23, 0.5, 1.5)) vetoEvent;

      // Cut on dijet mass
      const FourMomentum diJet = jet1 + jet2;
      if (diJet.mass() < 220*GeV) vetoEvent;

      //double jet_pt_r = (jet2.pT() + jet3.pT())/jet1.pT();
      //if (!inRange(jet_pt_r, 0.9, 1.1)) vetoEvent;

      //double jet_pt_r23 = jet3.pT()/jet2.pT();
      //if (jet_pt_r23<0.7) vetoEvent;
      // Calc beta and fill histogram (choose central or fwd histo inline)
      double del_eta = sign(jet2.eta())*dEta23;
      double beta = fabs(atan2(dPhi23, del_eta));

      //const double lepcut = 151.11661947806283; 
      //const double mepcut = 302.029859873333;
      //const double hepcut = 819.2469850804946;
      const double lepcut = 1.0; 
      const double mepcut = 1.0;
      const double hepcut = 1.0;



      if (inRange(jet1.pT(), 100*GeV,2500*GeV)){
         if (inRange(jet2.abseta(), 0.0, 0.8)){
           //if (jet1.p3().mod() < lepcut || jet2.p3().mod() < lepcut || jet3.p3().mod() < lepcut) vetoEvent;
           _h_h_1->fill(beta, event.weight());
           _h_h_2->fill(jet1.pT(), event.weight());
           _h_h_3->fill(jet2.pT(), event.weight());
           _h_h_4->fill(jet3.pT(), event.weight());
           _h_h_5->fill(del_eta, event.weight());
           _h_h_6->fill(dPhi23, event.weight());
         }
         if (inRange(jet2.abseta(), 0.8, 1.5)){
           if (jet1.p3().mod() < mepcut || jet2.p3().mod() < mepcut || jet3.p3().mod() < mepcut) vetoEvent;
           _h_h_7->fill(beta, event.weight());
           _h_h_8->fill(jet1.pT(), event.weight());
           _h_h_9->fill(jet2.pT(), event.weight());
           _h_h_10->fill(jet3.pT(), event.weight());
           _h_h_11->fill(del_eta, event.weight());
           _h_h_12->fill(dPhi23, event.weight());
         }
         if (inRange(jet2.abseta(), 0.8, 2.5)){
           if (jet1.p3().mod() < hepcut || jet2.p3().mod() < hepcut || jet3.p3().mod() < hepcut) vetoEvent;
           _h_h_13->fill(beta, event.weight());
           _h_h_14->fill(jet1.pT(), event.weight());
           _h_h_15->fill(jet2.pT(), event.weight());
           _h_h_16->fill(jet3.pT(), event.weight());
           _h_h_17->fill(del_eta, event.weight());
           _h_h_18->fill(dPhi23, event.weight());
         }
      }

      if (inRange(jet1.pT(), 510*GeV,700*GeV)){
         if (inRange(jet2.abseta(), 0.0, 0.8)){
           if (jet1.p3().mod() < lepcut || jet2.p3().mod() < lepcut || jet3.p3().mod() < lepcut) vetoEvent;
           _h_m_1->fill(beta, event.weight());
           _h_m_2->fill(jet1.pT(), event.weight());
           _h_m_3->fill(jet2.pT(), event.weight());
           _h_m_4->fill(jet3.pT(), event.weight());
           _h_m_5->fill(del_eta, event.weight());
           _h_m_6->fill(dPhi23, event.weight());
         }
         if (inRange(jet2.abseta(), 0.8, 1.5)){
           if (jet1.p3().mod() < mepcut || jet2.p3().mod() < mepcut || jet3.p3().mod() < mepcut) vetoEvent;
           _h_m_7->fill(beta, event.weight());
           _h_m_8->fill(jet1.pT(), event.weight());
           _h_m_9->fill(jet2.pT(), event.weight());
           _h_m_10->fill(jet3.pT(), event.weight());
           _h_m_11->fill(del_eta, event.weight());
           _h_m_12->fill(dPhi23, event.weight());
         }
         if (inRange(jet2.abseta(), 1.5, 2.5)){
           if (jet1.p3().mod() < hepcut || jet2.p3().mod() < hepcut || jet3.p3().mod() < hepcut) vetoEvent;
           _h_m_13->fill(beta, event.weight());
           _h_m_14->fill(jet1.pT(), event.weight());
           _h_m_15->fill(jet2.pT(), event.weight());
           _h_m_16->fill(jet3.pT(), event.weight());
           _h_m_17->fill(del_eta, event.weight());
           _h_m_18->fill(dPhi23, event.weight());
         }
      }

      if (inRange(jet1.pT(), 220*GeV,500*GeV)){
         if (inRange(jet2.abseta(), 0.0, 0.8)){
           if (jet1.p3().mod() < lepcut || jet2.p3().mod() < lepcut || jet3.p3().mod() < lepcut) vetoEvent;
           _h_l_1->fill(beta, event.weight());
           _h_l_2->fill(jet1.pT(), event.weight());
           _h_l_3->fill(jet2.pT(), event.weight());
           _h_l_4->fill(jet3.pT(), event.weight());
           _h_l_5->fill(del_eta, event.weight());
           _h_l_6->fill(dPhi23, event.weight());
         }
         if (inRange(jet2.abseta(), 0.8, 1.5)){
           if (jet1.p3().mod() < mepcut || jet2.p3().mod() < mepcut || jet3.p3().mod() < mepcut) vetoEvent;
           _h_l_7->fill(beta, event.weight());
           _h_l_8->fill(jet1.pT(), event.weight());
           _h_l_9->fill(jet2.pT(), event.weight());
           _h_l_10->fill(jet3.pT(), event.weight());
           _h_l_11->fill(del_eta, event.weight());
           _h_l_12->fill(dPhi23, event.weight());
         }
         if (inRange(jet2.abseta(), 1.5, 2.5)){
           if (jet1.p3().mod() < hepcut || jet2.p3().mod() < hepcut || jet3.p3().mod() < hepcut) vetoEvent;
           _h_l_13->fill(beta, event.weight());
           _h_l_14->fill(jet1.pT(), event.weight());
           _h_l_15->fill(jet2.pT(), event.weight());
           _h_l_16->fill(jet3.pT(), event.weight());
           _h_l_17->fill(del_eta, event.weight());
           _h_l_18->fill(dPhi23, event.weight());
         }
      }




    }


    /// Normalise histograms etc., after the run
    void finalize() {
      //const double width = _h_hTotD->bin(0).xWidth();
      //const double width = 1.0;
       
      //normalize(_h_hTotD, width);
      //normalize(_h_hTotDF, width);
      //normalize(_h_1, width);
      //normalize(_h_2, width);
      //normalize(_h_3, width);
      //normalize(_h_5, width);
      //normalize(_h_6, width);

    }


  private:

    /// @name Histograms
    Histo1DPtr _h_h_1;
    Histo1DPtr _h_h_2;
    Histo1DPtr _h_h_3;
    Histo1DPtr _h_h_4;
    Histo1DPtr _h_h_5;
    Histo1DPtr _h_h_6;
    Histo1DPtr _h_h_7;
    Histo1DPtr _h_h_8;
    Histo1DPtr _h_h_9;
    Histo1DPtr _h_h_10;
    Histo1DPtr _h_h_11;
    Histo1DPtr _h_h_12;
    Histo1DPtr _h_h_13;
    Histo1DPtr _h_h_14;
    Histo1DPtr _h_h_15;
    Histo1DPtr _h_h_16;
    Histo1DPtr _h_h_17;
    Histo1DPtr _h_h_18;
    //@}
    Histo1DPtr _h_m_1;
    Histo1DPtr _h_m_2;
    Histo1DPtr _h_m_3;
    Histo1DPtr _h_m_4;
    Histo1DPtr _h_m_5;
    Histo1DPtr _h_m_6;
    Histo1DPtr _h_m_7;
    Histo1DPtr _h_m_8;
    Histo1DPtr _h_m_9;
    Histo1DPtr _h_m_10;
    Histo1DPtr _h_m_11;
    Histo1DPtr _h_m_12;
    Histo1DPtr _h_m_13;
    Histo1DPtr _h_m_14;
    Histo1DPtr _h_m_15;
    Histo1DPtr _h_m_16;
    Histo1DPtr _h_m_17;
    Histo1DPtr _h_m_18;

    Histo1DPtr _h_l_1;
    Histo1DPtr _h_l_2;
    Histo1DPtr _h_l_3;
    Histo1DPtr _h_l_4;
    Histo1DPtr _h_l_5;
    Histo1DPtr _h_l_6;
    Histo1DPtr _h_l_7;
    Histo1DPtr _h_l_8;
    Histo1DPtr _h_l_9;
    Histo1DPtr _h_l_10;
    Histo1DPtr _h_l_11;
    Histo1DPtr _h_l_12;
    Histo1DPtr _h_l_13;
    Histo1DPtr _h_l_14;
    Histo1DPtr _h_l_15;
    Histo1DPtr _h_l_16;
    Histo1DPtr _h_l_17;
    Histo1DPtr _h_l_18;



  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(cc_ana);

}
