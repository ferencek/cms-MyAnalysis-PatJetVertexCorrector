import FWCore.ParameterSet.Config as cms

process = cms.Process("JETFIX")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:top_eventdisplayB_196453_966_843094521.root'
    )
)

process.selectedPatJetsPFlowCentered = cms.EDProducer('PatJetVertexCorrector',
    VertexSource = cms.InputTag('goodOfflinePrimaryVertices'),
    JetSource    = cms.InputTag('selectedPatJetsPFlow')
)

process.selectedPatJetsCAHEPTopTagPFCentered = cms.EDProducer('PatJetVertexCorrector',
    VertexSource = cms.InputTag('goodOfflinePrimaryVertices'),
    JetSource    = cms.InputTag('selectedPatJetsCAHEPTopTagPF')
)

process.selectedPatJetsCAHEPTopTagSubjetsPFCentered = cms.EDProducer('PatJetVertexCorrector',
    VertexSource = cms.InputTag('goodOfflinePrimaryVertices'),
    JetSource    = cms.InputTag('selectedPatJetsCAHEPTopTagSubjetsPF')
)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('top_eventdisplayB_196453_966_843094521_CenteredJets.root'),
    outputCommands = cms.untracked.vstring('keep *')
)

## Path definition
process.p = cms.Path(
    process.selectedPatJetsPFlowCentered
    * process.selectedPatJetsCAHEPTopTagPFCentered
    * process.selectedPatJetsCAHEPTopTagSubjetsPFCentered
)

## Define Endpath
process.outpath = cms.EndPath(process.out)
