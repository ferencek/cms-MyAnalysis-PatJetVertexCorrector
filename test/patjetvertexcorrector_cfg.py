import FWCore.ParameterSet.Config as cms

process = cms.Process("JETFIX")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:RadionToHHTo4b_EventDisplay.root'
    )
)

process.selectedPatJetsCentered = cms.EDProducer('PatJetVertexCorrector',
    VertexSource = cms.InputTag('goodOfflinePrimaryVertices'),
    JetSource    = cms.InputTag('selectedPatJets')
)

process.selectedPatJetsCAPrunedSubPFCentered = cms.EDProducer('PatJetVertexCorrector',
    VertexSource = cms.InputTag('goodOfflinePrimaryVertices'),
    JetSource    = cms.InputTag('selectedPatJetsCAPrunedSubPF')
)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('RadionToHHTo4b_EventDisplay_CenteredJets.root'),
    outputCommands = cms.untracked.vstring('keep *')
)

## Path definition
process.p = cms.Path(
    process.selectedPatJetsCentered
    * process.selectedPatJetsCAPrunedSubPFCentered
)

## Define Endpath
process.outpath = cms.EndPath(process.out)
