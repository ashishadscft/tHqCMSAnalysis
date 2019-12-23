Codes created by Hiram Ernesto Damian

This list of codes made in ROOT is for the analysis of data by fitting a statistical model with data.
The codes require the roofit package of ROOT in order to work. See the ROOT webpage for more information.


//////////////////////
make_workspace.C
//////////////////////
This algorithm creates a workspace. Here the model is created. Also the data to fit is loaded.
The programs requires to load the MC data file that will be the model. The file is plots-thq-2lss-kinMVA.root
The product will be _combined_kinMVA_model.root that contains the model.
Further instructions are in the code.

//////////////////////
fit_workspace.C
/////////////////////
The code for fitting the statistical model and data. The fitting is also plotted. Further instructions are in the code.

/////////////////////
scanLikelihood.C
/////////////////////
Creates a likelihood scan from the file _combined_kinMVA_model.root created in make_workspace.C. Also plots the scan.

//////////////////////
limite.C
///////////////////////
By using the file _combined_kinMVA_model.root created from make_workspace.C, calculates an upper limit for the model.
Further instructions are the code.
