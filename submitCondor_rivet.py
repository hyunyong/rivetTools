#!/usr/bin/env python
import os, sys, time
pt_min = int(sys.argv[1])
pt_max = int(sys.argv[2])

def submiter(exe_l):
  print "\nSubmiter will submit"
  print "="*10
  print exe_l
  print "="*10
  os.system(exe_l)
  time.sleep(3)
  print "\n"*3

teve = 5000000*3
cfg_l = ["QCD_TuneCUETP8M1_13TeV_pythia8_rivet.py",
         "QCD_TuneCUETP8M1_13TeV_pythia8_rivet_cc_off.py"]
         #"QCD_TuneCUETP8M1_13TeV_pythia8_rivet_cc_isr_off.py",
         #"QCD_TuneCUETP8M1_13TeV_pythia8_rivet_cc_fsr_off.py",
         #"QCD_TuneCUETP8M1_13TeV_pythia8_rivet_cc_tgp_off.py",
         #"QCD_TuneCUETP8M1_13TeV_pythia8_rivet_cc_sgp_off.py"]
tag_l = ["cc_on", "cc_off"]#, "isr_off", "fsr_off", "tgp_off", "sgp_off"]
"""
cfg_l = ["QCD_TuneD6T_13TeV_pythia6_rivet_cc_on.py",
         "QCD_TuneD6T_13TeV_pythia6_rivet_cc_off.py",
         "QCD_TuneD6T_13TeV_pythia6_rivet_cc_isr_off.py",
         "QCD_TuneD6T_13TeV_pythia6_rivet_cc_fsr_off.py"]
tag_l = ["cc_on", "cc_off", "isr_off", "fsr_off"]
"""
if len(cfg_l) != len(tag_l):
  print "Input file is worng!"
  sys.exit()

for x in xrange(len(cfg_l)):
  exe_l = "./runCondor_rivet %s %d %d %d %s"%(cfg_l[x], teve, pt_min, pt_max, tag_l[x])
  submiter(exe_l)

