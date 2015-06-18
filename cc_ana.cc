// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/FastJets.hh"

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

      _h_1 = bookHisto1D("h_low_eta_low_pt", 18, 0, M_PI);
      _h_2 = bookHisto1D("h_high_eta_low_pt", 18, 0, M_PI);
      _h_3 = bookHisto1D("h_low_eta_medium_pt", 18, 0, M_PI);
      _h_4 = bookHisto1D("h_high_eta_medium_pt", 18, 0, M_PI);
      _h_5 = bookHisto1D("h_low_eta_high_pt", 18, 0, M_PI);
      _h_6 = bookHisto1D("h_high_eta_high_pt", 18, 0, M_PI);

      _h_7 =  bookHisto1D("h_lelp_jet1_pt", 30, 0, 250)
      _h_8 =  bookHisto1D("h_help_jet1_pt", 30, 0, 250)
      _h_9 =  bookHisto1D("h_lemp_jet1_pt", 30, 0, 550)
      _h_10 = bookHisto1D("h_hemp_jet1_pt", 30, 0, 550)
      _h_11 = bookHisto1D("h_lehp_jet1_pt", 30, 0, 2500)
      _h_12 = bookHisto1D("h_hehp_jet1_pt", 30, 0, 2500)

      _h_13 = bookHisto1D("h_lelp_jet2_pt", 30, 0, 250)
      _h_14 = bookHisto1D("h_help_jet2_pt", 30, 0, 250)
      _h_15 = bookHisto1D("h_lemp_jet2_pt", 30, 0, 550)
      _h_16 = bookHisto1D("h_hemp_jet2_pt", 30, 0, 550)
      _h_17 = bookHisto1D("h_lehp_jet2_pt", 30, 0, 2500)
      _h_18 = bookHisto1D("h_hehp_jet2_pt", 30, 0, 2500)

      _h_19 = bookHisto1D("h_lelp_jet3_pt", 30, 0, 250)
      _h_20 = bookHisto1D("h_help_jet3_pt", 30, 0, 250)
      _h_21 = bookHisto1D("h_lemp_jet3_pt", 30, 0, 550)
      _h_22 = bookHisto1D("h_hemp_jet3_pt", 30, 0, 550)
      _h_23 = bookHisto1D("h_lehp_jet3_pt", 30, 0, 2500)
      _h_24 = bookHisto1D("h_hehp_jet3_pt", 30, 0, 2500)
    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {
      const Jets& jets = applyProjection<FastJets>(event, "Jets").jetsByPt(30.0*GeV);
      if (jets.size() < 3) vetoEvent;

      const FourMomentum jet1 = jets[0].momentum();
      const FourMomentum jet2 = jets[1].momentum();
      const FourMomentum jet3 = jets[2].momentum();

      // Cut on lead jet pT and lead/sublead jet centrality
      if (jet1.pT() < 74*GeV) vetoEvent;
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

      // Calc beta and fill histogram (choose central or fwd histo inline)
      double beta = fabs(atan2(dPhi23, sign(jet2.eta())*dEta23));
      if (inRange(jet1.pT(), 74*GeV,220*GeV)){
         ((jet2.abseta() < 0.8) ? _h_1 : _h_2)->fill(beta, event.weight());
         ((jet2.abseta() < 0.8) ? _h_7 : _h_8)->fill(beta, event.weight());
         ((jet2.abseta() < 0.8) ? _h_13 : _h_14)->fill(beta, event.weight());
         ((jet2.abseta() < 0.8) ? _h_19 : _h_20)->fill(beta, event.weight());
      }
      if (inRange(jet1.pT(), 220*GeV,507*GeV)){
         ((jet2.abseta() < 0.8) ? _h_3 : _h_4)->fill(beta, event.weight());
         ((jet2.abseta() < 0.8) ? _h_9 : _h_10)->fill(beta, event.weight());
         ((jet2.abseta() < 0.8) ? _h_15 : _h_16)->fill(beta, event.weight());
         ((jet2.abseta() < 0.8) ? _h_21 : _h_22)->fill(beta, event.weight());
      }
      if (inRange(jet1.pT(), 507*GeV,2500*GeV)){
         ((jet2.abseta() < 0.8) ? _h_5 : _h_6)->fill(beta, event.weight());
         ((jet2.abseta() < 0.8) ? _h_11 : _h_12)->fill(beta, event.weight());
         ((jet2.abseta() < 0.8) ? _h_17 : _h_18)->fill(beta, event.weight());
         ((jet2.abseta() < 0.8) ? _h_23 : _h_24)->fill(beta, event.weight());
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
    Histo1DPtr _h_1;
    Histo1DPtr _h_2;
    Histo1DPtr _h_3;
    Histo1DPtr _h_4;
    Histo1DPtr _h_5;
    Histo1DPtr _h_6;
    Histo1DPtr _h_7;
    Histo1DPtr _h_8;
    Histo1DPtr _h_9;
    Histo1DPtr _h_10;
    Histo1DPtr _h_11;
    Histo1DPtr _h_12;
    Histo1DPtr _h_13;
    Histo1DPtr _h_14;
    Histo1DPtr _h_15;
    Histo1DPtr _h_16;
    Histo1DPtr _h_17;
    Histo1DPtr _h_18;
    Histo1DPtr _h_19;
    Histo1DPtr _h_20;
    Histo1DPtr _h_21;
    Histo1DPtr _h_22;
    Histo1DPtr _h_23;
    Histo1DPtr _h_24;
    //@}

  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(cc_ana);

}
