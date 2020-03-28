// This is a rudimentary macro used to test the geometry with geantinos.
// To run it: root ploatGeantino.C
// 1: Takes as input the root files for a particular part.
// 2: Extracts the information of the tree and stores it in arrays.
// 3: The arrays are used to form a TGraph for each part.
// 4: Merges all the TGraphs in a single multigraph.  

void plotGeantino(){

// Function that fills arrays from branch
void readBranch(const char *name, Float_t vx[], Float_t vz[]);

int nEntries = 100000;

// Rock cavern
Float_t xRCavern[nEntries];
Float_t zRCavern[nEntries];
readBranch("rockCavern.root", xRCavern, zRCavern);
TGraph* grRockCavern = new TGraph(nEntries,xRCavern,zRCavern);
grRockCavern->SetTitle("Rock cavern");
grRockCavern->SetMarkerColor(20);
grRockCavern->SetMarkerSize(1);

// Rock walls
Float_t xRWalls[nEntries];
Float_t zRWalls[nEntries];
readBranch("rockWalls.root", xRWalls, zRWalls);
TGraph* grRockWalls = new TGraph(nEntries,xRWalls,zRWalls);
grRockWalls->SetTitle("Rock walls");
grRockWalls->SetMarkerColor(21);
grRockWalls->SetMarkerSize(1);

// Rock floor
Float_t xRFloor[nEntries];
Float_t zRFloor[nEntries];
readBranch("rockFloor.root", xRFloor, zRFloor);
TGraph* grRockFloor = new TGraph(nEntries,xRFloor,zRFloor);
grRockFloor->SetTitle("Rock floor");
grRockFloor->SetMarkerColor(22);
grRockFloor->SetMarkerSize(1);

// Multigraph
TMultiGraph  *lab  = new TMultiGraph();
lab->SetTitle("Rock components; x(mm); z(mm)");
lab->Add(grRockWalls);
lab->Add(grRockCavern);
lab->Add(grRockFloor);
lab->Draw("AP");
}
// ----------------------------------------------------------------------------------

// Definition of the read function
void readBranch(const char *name, Float_t vx[], Float_t vz[]){

	// Open file and tree
	TFile *file = new TFile(name);
	TDirectoryFile *pDir = (TDirectoryFile *) file->Get("events");
	TTree *pTree = (TTree *) pDir->Get("events");
	int n = pTree->GetEntries();

	// Set branches and variables
	TBranch *branchx = 0;
	TBranch *branchz = 0;
	Float_t x=0.0, z = 0.0;

	pTree->SetBranchAddress("xp_pri",&x,&branchx);
	pTree->SetBranchAddress("zp_pri",&z,&branchz);

	// Fill arrays with the values in branches
	for(int i=0;i<n;i++){
		branchx->GetEntry(i);
		branchz->GetEntry(i);
		vx[i] = x;
		vz[i] = z;
	}
}
