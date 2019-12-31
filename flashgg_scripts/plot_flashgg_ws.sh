
#ERA=Era2016_RR-17Jul2018_v2
#ERA=Era2017_RR-31Mar2018_v2
ERA=Era2018_RR-17Sep2018_v2


INDIR=/afs/cern.ch/user/b/benitezj/output/tH/workspace/CMSSW_10_5_0/src/${ERA}
OUTDIR=/afs/cern.ch/user/b/benitezj/www/SonoraTHQ/workspaces/${ERA}

mkdir $OUTDIR
rm -f $OUTDIR/*.gif
rm -f $OUTDIR/*.txt
rm -f $OUTDIR/*.tex
rm -f $OUTDIR/*.root
rm -f $OUTDIR/*.pdf

##fit for each sample and category
for SAMPLE in Data ggh_ vbf_ tth_ vh bbh_ thw_ thq_; do
#for SAMPLE in Data; do
root -b -q $CMSSW_BASE/src/tHqCMSAnalysis/flashgg_scripts/plot_flashgg_ws.C\(\"${INDIR}\",\"${SAMPLE}\",\"${OUTDIR}\"\)
done

##fit to the sum of the samples
root -b -q $CMSSW_BASE/src/tHqCMSAnalysis/flashgg_scripts/fit_higgs.C\(\"${INDIR}\",\"${OUTDIR}\"\)


##make the table
root -b -q $CMSSW_BASE/src/tHqCMSAnalysis/flashgg_scripts/make_table.C\(\"${OUTDIR}\"\)
