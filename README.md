# rivetTools

```bash
scram p -n rivet CMSSW CMSSW_7_2_0_pre3
cd rivet/src
cmsenv
git cms-addpkg GeneratorInterface/RivetInterface
git clone git@github.com:hyunyong/rivetTools.git
wget -P Configuration/GenProduction/python/ https://raw.githubusercontent.com/cms-sw/genproductions/master/python/rivet_customize.py 
cp rivetTools/cc_ana.cc GeneratorInterface/RivetInterface/src
scram b -j 8
```
## runGen.py
```
python runGen.py sample.py tot_num num_per_job min_pt_hat max_pt_hat
e.g.)
python runGen.py QCD_Tune4C_8TeV_pythia8_rivet.py 1000 10 100 2500
```
