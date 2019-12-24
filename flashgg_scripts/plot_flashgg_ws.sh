OUTDIR=/afs/cern.ch/user/b/benitezj/www/SonoraTHQ/workspaces/Era2016_RR-17Jul2018_v2
INDIR=/afs/cern.ch/user/b/benitezj/output/tH/workspace/CMSSW_10_5_0/src/flashgg/Systematics/test

for SAMPLE in Data GluGluHToGG_M125 VBFHToGG_M125 ttHJetToGG_M125 VHToGG_M125 bbHToGG ZH  THW  THQ; do
root -b -q $CMSSW_BASE/src/tHqCMSAnalysis/flashgg_scripts/plot_flashgg_ws.C\(\"${INDIR}/${SAMPLE}.root\",\"${SAMPLE}\",\"${OUTDIR}\"\)
done
