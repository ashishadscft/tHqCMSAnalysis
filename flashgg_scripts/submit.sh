
INSTALLDIR=/afs/cern.ch/user/b/benitezj/output/tH/workspace/CMSSW_10_5_0/src

#fggRunJobs.py --load ${INSTALLDIR}/tHqCMSAnalysis/flashgg_scripts/higgs_2016.json -d higgs_2016 -n 300 -q workday --no-copy-proxy ${INSTALLDIR}/flashgg/Systematics/test/workspaceStd.py 
fggRunJobs.py --load ${INSTALLDIR}/tHqCMSAnalysis/flashgg_scripts/higgs_2016_v2.json -d higgs_2016_v2 -n 300 -q workday --no-copy-proxy ${INSTALLDIR}/flashgg/Systematics/test/workspaceStd.py 
#fggRunJobs.py  --load ${INSTALLDIR}/tHqCMSAnalysis/flashgg_scripts/thq_2016.json -d thq_2016  ${INSTALLDIR}/flashgg/Systematics/test/workspaceStd.py  -n 300  -q workday  --no-copy-proxy 
