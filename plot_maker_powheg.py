from ROOT import *
from os import mkdir, chdir, system
import copy
from plot_maker import *
gROOT.SetBatch()


if __name__ == '__main__':
  #root_f_list = ["JetHT_win14.root", "JetMon_win14.root", "QCD_HT_TuneZ2star_8TeV-madgraph-pythia6_hist.root", "QCD_Pt-15to3000_TuneEE3C_Flat_8TeV_herwigpp_hist.root", "QCD_Pt-15to3000_TuneZ2star_Flat_8TeV_pythia6_hist.root"]
  #root_f_list = ["JetHT_win14.root", "JetMon_win14.root", "QCD_HT_TuneZ2star_8TeV-madgraph-pythia6_hist.root"]
  root_f_list = ["JetHT_RD.root", "QCD_Pt_TuneCUETP8M1_13TeV_pythia8_v7-4-2_RunIISpring15DR74-Asympt50ns_MCRUN2_hist.root", "QCD_HT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_hist.root"]
  root_f_list = ["Unfold_hist_PYTHIA8.root", "QCD_powheg_ct10_pythia8_cuetp8m1_13TeV_ps_hist.root", "QCD_powheg_ct10_pythia8_cuetp8m1_13TeV_nps_hist.root"]
  tr_list = []
  for x in root_f_list:
    tr_list.append(TFile(x))
  chdir("./powheg")
  eta_l = ["low", "medium", "high"]
  pt_l = ["high"]
  cut_l = ["_", "_sdr_", "_ldr_", "_lpt_", "_hpt_"]
  g_l = ["beta", "del_eta", "del_phi", "del_r", "jet3_pt_jet2_pt"]
  t_l = ["#beta_{23}", "#Delta#eta_{23}", "#Delta#phi_{23}", "#DeltaR_{23}", "Jet_{3} p_{T}/Jet_{2} p_{T}"]

  color = [1,2,3,4,6,7,8]
  marker = [20,21,22,23,33]
  for i,p in enumerate(g_l):
    for j,e in enumerate(eta_l):
      for k,c in enumerate(cut_l):
        h_list = []
        data_s = ""
        if c == "_":
          data_s = e+"_eta_high_pt_dr_non_rd_"+p
        if c == "_sdr_":
          data_s = e+"_eta_high_pt_sdr_non_rd_"+p
        if c == "_ldr_":
          data_s = e+"_eta_high_pt_ldr_non_rd_"+p
        if c == "_lpt_":
          data_s = e+"_eta_high_pt_dr_lpt3_rd_"+p
        if c == "_hpt_":
          data_s = e+"_eta_high_pt_dr_hpt3_rd_"+p
        if p != "jet3_pt_jet2_pt":
          data_s += "23"
        data = copy.deepcopy(tr_list[0].Get(data_s))
        if p != "jet3_pt_jet2_pt":
          mc_s = "h_"+e+"_eta_high_pt"+c+p
        else:
          mc_s = "h_"+e+"_eta_high_pt"+c+"pt3_pt2"
    
        mc1 = copy.deepcopy(tr_list[1].Get(mc_s))
        mc2 = copy.deepcopy(tr_list[2].Get(mc_s))
        title = e+" #eta  high p_{T} "+t_l[i]
        if c == "_sdr_": title += " (small #Delta R)"
        if c == "_ldr_": title += " (large #Delta R)"
        if c == "_lpt_": title += " (low p_{T3})"
        if c == "_hpt_": title += " (high p_{T3})"
        h_list.append(data)
        h_list.append(mc1)
        h_list.append(mc2)
        h_list[1].SetXTitle(t_l[i])
        h_list[0].SetYTitle("Normalized Yield")
        h_list[1].SetYTitle("MC / Data")
        comp_plot(h_list,color,marker,title,["CMS #sqrt{s} = 13 TeV","Unfolded data", "POWHEG + PYTHIA8", "POWHEG + PYTHIA8 without PS"],"POWHEG")
  #system("runEpsPdf .")
