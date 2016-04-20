#!/usr/bin/env python

import ROOT, yoda, array, numpy
ROOT.gROOT.SetBatch()
 
class Histo1D:
  title = ""
  numOfBins = 0
  bins = []
  def __init__(self, h1):
    self.bins = h1.bins
    self.title = h1.path.split("/")[2]
    self.numOfBins = h1.numBins
  def getBinContent(self, index):
    return self.bins[index].effNumEntries 
  def makeTH1F(self):
    bin_l = [self.bins[0].xMin]
    for x in self.bins:
      bin_l.append(x.xMax)
    th1 = ROOT.TH1F(self.title, self.title, self.numOfBins, array.array('d',bin_l))
    for x in self.bins:
      th1.Fill(x.xMid, x.effNumEntries)
    return th1


class Histo2D:
  title = ""
  numOfBins = 0
  bins = []
  x_min = 0.0
  x_max = 0.0
  y_min = 0.0
  y_max = 0.0
  dx = 0.0
  dy = 0.0
  nx = 0.0
  ny = 0.0
  def __init__(self, h2):
    self.bins = h2.bins
    self.title = h2.path.split("/")[2]
    self.numOfBins = h2.numBins
    self.x_min = h2.bins[0].xMin
    self.y_min = h2.bins[0].yMin
    self.x_max = h2.bins[-1].xMax
    self.y_max = h2.bins[-1].yMax
    self.nx = h2.numBinsX
    self.ny = h2.numBinsY
  def getBinContent(self, index):
    return self.bins[index].effNumEntries

  def makeTH2D(self):
    th2 = ROOT.TH2D(self.title, self.title, self.nx, self.x_min, self.x_max, self.ny, self.y_min, self.y_max)
    for x in self.bins:
      th2.Fill(x.xMid, x.yMid, x.effNumEntries)
    return th2

class Profile1D:
  title = ""
  numOfBins = 0
  bins = []
  def __init__(self, p1):
    self.bins = p1.bins
    self.title = p1.path.split("/")[2]
    self.numOfBins = p1.numBins
  def getBinContent(self, index):
    return self.bins[index].mean
  def makeTProfile(self):
    bin_l = [self.bins[0].xMin]
    for x in self.bins:
      bin_l.append(x.xMax)
    #bin_l = [0,100,200,300,400,500,600,700,800,1000,1500]
    tp1 = ROOT.TProfile(self.title, self.title, self.numOfBins, array.array('d',bin_l))
    #tp1 = ROOT.TProfile(self.title, self.title, len(bin_l)-1, array.array('d',bin_l))
    for x in self.bins:
      bv = 0.0
      try:
        bv = x.mean
      except:
        bv = 0.0
      tp1.Fill(x.xMid, bv, x.effNumEntries)
    return tp1

if __name__ =='__main__':
  
  import os, sys, ROOT
  ROOT.gROOT.SetBatch()
  in_dir = sys.argv[1]
  in_file = [x for x in os.listdir(in_dir) if x.endswith(".yoda")]
  print in_file
  for f in in_file:
    tmp = yoda.read(f)
    key_l = tmp.keys()
    hist_l = []
    for x in key_l:
      tmp_h = tmp.get(x)
      if tmp_h.type == "Histo1D":
        tmp_h1 = Histo1D(tmp_h)
        hist_l.append(tmp_h1.makeTH1F())
      if tmp_h.type == "Histo2D":
        tmp_h2 = Histo2D(tmp_h)
        hist_l.append(tmp_h2.makeTH2D())
      if tmp_h.type == "Profile1D":
        tmp_p1 = Profile1D(tmp_h)
        hist_l.append(tmp_p1.makeTProfile())

    out_f = ROOT.TFile(f.replace(".yoda", ".root").split("/")[-1], "RECREATE")
    out_f.cd()
    for x in hist_l:
      x.Write()
    out_f.Close()
