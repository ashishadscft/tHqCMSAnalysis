import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/eos/user/b/benitezj/RunIISummer16MiniAODv3//THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM/EE7BE19D-31EB-E811-AC13-44A84225D36F.root'
    )
)

process.demo = cms.EDAnalyzer('DemoAnalyzer'
)


process.p = cms.Path(process.demo)
