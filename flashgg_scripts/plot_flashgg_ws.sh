OUTDIR=/afs/cern.ch/user/b/benitezj/www/SonoraTHQ/workspaces/Era2016_RR-17Jul2018_v2
INDIR=/afs/cern.ch/user/b/benitezj/output/tH/workspace/CMSSW_10_5_0/src

rm -f $OUTDIR/*.gif
rm -f $OUTDIR/*.txt



##fit for each sample and category
for SAMPLE in Data ggh_ vbf_ tth_ vh bbh_ thw_ thq_; do
#for SAMPLE in Data; do
root -b -q $CMSSW_BASE/src/tHqCMSAnalysis/flashgg_scripts/plot_flashgg_ws.C\(\"${INDIR}/${SAMPLE}.root\",\"${SAMPLE}\",\"${OUTDIR}\"\)
done

##fit to the sum of the samples
root -b -q $CMSSW_BASE/src/tHqCMSAnalysis/flashgg_scripts/fit_higgs.C\(\"${INDIR}\",\"${OUTDIR}\"\)
