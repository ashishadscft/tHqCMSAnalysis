INSTALLDIR=/afs/cern.ch/user/b/benitezj/output/tH/workspace/CMSSW_10_5_0/src/flashgg/Systematics/test


#INDIR=test_legacy_2016
#hadd_workspaces Data.root ${INSTALLDIR}/${INDIR}/output_DoubleEG_*.root
#
INDIR=higgs_2016
#hadd_workspaces GluGluHToGG_M125.root ${INSTALLDIR}/${INDIR}/output_GluGluHToGG_M125*.root
hadd_workspaces VBFHToGG_M125.root ${INSTALLDIR}/${INDIR}/output_VBFHToGG_M125*.root
#hadd_workspaces ttHJetToGG_M125.root ${INSTALLDIR}/${INDIR}/output_ttHJetToGG_M125*.root
#hadd_workspaces VHToGG_M125.root ${INSTALLDIR}/${INDIR}/output_VHToGG_M125*.root
hadd_workspaces bbHToGG.root ${INSTALLDIR}/${INDIR}/output_bbHToGG_M-125*.root
hadd_workspaces ZH.root ${INSTALLDIR}/${INDIR}/output_ZH_HToGG_ZToAll_M125*.root
hadd_workspaces THW.root ${INSTALLDIR}/${INDIR}/output_THW_ctcvcp_HToGG*.root
#
#INDIR=thq_2016
#hadd_workspaces THQ.root ${INSTALLDIR}/${INDIR}/output_THQ_ctcvcp_HToGG_M125*.root

