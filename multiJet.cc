#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/FastJets.hh"

//#include "Rivet/Projections/LeadingParticlesFinalState.hh"

#include <vector>
#include <string>
namespace Rivet {


  class multiJet : public Analysis {
  public:

    multiJet()
      : Analysis("multiJet")
    {    }
    float jr = 0.5; 
    void init() {
      const FastJets jets(FinalState(-10, 10, 0.0*GeV), FastJets::ANTIKT, jr);
      addProjection(jets, "Jets");
   
      std::vector<std::string> m_l = {"beta23","del_eta23","del_phi23", "del_r23", "jet3_pt_jet2_pt", "jet1_pt", "jet1_eta", "jet1_phi","jet2_pt", "jet2_eta", "jet2_phi","jet3_pt", "jet3_eta", "jet3_phi"};
      std::vector<std::vector<float>> bin_l = {{18,0,M_PI}, {30,-3.0,3.0}, {30,-3.0,3.0}, {20,0,2.0}, {10,0,1.0}, {30,0,2500}, {30,-3,3}, {30,-M_PI,M_PI}, {30,0,2500}, {30,-3,3}, {30,-M_PI,M_PI}, {30,0,2500}, {30,-3,3}, {30,-M_PI,M_PI}};
      std::vector<std::string> e_l = {"low", "medium", "high", "non"};
      std::vector<std::string> c_l = {"dr_pt3", "sdr_pt3", "ldr_pt3", "dr_lpt3", "dr_hpt3"};

      for(auto e : e_l){
        for(auto c : c_l){
          int size_m  = m_l.size();
          std::vector<Histo1DPtr> tmp;
          for(int i=0; i<size_m;i++){
            string hname = e+"_eta_high_pt_"+c+"_rivet_"+m_l.at(i);
            tmp.push_back(bookHisto1D(hname,(int)bin_l.at(i).at(0), bin_l.at(i).at(1), bin_l.at(i).at(2)));
          }
          h_l.push_back(tmp);
        }
      }

    }

    void fillHist(std::vector<Histo1DPtr>& a, std::vector<double>& b, double w) {
       int size_a = a.size();
       int size_b = b.size();
       if (size_a != size_b) return;
       for(int i=0; i<size_a;i++){
         a.at(i)->fill(b.at(i),w);
       }
 
    }

    void analyze(const Event& event) {
      const Jets& jets = applyProjection<FastJets>(event, "Jets").jetsByPt(30.0*GeV);
      if (jets.size() < 3) vetoEvent;
      const FourMomentum jet1 = jets[0].momentum();
      const FourMomentum jet2 = jets[1].momentum();
      const FourMomentum jet3 = jets[2].momentum();
      

      if (jet1.pT() < 500*GeV) vetoEvent;
      if (jet1.absrapidity() > 2.5 || jet2.absrapidity() > 2.5) vetoEvent;

      const FourMomentum diJet = jet1 + jet2;
      if (diJet.mass() < 220*GeV) vetoEvent;

      //double jet_pt_r = (jet2.pT() + jet3.pT())/jet1.pT();
      //if (!inRange(jet_pt_r, 0.9, 1.1)) vetoEvent;

      double jet3_pt_jet2_pt = jet3.pT()/jet2.pT();
      if (jet3_pt_jet2_pt > 0.9) vetoEvent;

      double del_phi12 = mapAngleMPiToPi(jet2.phi() - jet1.phi());
      if (abs(abs(del_phi12) - M_PI) > 1.0) vetoEvent;

      double del_phi23 = mapAngleMPiToPi(jet3.phi() -  jet2.phi());

      double del_eta23 = sign(jet2.rapidity())*(jet3.rapidity() - jet2.rapidity());
      const double del_r23 = add_quad(del_eta23, del_phi23);
      if (!inRange(del_r23, jr, 1.5)) vetoEvent;
      double beta23 = fabs(atan2(del_phi23, del_eta23));




      std::vector<double> results ={beta23, del_eta23, del_phi23, del_r23, jet3_pt_jet2_pt, jet1.pT(), jet1.rapidity(), jet1.phi(), jet2.pT(), jet2.rapidity(), jet2.phi(), jet3.pT(), jet3.rapidity(), jet3.phi()};
      double w = event.weight();
      if (inRange(jet1.pT(), 510*GeV,2500*GeV)){
         if (inRange(jet2.absrapidity(), 0.0, 0.8)){
           fillHist(h_l[0], results, w);
           if (inRange(del_r23, jr,1.0)) fillHist(h_l[1], results, w);
           if (inRange(del_r23, 1.0,1.5)) fillHist(h_l[2], results, w);
           if (inRange(jet3_pt_jet2_pt, 0.0, 0.3)) fillHist(h_l[3], results, w);
           if (inRange(jet3_pt_jet2_pt, 0.6, 0.9)) fillHist(h_l[4], results, w);
         }
         if (inRange(jet2.absrapidity(), 0.8, 1.5)){
           fillHist(h_l[5], results, w);
           if (inRange(del_r23, jr,1.0)) fillHist(h_l[6], results, w);
           if (inRange(del_r23, 1.0,1.5)) fillHist(h_l[7], results, w);
           if (inRange(jet3_pt_jet2_pt, 0.0, 0.3)) fillHist(h_l[8], results, w);
           if (inRange(jet3_pt_jet2_pt, 0.6, 0.9)) fillHist(h_l[9], results, w);
         }
         if (inRange(jet2.absrapidity(), 0.8, 2.5)){
           fillHist(h_l[10], results, w);
           if (inRange(del_r23, jr,1.0)) fillHist(h_l[11], results, w);
           if (inRange(del_r23, 1.0,1.5)) fillHist(h_l[12], results, w);
           if (inRange(jet3_pt_jet2_pt, 0.0, 0.3)) fillHist(h_l[13], results, w);
           if (inRange(jet3_pt_jet2_pt, 0.6, 0.9)) fillHist(h_l[14], results, w);
         }
         if (inRange(jet2.absrapidity(), 0, 2.5)){
           fillHist(h_l[15], results, w);
           if (inRange(del_r23, jr,1.0)) fillHist(h_l[16], results, w);
           if (inRange(del_r23, 1.0,1.5)) fillHist(h_l[17], results, w);
           if (inRange(jet3_pt_jet2_pt, 0.0, 0.3)) fillHist(h_l[18], results, w);
           if (inRange(jet3_pt_jet2_pt, 0.6, 0.9)) fillHist(h_l[19], results, w);
         }
      }
    }


    void finalize() {

    }

  private:

    std::vector<std::vector<Histo1DPtr>> h_l;

  };

  DECLARE_RIVET_PLUGIN(multiJet);

}
