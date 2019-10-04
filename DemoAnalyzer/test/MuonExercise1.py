import FWCore.ParameterSet.Config as cms
import os, sys, glob

process = cms.Process("MuonExercise1")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 500
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    limit = cms.untracked.int32(0)
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False),
SkipEvent = cms.untracked.vstring('ProductNotFound'))

#process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring('root://cmseos.fnal.gov///store/user/hats/2017/muon/dymm.root'))


#sample = 'THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1'
#sample = 'TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8'
#inputlist = cms.untracked.vstring('file:/eos/user/b/benitezj/RunIISummer16MiniAODv3/' + sample +'/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM/EE7BE19D-31EB-E811-AC13-44A84225D36F.root')
#fileNames = cms.untracked.vstring('file:/eos/user/b/benitezj/RunIISummer16MiniAODv3/' + sample +'/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM/948EDA1B-AD35-E911-A027-0001010008EE.root')


inputlist = cms.untracked.vstring()
#inputlist = cms.untracked.vstring('file:/eos/user/b/benitezj/RunIISummer16MiniAODv3/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM/EE7BE19D-31EB-E811-AC13-44A84225D36F.root')
#inputlist = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/mc/RunIISummer16MiniAODv3/THQ_Hincl_13TeV-madgraph-pythia8_TuneCUETP8M1/MINIAODSIM/PUMoriond17_94X_mcRun2_asymptotic_v3-v2/120000/F8AF947C-2AEB-E811-BE18-246E96D14B94.root')


if len(inputlist) == 0 :
    input = os.getenv('INPUT')
    if input == None : sys.exit('invalid INPUTDIR')
    #print 'reading from inputdir: ', input
    #for f in glob.glob(input+'/*.root'):
    files=input.split(" ")
    for i in range(len(files)) :
        if ".root" in files[i] :
            #file='file:'+files[i]
            file=files[i]
            print 'adding: '+file
            inputlist.extend(cms.vstring(file))
     

process.source = cms.Source("PoolSource", 
                            fileNames = inputlist
)

process.demo = cms.EDAnalyzer('MuonExercise1')


process.TFileService = cms.Service("TFileService",
          fileName = cms.string('output.root')
)

process.p = cms.Path(process.demo)
