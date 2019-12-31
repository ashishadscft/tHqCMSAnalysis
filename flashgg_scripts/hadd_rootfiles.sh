INSTALLDIR=/afs/cern.ch/user/b/benitezj/output/tH/workspace/CMSSW_10_5_0/src

#YEAR=2016
#ERA=Era2016_RR-17Jul2018_v2

#YEAR=2017
#ERA=Era2017_RR-31Mar2018_v2

YEAR=2018
ERA=Era2018_RR-17Sep2018_v2


#SUBDIR=thq_${YEAR}
#hadd_workspaces ${ERA}/thq_.root ${INSTALLDIR}/${SUBDIR}/output_THQ_ctcvcp_HToGG_M125*.root

SUBDIR=higgs_${YEAR}
hadd_workspaces ${ERA}/ggh_.root ${INSTALLDIR}/${SUBDIR}/output_GluGluHToGG_M125*.root
#hadd_workspaces ${ERA}/tth_.root ${INSTALLDIR}/${SUBDIR}/output_ttHJetToGG_M125*.root
#hadd_workspaces ${ERA}/vh.root ${INSTALLDIR}/${SUBDIR}/output_VHToGG_M125*.root
hadd_workspaces ${ERA}/bbh_.root ${INSTALLDIR}/${SUBDIR}/output_bbHToGG_M-125*.root
#hadd_workspaces ${ERA}/vbf_.root ${INSTALLDIR}/${SUBDIR}/output_VBFHToGG_M125*.root
#hadd_workspaces ${ERA}/thw_.root ${INSTALLDIR}/${SUBDIR}/output_THW_ctcvcp_HToGG*.root

#SUBDIR=data_${YEAR}
#hadd_workspaces ${ERA}/Data.root ${INSTALLDIR}/${SUBDIR}/output_*.root
#hadd_workspaces ${ERA}/Data_Run${YEAR}A.root ${INSTALLDIR}/${SUBDIR}/output_*Run${YEAR}A*.root
#hadd_workspaces ${ERA}/Data_Run${YEAR}B.root ${INSTALLDIR}/${SUBDIR}/output_*Run${YEAR}B*.root
#hadd_workspaces ${ERA}/Data_Run${YEAR}C.root ${INSTALLDIR}/${SUBDIR}/output_*Run${YEAR}C*.root
#hadd_workspaces ${ERA}/Data_Run${YEAR}D.root ${INSTALLDIR}/${SUBDIR}/output_*Run${YEAR}D*.root



