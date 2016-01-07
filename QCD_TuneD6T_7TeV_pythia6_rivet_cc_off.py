import FWCore.ParameterSet.Config as cms
from Configuration.Generator.PythiaUED6TSettings_cfi import *
process = cms.Process('GEN')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
#process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
#process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

import sys
max_num = int(sys.argv[2])
f_num = int(sys.argv[3])
min_pt = int(sys.argv[4])
max_pt = int(sys.argv[5])

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(max_num)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('\\$Revision: 1.1 $'),
    annotation = cms.untracked.string('PYTHIA6: QCD dijet production, pThat = %d .. %d GeV, TuneZ2'%(min_pt, max_pt)),
    name = cms.untracked.string('\\$Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/GenProduction/python/EightTeV/Attic/QCD_Pt_15to3000_TuneZ2_Flat_8TeV_pythia6_cff.py,v $')
)

# Output definition
process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('QCD_Pt_%dto%d_TuneZ2_13TeV_pythia6_GEN_%03d.root'%(min_pt, max_pt, f_num)),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-RAW')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)
# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:mc', '')


process.generator = cms.EDFilter('Pythia6GeneratorFilter',
	comEnergy = cms.double(7000.0),
	crossSection = cms.untracked.double(0),
	filterEfficiency = cms.untracked.double(1),
	maxEventsToPrint = cms.untracked.int32(0),
	pythiaHepMCVerbosity = cms.untracked.bool(False),
	pythiaPylistVerbosity = cms.untracked.int32(0),

	PythiaParameters = cms.PSet(
		pythiaUESettingsBlock,
		processParameters = cms.vstring(
			'MSEL = 1        ! QCD hight pT processes',
			'CKIN(3) = %d    ! minimum pt hat for hard interactions'%min_pt,
			'CKIN(4) = %d  ! maximum pt hat for hard interactions'%max_pt,
			#'MSTP(142) = 2   ! Turns on the PYWEVT Pt reweighting routine',
            'MSTP(67) = 0',
            'MSTJ(50) = 0',
            #'MSTJ(42) = 1',
            #'MSTJ(46) = 0',
            #'MSTP(62) = 1'

		),

		#CSAParameters = cms.vstring(
		#	'CSAMODE = 7     ! towards a flat QCD spectrum',
		#	'PTPOWER = 4.5   ! reweighting of the pt spectrum',
		#),
		parameterSets = cms.vstring(
			'pythiaUESettings',
			'processParameters',
			#'CSAParameters',
		)
	)
)


# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.endjob_step,process.RAWSIMoutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 

process.source.firstRun = cms.untracked.uint32(f_num)
process.RandomNumberGeneratorService.generator.initialSeed = f_num

from Configuration.GenProduction.rivet_customize import customise

#call to customisation function customise imported from Configuration.GenProduction.rivet_customize
process = customise(process)

# End of customisation functions
process.rivetAnalyzer.AnalysisNames = cms.vstring('cc_ana')
process.rivetAnalyzer.OutputFile = cms.string('QCD_Pt_%dto%d_TuneD6T_7TeV_pythia6_rivet_cc_off_%03d.yoda'%(min_pt, max_pt, f_num))
