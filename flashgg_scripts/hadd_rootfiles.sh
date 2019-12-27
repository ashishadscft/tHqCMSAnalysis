#INSTALLDIR=/afs/cern.ch/user/b/benitezj/output/tH/workspace/CMSSW_10_5_0/src/flashgg/Systematics/test
INSTALLDIR=/afs/cern.ch/user/b/benitezj/output/tH/workspace/CMSSW_10_5_0/src


SUBDIR=thq_2016
hadd_workspaces thq_.root ${INSTALLDIR}/${SUBDIR}/output_THQ_ctcvcp_HToGG_M125*.root

SUBDIR=higgs_2016
hadd_workspaces ggh_.root ${INSTALLDIR}/${SUBDIR}/output_GluGluHToGG_M125*.root
hadd_workspaces tth_.root ${INSTALLDIR}/${SUBDIR}/output_ttHJetToGG_M125*.root
hadd_workspaces vh.root ${INSTALLDIR}/${SUBDIR}/output_VHToGG_M125*.root
hadd_workspaces bbh_.root ${INSTALLDIR}/${SUBDIR}/output_bbHToGG_M-125*.root

SUBDIR=higgs_2016_v2
hadd_workspaces vbf_.root ${INSTALLDIR}/${SUBDIR}/output_VBFHToGG_M125*.root
hadd_workspaces thw_.root ${INSTALLDIR}/${SUBDIR}/output_THW_ctcvcp_HToGG*.root

SUBDIR=test_legacy_2016
hadd_workspaces Data.root ${INSTALLDIR}/${SUBDIR}/output_DoubleEG_*.root
