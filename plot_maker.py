from ROOT import *
from os import mkdir, chdir
import copy, math
import CMS_lumi, tdrstyle

#from cc_ana_tool import *
gROOT.SetBatch()
tdrstyle.setTDRStyle()

#CMS_lumi.writeExtraText = 1
#CMS_lumi.extraText = "Preliminary"
#CMS_lumi.lumi_sqrtS = "8 TeV"

iPos = 11
iPeriod = 2

def comp_plot(h_list, color, marker, title,root_name, tag):
  pad = TCanvas("c1", "c1", 600, 800)
  set_log = 0
  tmp = h_list[0].GetName().split("_")
  if tmp[-1] =="pt" or tmp[-1] == "met" or tmp[-1] == "mass":
    set_log = 1
  if tmp[-1] == "weight":
    return 0
  pad.cd()
  #set_log = 0
  le = TLegend(0.55, 0.75, 0.99, 0.87)
  le.SetFillStyle(0)
  le.SetFillColor(kWhite)
  le.SetBorderSize(0)
  le.SetHeader(root_name[0])
  padt = TPad("t", "t", 0.0, 1.0, 1.0, 0.35)
  padb = TPad("b", "b", 0.0, 0.35, 1.0, 0.0)
  margin_s = 0.005
  margin_b = 2.0
  padt.Draw()
  padt.cd()
  padt.SetGrid()
  padt.SetLogy(set_log)
  padt.SetBottomMargin(0.01)
  padt.SetTopMargin(0.18)

  tmp_h =[]
  #for x in xrange(h_list[0].GetNbinsX()):
  #  er1 = h_list[0].GetBinError(x+1)
  #  er2 = math.sqrt(h_list[0].GetBinContent(x+1))
  #  print er1, er2
  for x in h_list:
    for bin in xrange(x.GetNbinsX()):
      er = math.sqrt(x.GetBinContent(bin+1))
      x.SetBinError(bin+1,er)
    x.Sumw2()
    tmp_h.append(copy.deepcopy(x.DrawNormalized()))
  print title

  chi2_mc1 = 0.0
  chi2_mc2 = 0.0
  ent = 0
  for x in xrange(tmp_h[0].GetNbinsX()):
    dv = tmp_h[0].GetBinContent(x+1)
    de = tmp_h[0].GetBinError(x+1)
    m1v = tmp_h[1].GetBinContent(x+1)
    m1e = tmp_h[1].GetBinError(x+1)
    m2v = tmp_h[2].GetBinContent(x+1)
    m2e = tmp_h[2].GetBinError(x+1)
    if dv == 0 or m1v ==0: continue
    chi2_mc1 += ((dv - m1v)**2)/(de**2 + m1e**2)
    chi2_mc2 += ((dv - m2v)**2)/(de**2 + m2e**2)
    ent += 1
  print "my chi2 mc1 : %2.2f"%(chi2_mc1/ent)
  print "my chi2 mc2 : %2.2f"%(chi2_mc2/ent)
  #print "ktest : ", tmp_h[0].KolmogorovTest(tmp_h[1],"N")
  #print "chi2 mc1 : ", tmp_h[0].Chi2Test(tmp_h[1],"NORM, CHI2")
  #print "chi2/ndf mc1 : ", tmp_h[0].Chi2Test(tmp_h[1],"NORM, CHI2/NDF")
  #print "chi2 mc2 : ", tmp_h[0].Chi2Test(tmp_h[2],"NORM, CHI2")
  #print "chi2/ndf mc2 : ", tmp_h[0].Chi2Test(tmp_h[2],"NORM, CHI2/NDF")

  t_max = 0.0
  t_min = 1.0
  ent_l = []
  for i, x in enumerate(tmp_h):
    x.SetLineColor(color[i])
    x.SetLineWidth(2)
    x.SetMarkerStyle(marker[i])
    x.SetMarkerSize(0.5)
    x.SetMarkerColor(color[i])
    tmp_max = x.GetMaximum()
    tmp_min = x.GetMinimum()
    if t_max < tmp_max:
      t_max = tmp_max
  for i, h in enumerate(tmp_h):
    le.AddEntry(h, root_name[i+1])
    if i == 0:
      if set_log == 1:
        h.SetMinimum(0.00001)
      else:
        #h.SetMinimum(0.021)
        if tmp_min < 0.0:
          h.SetMinimum(tmp_min*0.7)
        else:
          h.SetMinimum(0.001)
      #h.SetMaximum(0.089)
      h.SetMaximum(t_max*1.5)
      if set_log == 1:
        h.SetMaximum(t_max*1000)
      h.SetStats(0)
      h.GetYaxis().SetTitleOffset(1.0)
      h.GetYaxis().SetTitleSize(0.05)
      h.GetYaxis().SetLabelSize(0.035)
      #h.GetYaxis().SetLabelSize(0.06)
      h.GetXaxis().SetLabelOffset(1.7)
      h.GetXaxis().SetTitleOffset(1.7)
      h.GetXaxis().CenterTitle()
      h.GetYaxis().CenterTitle()
      h.Draw()
    else:
      h.Draw("same")
  pad.cd()
  padb.Draw()
  ###div. plot
  padb.cd()
  padb.SetGrid()
  padb.SetTopMargin(0.018)
  padb.SetBottomMargin(0.3)
  div_h = []
  for x in tmp_h:
    tmp_0 = tmp_h[0].Clone()
    tmp_h1 = x.Clone()
    tmp_h1.Divide(tmp_0)
    print tmp_h1.GetBinError(3)
    div_h.append(tmp_h1)
  le2 = TLegend(0.7, 0.15, 0.9, 0.25)
  le2.SetFillStyle(0)
  le2.SetBorderSize(0)
  for i, h in enumerate(div_h):
    h.SetLineWidth(2)
    h.SetMarkerSize(0.5)
    h.SetLineColor(color[i])
    h.SetMarkerStyle(marker[i])
    h.SetMarkerColor(color[i])
    #h.SetMarkerStyle(24)
    #h.SetMarkerColor(4)
    #h.SetLineColor(4)
    if i == 0:
      continue
    if i == 1:
      le2.AddEntry(h, root_name[i])
      h.SetStats(0)
      h.SetTitle("")
      h.SetMaximum(1.51)
      h.SetMinimum(0.49)
      h.GetYaxis().SetTitleSize(0.1)
      h.GetYaxis().SetTitleOffset(0.6)
      h.GetYaxis().SetLabelSize(0.07)
      h.GetXaxis().SetTitleSize(0.1)
      h.GetXaxis().SetLabelSize(0.07)
      h.GetXaxis().CenterTitle()
      h.GetYaxis().CenterTitle()
      h.Draw()
    else:
      le2.AddEntry(h, root_name[i])
      h.Draw("same")
  pad.cd()
  le.Draw()
  #le2.Draw()
  p = h_list[0].GetName()
  store_n = tag+"_"+p
  lum_l = ["2.13 pb^{-1}", "55.92 pb^{-1}", "19.79 fb^{-1}"]
  if title.split()[2] == "low": lumi_s = lum_l[0]
  if title.split()[2] == "medium": lumi_s = lum_l[1]
  if title.split()[2] == "high": lumi_s = lum_l[2]
  #CMS_lumi.lumi_8TeV = "L_{int} = %s"%lumi_s
  #CMS_lumi.CMS_lumi(pad, iPeriod, iPos)
  latex = TLatex()
  latex.DrawLatex(0.1,0.93,title)
  pad.SaveAs(store_n+".png")
  pad.SaveAs(store_n+".eps")
  out_txt = open(store_n+".txt","w")
  for x in xrange(div_h[1].GetNbinsX()):
    out_txt.write("%02d bin value, error, statistics : %3.4f, %3.4f, %3.4f\n"%(x+1, div_h[1].GetBinContent(x+1), div_h[1].GetBinError(x+1), div_h[0].GetBinError(x+1)))
  out_txt.close()
  out_txt2 = open(store_n+"_chi2.txt","w")
  out_txt2.write("chi2 mc1 : %2.2f\n"%(chi2_mc1/ent))
  out_txt2.write("chi2 mc2 : %2.2f\n"%(chi2_mc2/ent))
  out_txt2.close()
  del(pad)

