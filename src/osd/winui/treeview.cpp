// license:BSD-3-Clause
// For licensing and usage information, read docs/release/winui_license.txt

#include "winui.h"

/***************************************************************************
    private variables
 ***************************************************************************/

/* this has an entry for every folder eventually in the UI, including subfolders */
static TREEFOLDER **treeFolders = 0;
static UINT numFolders  = 0;        		/* Number of folder in the folder array */
static UINT next_folder_id = MAX_FOLDERS;
static UINT folderArrayLength = 0;  		/* Size of the folder array */
static LPTREEFOLDER lpCurrentFolder = 0;    /* Currently selected folder */
static UINT nCurrentFolder = 0;     		/* Current folder ID */
static WNDPROC g_lpTreeWndProc = 0;   		/* for subclassing the TreeView */
static HIMAGELIST hTreeSmall = 0;         	/* TreeView Image list of icons */
/* this only has an entry for each TOP LEVEL extra folder + SubFolders*/
LPEXFOLDERDATA ExtraFolderData[MAX_EXTRA_FOLDERS * MAX_EXTRA_SUBFOLDERS];
static int numExtraFolders = 0;
static int numExtraIcons = 0;
static char *ExtraFolderIcons[MAX_EXTRA_FOLDERS] = {};
// built in folders and filters
static LPCFOLDERDATA  g_lpFolderData;
static LPCFILTER_ITEM g_lpFilterList;

/***************************************************************************
    private function prototypes
 ***************************************************************************/

static bool	InitFolders(void);
static bool CreateTreeIcons(void);
static void	CreateAllChildFolders(void);
static bool AddFolder(LPTREEFOLDER lpFolder);
static LPTREEFOLDER NewFolder(const char *lpTitle, UINT nFolderId, int nParent, UINT nIconId, DWORD dwFlags);
static void DeleteFolder(LPTREEFOLDER lpFolder);
static LRESULT CALLBACK TreeWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static int InitExtraFolders(void);
static void FreeExtraFolders(void);
static void SetExtraIcons(char *name, int *id);
static bool TryAddExtraFolderAndChildren(int parent_index);
static bool TrySaveExtraFolder(LPTREEFOLDER lpFolder);
static void LoadExternalFolders(int parent_index, int id);
static void SaveExternalFolders(int parent_index);
static bool FilterAvailable(int driver_index);

/***************************************************************************
    Functions to build builtin folder lists
 ***************************************************************************/

static void CreateManufacturerFolders(int parent_index);
static void CreateYearFolders(int parent_index);
static void CreateSourceFolders(int parent_index);
static void CreateDeficiencyFolders(int parent_index);
static void CreateBIOSFolders(int parent_index);
static void CreateCPUFolders(int parent_index);
static void CreateSoundFolders(int parent_index);
static void CreateScreenFolders(int parent_index);
static void CreateFPSFolders(int parent_index);
static void CreateResolutionFolders(int parent_index);
static void CreateSaveStateFolders(int parent_index);
static void CreateDumpingFolders(int parent_index);

/***************************************************************************
    public structures
 ***************************************************************************/

extern const FOLDERDATA g_folderData[] =
{
// 修改的 代码来源 (加斯顿90)
/*******************************************************************************************************************************************************************************************/
	// commented-out lines have parts not defined elsewhere
	{"All Games",       "allgames",          FOLDER_ALLGAMES,     IDI_FOLDER_ALLGAMES,      0,             0,            0, NULL,                       NULL,                    true },
	{"Available",       "available",         FOLDER_AVAILABLE,    IDI_FOLDER_AVAILABLE,     F_AVAILABLE,   0,            0, NULL,                       FilterAvailable,         true },
	{"Unavailable",     "unavailable",       FOLDER_UNAVAILABLE,  IDI_FOLDER_UNAVAILABLE,   0,             F_AVAILABLE,  0, NULL,                       FilterAvailable,         false },
	{"Console",         "console",           FOLDER_CONSOLE,      IDI_FOLDER_CONSOLE,       0,             0,            0, NULL,                       DriverIsConsole,         true },
	{"Collection",      "Collection", 	     FOLDER_COLLECTION,   IDI_FOLDER_COLLECTION,    0,			   0, 		     0, CreateCOLLECTIONFolders },
	{"BIOS",            "bios",              FOLDER_BIOS,         IDI_FOLDER_BIOS,          0,             0,            1, CreateBIOSFolders,          DriverIsBios,            true },
    {"Parents",         "originals",         FOLDER_ORIGINAL,     IDI_FOLDER_ORIGINALS,     F_ORIGINALS,   F_CLONES,     0, NULL,                       DriverIsClone,           false },
    {"Clones",          "clones",            FOLDER_CLONES,       IDI_FOLDER_CLONES,        F_CLONES,      F_ORIGINALS,  0, NULL,                       DriverIsClone,           true },
	{"Source",          "source",            FOLDER_SOURCE,       IDI_FOLDER_SOURCE,        0,             0,            0, CreateSourceFolders },
	{"Vertical",        "vertical",          FOLDER_VERTICAL,     IDI_FOLDER_VERTICAL,      F_VERTICAL,    F_HORIZONTAL, 0, NULL,                       DriverIsVertical,        true },
	{"Horizontal",      "horizontal",        FOLDER_HORIZONTAL,   IDI_FOLDER_HORIZONTAL,    F_HORIZONTAL,  F_VERTICAL,   0, NULL,                       DriverIsVertical,        false },
	{"Working",         "working",           FOLDER_WORKING,      IDI_FOLDER_WORKING,       F_WORKING,     F_NONWORKING, 0, NULL,                       DriverIsBroken,          false },	
	{"Not Working",     "nonworking",        FOLDER_NONWORKING,   IDI_FOLDER_NONWORKING,    F_NONWORKING,  F_WORKING,    0, NULL,                       DriverIsBroken,          true },	
	{"Imperfect",       "imperfect",         FOLDER_DEFICIENCY,   IDI_FOLDER_IMPERFECT,     0,             0,            0, CreateDeficiencyFolders },	
	{"Year",            "year",              FOLDER_YEAR,         IDI_FOLDER_YEAR,          0,             0,            0, CreateYearFolders },	
	{"Manufacturer",    "manufacturer",      FOLDER_MANUFACTURER, IDI_FOLDER_MANUFACTURER,  0,             0,            0, CreateManufacturerFolders },
	{"CHD",             "harddisk",          FOLDER_HARDDISK,     IDI_FOLDER_HARDDISK,      0,             0,            0, NULL,                       DriverIsHarddisk,        true },
	{"CPU",             "cpu",               FOLDER_CPU,          IDI_FOLDER_CPU,           0,             0,            1, CreateCPUFolders },
	{"Lightgun",        "lightgun",          FOLDER_LIGHTGUN,     IDI_FOLDER_LIGHTGUN,      0,             0,            0, NULL,                       DriverUsesLightGun,      true },
	{"Trackball",       "trackball",         FOLDER_TRACKBALL,    IDI_FOLDER_TRACKBALL,     0,             0,            0, NULL,                       DriverUsesTrackball,     true },
	{"Raster",          "raster",            FOLDER_RASTER,       IDI_FOLDER_RASTER,        F_RASTER,      F_VECTOR,     0, NULL,                       DriverIsVector,          false },
	{"Vector",          "vector",            FOLDER_VECTOR,       IDI_FOLDER_VECTOR,        F_VECTOR,      F_RASTER,     0, NULL,                       DriverIsVector,          true },
	{"Savestate",       "savestate",         FOLDER_SAVESTATE,    IDI_FOLDER_SAVESTATE,     0,             0,            0, CreateSaveStateFolders },	
	{"Dumping Status",  "dumping",           FOLDER_DUMPING,      IDI_FOLDER_DUMP,          0,             0,            1, CreateDumpingFolders },
	{"Mechanical",      "mechanical",        FOLDER_MECHANICAL,   IDI_FOLDER_MECHANICAL,    0,             0,            0, NULL,                       DriverIsMechanical,      true },
	//{"Non Mechanical",  "nonmechanical",     FOLDER_NONMECHANICAL,IDI_FOLDER,               0,             0,            0, NULL,                       DriverIsMechanical,      FALSE },
	{"Refresh",         "refresh",           FOLDER_FPS,          IDI_FOLDER_FPS,           0,             0,            1, CreateFPSFolders },
	{"Resolution",      "resolution",        FOLDER_RESOLUTION,   IDI_FOLDER_RESOL,         0,             0,            1, CreateResolutionFolders },
	{"Sound",           "sound",             FOLDER_SOUND,        IDI_FOLDER_SOUND,         0,             0,            1, CreateSoundFolders },
	{"Samples",         "samples",           FOLDER_SAMPLES,      IDI_FOLDER_SAMPLES,       0,             0,            0, NULL,                       DriverUsesSamples,       true },
	{"Screens",         "screens",           FOLDER_SCREENS,      IDI_FOLDER_MONITOR,       0,             0,            0, CreateScreenFolders },
	//{"Stereo",          "stereo",            FOLDER_STEREO,       IDI_FOLDER,               0,             0,            0, NULL,                       DriverIsStereo,          TRUE },
	{ NULL }
/*******************************************************************************************************************************************************************************************/
};

/* list of filter/control Id pairs */
extern const FILTER_ITEM g_filterList[] =
{
	{ F_CLONES,       IDC_FILTER_CLONES,      DriverIsClone, 		true },
	{ F_NONWORKING,   IDC_FILTER_NONWORKING,  DriverIsBroken, 		true },
	{ F_UNAVAILABLE,  IDC_FILTER_UNAVAILABLE, FilterAvailable, 		false },
	{ F_RASTER,       IDC_FILTER_RASTER,      DriverIsVector, 		false },
	{ F_VECTOR,       IDC_FILTER_VECTOR,      DriverIsVector, 		true },
	{ F_ORIGINALS,    IDC_FILTER_ORIGINALS,   DriverIsClone, 		false },
	{ F_WORKING,      IDC_FILTER_WORKING,     DriverIsBroken, 		false },
	{ F_AVAILABLE,    IDC_FILTER_AVAILABLE,   FilterAvailable, 		true },
	{ F_HORIZONTAL,   IDC_FILTER_HORIZONTAL,  DriverIsVertical, 	false },
	{ F_VERTICAL,     IDC_FILTER_VERTICAL,    DriverIsVertical, 	true },
	{ 0 }
};

static const TREEICON treeIconNames[] =
{
	{ IDI_FOLDER_OPEN,         "foldopen" },
	{ IDI_FOLDER,              "folder" },
	{ IDI_FOLDER_ALLGAMES,     "allgames" },
	{ IDI_FOLDER_AVAILABLE,    "foldavail" },
	{ IDI_FOLDER_BIOS,         "foldcsb" },
	{ IDI_FOLDER_CLONES,       "foldclone" },
	{ IDI_FOLDER_CPU,          "foldcsb" },
	{ IDI_FOLDER_DUMP,         "foldcsb" },
	{ IDI_FOLDER_FPS,      	   "foldfps" },
	{ IDI_FOLDER_HARDDISK,     "harddisk" },
	{ IDI_FOLDER_HORIZONTAL,   "horz" },
	{ IDI_FOLDER_IMPERFECT,    "foldimp" },
	{ IDI_FOLDER_LIGHTGUN,     "foldgun" },
	{ IDI_FOLDER_MANUFACTURER, "foldmanu" },
	{ IDI_FOLDER_MECHANICAL,   "mechanical" },
	{ IDI_FOLDER_MONITOR,      "multimon" },
	{ IDI_FOLDER_NONWORKING,   "nonwork" },
	{ IDI_FOLDER_ORIGINALS,    "foldorig" },
	{ IDI_FOLDER_RASTER,       "foldrast" },
	{ IDI_FOLDER_RESOL,        "foldres" },
	{ IDI_FOLDER_SAMPLES,      "foldsamp" },
	{ IDI_FOLDER_SAVESTATE,    "savestate" },
	{ IDI_FOLDER_SOUND,        "foldcsb" },
	{ IDI_FOLDER_SOURCE,       "foldsrc" },
	{ IDI_SOURCE,              "source" },
// 修改的 代码来源 (加斯顿90)
/**********************************************/
	{ IDI_FOLDER_CONSOLE,      "fold_console" },
	{ IDI_FOLDER_COLLECTION,   "fold_neogeo" },
/**********************************************/
	{ IDI_FOLDER_TRACKBALL,    "foldball" },
	{ IDI_FOLDER_UNAVAILABLE,  "foldunav" },
	{ IDI_FOLDER_VECTOR,       "foldvect" },
	{ IDI_FOLDER_VERTICAL,     "vert" },
	{ IDI_FOLDER_WORKING,      "working" },
	{ IDI_FOLDER_YEAR,         "foldyear" },
	{ IDI_BIOS,                "bios" },
	{ IDI_CHIP,                "chip" },
	{ IDI_MANUFACTURER,        "manufact" },
	{ IDI_MONITOR,             "monitor" },
	{ IDI_YEAR,                "year" },
};

/***************************************************************************
    public functions
 ***************************************************************************/

/* De-allocate all folder memory */
void FreeFolders(void)
{
	if (treeFolders)
	{
		if (numExtraFolders)
		{
			FreeExtraFolders();
			numFolders -= numExtraFolders;
		}

		for (int i = numFolders - 1; i >= 0; i--)
		{
			DeleteFolder(treeFolders[i]);
			treeFolders[i] = NULL;
			numFolders--;
		}

		free(treeFolders);
		treeFolders = NULL;
	}

	numFolders = 0;
}

/* Reset folder filters */
void ResetFilters(void)
{
	if (treeFolders)
		for (int i = 0; i < (int)numFolders; i++)
			treeFolders[i]->m_dwFlags &= ~F_MASK;
}

void InitTree(LPCFOLDERDATA lpFolderData, LPCFILTER_ITEM lpFilterList)
{
	g_lpFolderData = lpFolderData;
	g_lpFilterList = lpFilterList;

	InitFolders();
	/* this will subclass the treeview (where WM_DRAWITEM gets sent for the header control) */
	LONG_PTR l = GetWindowLongPtr(GetTreeView(), GWLP_WNDPROC);
	g_lpTreeWndProc = (WNDPROC)l;
	SetWindowLongPtr(GetTreeView(), GWLP_WNDPROC, (LONG_PTR)TreeWndProc);
}

void SetCurrentFolder(LPTREEFOLDER lpFolder)
{
	lpCurrentFolder = (lpFolder == 0) ? treeFolders[0] : lpFolder;
	nCurrentFolder = (lpCurrentFolder) ? lpCurrentFolder->m_nFolderId : 0;
}

LPTREEFOLDER GetCurrentFolder(void)
{
	return lpCurrentFolder;
}

UINT GetCurrentFolderID(void)
{
	return nCurrentFolder;
}

int GetNumFolders(void)
{
	return numFolders;
}

LPTREEFOLDER GetFolder(UINT nFolder)
{
	return (nFolder < numFolders) ? treeFolders[nFolder] : NULL;
}

LPTREEFOLDER GetFolderByID(UINT nID)
{
	for (int i = 0; i < numFolders; i++)
	{
		if (treeFolders[i]->m_nFolderId == nID)
			return treeFolders[i];
	}

	return (LPTREEFOLDER)0;
}

void AddGame(LPTREEFOLDER lpFolder, UINT nGame)
{
	if (lpFolder)
		SetBit(lpFolder->m_lpGameBits, nGame);
}

void RemoveGame(LPTREEFOLDER lpFolder, UINT nGame)
{
	ClearBit(lpFolder->m_lpGameBits, nGame);
}

int FindGame(LPTREEFOLDER lpFolder, int nGame)
{
	return FindBit(lpFolder->m_lpGameBits, nGame, true);
}

// Called to re-associate games with folders
void ResetWhichGamesInFolders(void)
{
	for (int i = 0; i < numFolders; i++)
	{
		LPTREEFOLDER lpFolder = treeFolders[i];
		// setup the games in our built-in folders
		for (int k = 0; g_lpFolderData[k].m_lpTitle; k++)
		{
			if (lpFolder->m_nFolderId == g_lpFolderData[k].m_nFolderId)
			{
				if (g_lpFolderData[k].m_pfnQuery || g_lpFolderData[k].m_bExpectedResult)
				{
					SetAllBits(lpFolder->m_lpGameBits, false);

					for (int jj = 0; jj < driver_list::total(); jj++)
					{
						// invoke the query function
						bool b = g_lpFolderData[k].m_pfnQuery ? g_lpFolderData[k].m_pfnQuery(jj) : true;

						// if we expect false, flip the result
						if (!g_lpFolderData[k].m_bExpectedResult)
							b = !b;

						// if we like what we hear, add the game
						if (b)
							AddGame(lpFolder, jj);
					}
				}
				break;
			}
		}
	}
}

/* Used to build the GameList */
bool GameFiltered(int nGame, DWORD dwMask)
{
	LPTREEFOLDER lpFolder = GetCurrentFolder();

	//Filter out the Bioses on all Folders, except for the Bios Folder
	if(lpFolder && lpFolder->m_nFolderId != FOLDER_BIOS)
	{
		if(DriverIsBios(nGame))
			return true;
	}

// (cache, 0 = cache, 1)
/* Add games "MACHINE_TYPE_CONSOLE" "MACHINE_TYPE_COMPUTER" "MACHINE_TYPE_OTHER"*/
	if(lpFolder && lpFolder->m_nFolderId != FOLDER_CONSOLE)
	{
		if(DriverIsConsole(nGame))
			return true;
	}

	if(driver_list::driver(nGame).name[0] == '_')
		return true;

	// Filter games--return true if the game should be HIDDEN in this view
	if(GetFilterInherit())
	{
		if(lpFolder)
		{
			LPTREEFOLDER lpParent = GetFolder(lpFolder->m_nParent);

			if(lpParent)
			{
				/* Check the Parent Filters and inherit them on child,
				* The inherited filters don't display on the custom Filter Dialog for the Child folder
				* No need to promote all games to parent folder, works as is */
				dwMask |= lpParent->m_dwFlags;
			}
		}
	}

// 修改的 代码来源 (缘来是你)
// =========================  搜索 =====================================================================>>>
    if (strlen(GetSearchText()) && _stricmp(GetSearchText(), SEARCH_PROMPT))
    {
        const char *search_text = GetSearchText();
        
        if (MyStrStrI(GetDescriptionByIndex(nGame, GetUsekoreanList()), search_text) != NULL)
        {
        }
        else if (MyStrStrI(GetGameNameByIndex(nGame, GetUsekoreanList()), search_text) != NULL)
        {
        }
        else if (MyStrStrI(GetGameManufactureByIndex(nGame, GetUsekoreanList()), search_text) != NULL)
        {
        }
        else if (MyStrStrI(GetDriverGameYear(nGame), search_text) != NULL)
        {
        }
        else if (MyStrStrI(GetDriverFileName(nGame), search_text) != NULL)
        {
        }
        else
        {
            return true;
        }
    }
// ====================================================================================================>>>

	// Are there filters set on this folder?
	if ((dwMask & F_MASK) == 0)
		return false;

	// Filter out clones?
	if (dwMask & F_CLONES && DriverIsClone(nGame))
		return true;

	for (int i = 0; g_lpFilterList[i].m_dwFilterType; i++)
		if (dwMask & g_lpFilterList[i].m_dwFilterType)
			if (g_lpFilterList[i].m_pfnQuery(nGame) == g_lpFilterList[i].m_bExpectedResult)
				return true;

	return false;
}

/* Get the parent of game in this view */
bool GetParentFound(int nGame)
{
	LPTREEFOLDER lpFolder = GetCurrentFolder();

	if(lpFolder)
	{
		int nParentIndex = GetParentIndex(&driver_list::driver(nGame));

		/* return false if no parent is there in this view */
		if( nParentIndex == -1)
			return false;

		/* return false if the folder should be HIDDEN in this view */
		if (TestBit(lpFolder->m_lpGameBits, nParentIndex) == 0)
			return false;

		/* return false if the game should be HIDDEN in this view */
		if (GameFiltered(nParentIndex, lpFolder->m_dwFlags))
			return false;

		return true;
	}

	return false;
}

LPCFILTER_ITEM GetFilterList(void)
{
	return g_lpFilterList;
}

/***************************************************************************
    private functions
 ***************************************************************************/

static void CreateSourceFolders(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);
	
	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		const char *source = GetDriverFileName(jj);

		// look for an existant source treefolder for this game
		// (likely to be the previous one, so start at the end)
		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, source) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			// nope, it's a source file we haven't seen before, make it.
			lpTemp = NewFolder(source, next_folder_id++, parent_index, IDI_SOURCE, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}

	SetNumOptionFolders(-1);
}

static void CreateManufacturerFolders(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		const char *made = GetDriverGameManufacturer(jj);

		// look for an existant manufacturer treefolder for this game
		// (likely to be the previous one, so start at the end)
		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, made) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			// nope, it's a manufacturer we haven't seen before, make it.
			lpTemp = NewFolder(made, next_folder_id++, parent_index, IDI_MANUFACTURER, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}
}

static void CreateDeficiencyFolders(int parent_index)
{
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpWrongCol, lpImpCol, lpImpGraph, lpMissSnd, lpImpSnd, lpIncomplete, lpNoSndHw;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);
	// create our subfolders
	lpWrongCol = NewFolder("Wrong Colors", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpImpCol = NewFolder("Imperfect Colors", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpImpGraph = NewFolder("Imperfect Graphics", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpMissSnd = NewFolder("Missing Sound", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpImpSnd = NewFolder("Imperfect Sound", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpIncomplete = NewFolder("Incomplete Prototype", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpNoSndHw = NewFolder("No Sound Hardware", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	AddFolder(lpWrongCol);
	AddFolder(lpImpCol);
	AddFolder(lpImpGraph);
	AddFolder(lpMissSnd);
	AddFolder(lpImpSnd);
	AddFolder(lpIncomplete);
	AddFolder(lpNoSndHw);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		uint32_t cache = GetDriverCacheLower(jj);
		if (BIT(cache, 21))
			AddGame(lpWrongCol, jj);

		if (BIT(cache, 20))
			AddGame(lpImpCol, jj);

		if (BIT(cache, 18))
			AddGame(lpImpGraph, jj);

		if (BIT(cache, 17))
			AddGame(lpMissSnd, jj);

		if (BIT(cache, 16))
			AddGame(lpImpSnd, jj);

		if (BIT(cache, 15))
			AddGame(lpIncomplete, jj);

		if (BIT(cache, 13))
			AddGame(lpNoSndHw, jj);
	}
}

static void CreateYearFolders(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		const char *year = GetDriverGameYear(jj);

		// look for an extant year treefolder for this game
		// (likely to be the previous one, so start at the end)
		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, year) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			// nope, it's a year we haven't seen before, make it.
			lpTemp = NewFolder(year, next_folder_id++, parent_index, IDI_YEAR, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}
}

static void CreateBIOSFolders(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	const game_driver *drv;
	int nParentIndex = -1;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		if (DriverIsClone(jj))
		{
			nParentIndex = GetParentIndex(&driver_list::driver(jj));

			if (nParentIndex < 0) 
				return;

			drv = &driver_list::driver(nParentIndex);
		}
		else
			drv = &driver_list::driver(jj);

		nParentIndex = GetParentIndex(drv);

		if (nParentIndex < 0 || !GetDriverGameTitle(nParentIndex))
			continue;

		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, GetDriverGameTitle(nParentIndex)) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			lpTemp = NewFolder(GetDriverGameTitle(nParentIndex), next_folder_id++, parent_index, IDI_BIOS, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}
}

static void CreateScreenFoldersIni(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		char screen[4];
		snprintf(screen, std::size(screen), "%d", DriverNumScreens(jj));

		// look for an existant screen treefolder for this game
		// (likely to be the previous one, so start at the end)
		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, screen) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			// nope, it's a screen we haven't seen before, make it.
			lpTemp = NewFolder(screen, next_folder_id++, parent_index, IDI_MONITOR, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}
}

static void CreateCPUFoldersIni(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		machine_config config(driver_list::driver(jj), MameUIGlobal());

		// enumerate through all devices
		for (device_execute_interface &device : execute_interface_enumerator(config.root_device()))
		{
			// get the name
			const char *cpu = device.device().name();

			// look for an existant CPU treefolder for this game
			// (likely to be the previous one, so start at the end)
			for (i = numFolders - 1; i >= start_folder; i--)
			{
				if (strcmp(treeFolders[i]->m_lpTitle, cpu) == 0)
				{
					AddGame(treeFolders[i], jj);
					break;
				}
			}

			if (i == start_folder - 1)
			{
				// nope, it's a CPU we haven't seen before, make it.
				lpTemp = NewFolder(cpu, next_folder_id++, parent_index, IDI_CHIP, GetFolderFlags(numFolders));
				AddFolder(lpTemp);
				AddGame(lpTemp, jj);
			}
		}
	}
}

static void CreateSoundFoldersIni(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		machine_config config(driver_list::driver(jj), MameUIGlobal());

		// enumerate through all devices
		for (device_sound_interface &device : sound_interface_enumerator(config.root_device()))
		{
			// get the name
			const char *sound = device.device().name();

			// look for an existant sound chip treefolder for this game
			// (likely to be the previous one, so start at the end)
			for (i = numFolders - 1; i >= start_folder; i--)
			{
				if (strcmp(treeFolders[i]->m_lpTitle, sound) == 0)
				{
					AddGame(treeFolders[i], jj);
					break;
				}
			}

			if (i == start_folder - 1)
			{
				// nope, it's a sound chip we haven't seen before, make it.
				lpTemp = NewFolder(sound, next_folder_id++, parent_index, IDI_CHIP, GetFolderFlags(numFolders));
				AddFolder(lpTemp);
				AddGame(lpTemp, jj);
			}
		}
	}
}

static void CreateSaveStateFolders(int parent_index)
{
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpSupported, lpUnsupported;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,false);
	// create our two subfolders
	lpSupported = NewFolder("Supported", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpUnsupported = NewFolder("Unsupported", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	AddFolder(lpSupported);
	AddFolder(lpUnsupported);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		if (DriverSupportsSaveState(jj))
			AddGame(lpSupported, jj);
		else
			AddGame(lpUnsupported, jj);
	}
}

static void CreateResolutionFoldersIni(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp, lpVectorH, lpVectorV, lpScreenless;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);
	// create our two subfolders
	lpVectorH = NewFolder("Vector (H)", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpVectorV = NewFolder("Vector (V)", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpScreenless = NewFolder("Screenless", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	AddFolder(lpVectorH);
	AddFolder(lpVectorV);
	AddFolder(lpScreenless);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		machine_config config(driver_list::driver(jj), MameUIGlobal());
		char res[32];

		if (DriverIsVector(jj))
		{
			if (DriverIsVertical(jj))
			{
				AddGame(lpVectorV, jj);
				continue;
			}
			else
			{
				AddGame(lpVectorH, jj);
				continue;
			}
		}

		const screen_device *screen = screen_device_enumerator(config.root_device()).first();

		if (screen == nullptr)
		{
			AddGame(lpScreenless, jj);
			continue;
		}

		const rectangle &visarea = screen->visible_area();

		if (DriverIsVertical(jj))
			snprintf(res, std::size(res), "%d x %d (V)", visarea.width(), visarea.height());
		else
			snprintf(res, std::size(res), "%d x %d (H)", visarea.width(), visarea.height());

		// look for an existant resolution treefolder for this game
		// (likely to be the previous one, so start at the end)
		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, res) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			// nope, it's a resolution we haven't seen before, make it.
			lpTemp = NewFolder(res, next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}
}

static void CreateFPSFoldersIni(int parent_index)
{
	int i = 0; 
	int start_folder = numFolders;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpTemp, lpVector, lpScreenless;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits, false);
	// create our two subfolders
	lpVector = NewFolder("Vector", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpScreenless = NewFolder("Screenless", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	AddFolder(lpVector);
	AddFolder(lpScreenless);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		machine_config config(driver_list::driver(jj), MameUIGlobal());
		char fps[16];
		
		if (DriverIsVector(jj))
		{
			AddGame(lpVector, jj);
			continue;
		}

		const screen_device *screen = screen_device_enumerator(config.root_device()).first();

		if (screen == nullptr)
		{
			AddGame(lpScreenless, jj);
			continue;
		}

		snprintf(fps, std::size(fps), "%f Hz", ATTOSECONDS_TO_HZ(screen->refresh_attoseconds()));

		// look for an existant refresh treefolder for this game
		// (likely to be the previous one, so start at the end)
		for (i = numFolders - 1; i >= start_folder; i--)
		{
			if (strcmp(treeFolders[i]->m_lpTitle, fps) == 0)
			{
				AddGame(treeFolders[i], jj);
				break;
			}
		}

		if (i == start_folder - 1)
		{
			// nope, it's a refresh we haven't seen before, make it.
			lpTemp = NewFolder(fps, next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
			AddFolder(lpTemp);
			AddGame(lpTemp, jj);
		}
	}
}

void CreateDumpingFoldersIni(int parent_index)
{
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
	LPTREEFOLDER lpBadDump, lpNoDump, lpGoodDump;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,false);
	// create our two subfolders
	lpNoDump = NewFolder("No Dump", next_folder_id, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpBadDump = NewFolder("Bad Dump", next_folder_id, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpGoodDump = NewFolder("Good Dump", next_folder_id, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	AddFolder(lpNoDump);
	AddFolder(lpBadDump);
	AddFolder(lpGoodDump);

	for (int jj = 0; jj < driver_list::total(); jj++)
	{
		machine_config config(driver_list::driver(jj), MameUIGlobal());
		bool bBadDump = false;
		bool bNoDump = false;

		if (!DriverUsesRoms(jj))
			continue;

		for (device_t &device : device_enumerator(config.root_device()))
		{
			for (const rom_entry *region = rom_first_region(device); region != nullptr; region = rom_next_region(region))
			{
				for (const rom_entry *rom = rom_first_file(region); rom != nullptr; rom = rom_next_file(rom))
				{
					if (ROMREGION_ISROMDATA(region) || ROMREGION_ISDISKDATA(region))
					{
						util::hash_collection hashes(rom->hashdata());
						
						if (hashes.flag(util::hash_collection::FLAG_NO_DUMP))
							bNoDump = true;
						
						if (hashes.flag(util::hash_collection::FLAG_BAD_DUMP))
							bBadDump = true;
					}
				}
			}
		}

		if (bNoDump)
		{
			AddGame(lpNoDump, jj);
			continue;
		}

		if (bBadDump)
		{
			AddGame(lpBadDump, jj);
			continue;
		}

		AddGame(lpGoodDump, jj);
	}
}

static void CreateCPUFolders(int parent_index)
{
	if (RequiredDriverCache())
	{
		CreateCPUFoldersIni(parent_index);
		SaveExternalFolders(parent_index);
	}
	else
		LoadExternalFolders(parent_index, IDI_CHIP);

	SendMessage(GetProgressBar(), PBM_SETPOS, 20, 0);
}

static void CreateSoundFolders(int parent_index)
{
	if (RequiredDriverCache())
	{
		CreateSoundFoldersIni(parent_index);
		SaveExternalFolders(parent_index);
	}
	else
		LoadExternalFolders(parent_index, IDI_CHIP);

	SendMessage(GetProgressBar(), PBM_SETPOS, 95, 0);
}

static void CreateScreenFolders(int parent_index)
{
	if (RequiredDriverCache())
	{
		CreateScreenFoldersIni(parent_index);
		SaveExternalFolders(parent_index);
	}
	else
		LoadExternalFolders(parent_index, IDI_MONITOR);

	SendMessage(GetProgressBar(), PBM_SETPOS, 80, 0);
}

static void CreateResolutionFolders(int parent_index)
{
	if (RequiredDriverCache())
	{
		CreateResolutionFoldersIni(parent_index);
		SaveExternalFolders(parent_index);
	}
	else
		LoadExternalFolders(parent_index, IDI_FOLDER);

	SendMessage(GetProgressBar(), PBM_SETPOS, 65, 0);
}

static void CreateFPSFolders(int parent_index)
{
	if (RequiredDriverCache())
	{
		CreateFPSFoldersIni(parent_index);
		SaveExternalFolders(parent_index);
	}
	else
		LoadExternalFolders(parent_index, IDI_FOLDER);

	SendMessage(GetProgressBar(), PBM_SETPOS, 50, 0);
}

static void CreateDumpingFolders(int parent_index)
{
	if (RequiredDriverCache())
	{
		CreateDumpingFoldersIni(parent_index);
		SaveExternalFolders(parent_index);
	}
	else
		LoadExternalFolders(parent_index, IDI_FOLDER);

	SendMessage(GetProgressBar(), PBM_SETPOS, 35, 0);
}

static void LoadExternalFolders(int parent_index, int id)
{
	const char* fname = NULL;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	for (int j = 0; g_lpFolderData[j].m_lpTitle; j++)
		if (strcmp(lpFolder->m_lpTitle, g_lpFolderData[j].m_lpTitle)==0)
			fname = g_lpFolderData[j].short_name;

	if (fname == NULL)
		return;

	char filename[MAX_PATH];
	snprintf(filename, std::size(filename), "%s\\%s", GetGuiDir(), fname);
	FILE *f = fopen(filename, "r");
 
	if (f == NULL)
		return;

	char readbuf[256];
	char *name = NULL;
	LPTREEFOLDER lpTemp = NULL;
	int current_id = lpFolder->m_nFolderId;

	while (fgets(readbuf, 256, f))
	{
		/* do we have [...] ? */
		if (readbuf[0] == '[')
		{
			char *p = strchr(readbuf, ']');
			
			if (p == NULL)
				continue;

			*p = '\0';
			name = &readbuf[1];

			/* is it [FOLDER_SETTINGS]? */
			if (strcmp(name, "FOLDER_SETTINGS") == 0)
			{
				current_id = -1;
				continue;
			}
			else
			{
				/* is it [ROOT_FOLDER]? */
				if (!strcmp(name, "ROOT_FOLDER"))
				{
					current_id = lpFolder->m_nFolderId;
					lpTemp = lpFolder;
				}
				else
				{
					current_id = next_folder_id++;
					lpTemp = NewFolder(name, current_id, parent_index, id, GetFolderFlags(numFolders));
					AddFolder(lpTemp);
				}
			}
		}
		else if (current_id != -1)
		{
			/* string on a line by itself -- game name */
			name = strtok(readbuf, " \t\r\n");

			if (name == NULL)
			{
				current_id = -1;
				continue;
			}

			AddGame(lpTemp, GetGameNameIndex(name));
		}
	}

	fclose(f);
}

static void SaveExternalFolders(int parent_index)
{
	const char* fname = NULL;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	for (int j = 0; g_lpFolderData[j].m_lpTitle; j++)
		if (strcmp(lpFolder->m_lpTitle, g_lpFolderData[j].m_lpTitle)==0)
			fname = g_lpFolderData[j].short_name;

	if (fname == NULL)
		return;

	char filename[MAX_PATH];
	snprintf(filename, std::size(filename), "%s\\%s", GetGuiDir(), fname);
	wchar_t *temp = win_wstring_from_utf8(GetGuiDir());
	CreateDirectory(temp, NULL);
	free(temp);
	FILE *f = fopen(filename, "w");

	if (f == NULL)
		return;

	fprintf(f, "[FOLDER_SETTINGS]\n");
	fprintf(f, "RootFolderIcon custom\n");
	fprintf(f, "SubFolderIcon custom\n");

	/* need to loop over all our TREEFOLDERs--first the root one, then each child.
	start with the root */
	TREEFOLDER *folder_data = lpFolder;
	fprintf(f, "\n[ROOT_FOLDER]\n");

	for (int i = 0; i < driver_list::total(); i++)
		if (TestBit(folder_data->m_lpGameBits, i))
			fprintf(f, "%s\n", GetDriverGameName(i));

	/* look through the custom folders for ones with our root as parent */
	for (int jj = 0; jj < numFolders; jj++)
	{
		folder_data = treeFolders[jj];

		if (folder_data->m_nParent >= 0 && treeFolders[folder_data->m_nParent] == lpFolder)
		{
			fprintf(f, "\n[%s]\n", folder_data->m_lpTitle);

			for (int i = 0; i < driver_list::total(); i++)
				if (TestBit(folder_data->m_lpGameBits, i))
					fprintf(f, "%s\n", GetDriverGameName(i));
		}
	}

	fclose(f);
}


// creates child folders of all the top level folders, including custom ones
void CreateAllChildFolders(void)
{
	int num_top_level_folders = numFolders;

	for (int i = 0; i < num_top_level_folders; i++)
	{
		LPTREEFOLDER lpFolder = treeFolders[i];
		LPCFOLDERDATA lpFolderData = NULL;

		for (int j = 0; g_lpFolderData[j].m_lpTitle; j++)
		{
			if (g_lpFolderData[j].m_nFolderId == lpFolder->m_nFolderId)
			{
				lpFolderData = &g_lpFolderData[j];
				break;
			}
		}

		if (lpFolderData)
		{
			if (lpFolderData->m_pfnCreateFolders)
				lpFolderData->m_pfnCreateFolders(i);
		}
		else
		{
			if ((lpFolder->m_dwFlags & F_CUSTOM) == 0)
				continue;

			// load the extra folder files, which also adds children
			if (TryAddExtraFolderAndChildren(i) == false)
				lpFolder->m_nFolderId = FOLDER_NONE;
		}
	}
}

// adds these folders to the treeview
void ResetTreeViewFolders(void)
{
	HWND hTreeView = GetTreeView();
	TVITEM tvi;
	TVINSERTSTRUCT tvs;

	// currently "cached" parent
	HTREEITEM hti_parent = NULL;
	int index_parent = -1;

	(void)TreeView_DeleteAllItems(hTreeView);
	tvs.hInsertAfter = TVI_LAST; // main items inserted according to g_folderData[] array

	for (int i = 0; i < numFolders; i++)
	{
		LPTREEFOLDER lpFolder = treeFolders[i];

		if (lpFolder->m_nParent == -1)
		{
			if (lpFolder->m_nFolderId < MAX_FOLDERS)
			{
				// it's a built in folder, let's see if we should show it
				if (GetShowFolder(lpFolder->m_nFolderId) == false)
					continue;
			}

			tvi.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
			tvs.hParent = TVI_ROOT;
			tvi.pszText = lpFolder->m_lptTitle;
			tvi.lParam = (LPARAM)lpFolder;
			tvi.iImage = GetTreeViewIconIndex(lpFolder->m_nIconId);
			tvi.iSelectedImage = 0;
			tvs.item = tvi;

			// Add root branch
			hti_parent = TreeView_InsertItem(hTreeView, &tvs);
			continue;
		}

		// not a top level branch, so look for parent
		if (treeFolders[i]->m_nParent != index_parent)
		{
			hti_parent = TreeView_GetRoot(hTreeView);

			while (1)
			{
				if (hti_parent == NULL)
					// couldn't find parent folder, so it's a built-in but
					// not shown folder
					break;

				tvi.hItem = hti_parent;
				tvi.mask = TVIF_PARAM;

				(void)TreeView_GetItem(hTreeView, &tvi);

				if (((LPTREEFOLDER)tvi.lParam) == treeFolders[treeFolders[i]->m_nParent])
					break;

				hti_parent = TreeView_GetNextSibling(hTreeView, hti_parent);
			}

			// if parent is not shown, then don't show the child either obviously!
			if (hti_parent == NULL)
				continue;

			index_parent = treeFolders[i]->m_nParent;
		}

		tvi.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		tvs.hParent = hti_parent;
		tvi.iImage = GetTreeViewIconIndex(treeFolders[i]->m_nIconId);
		tvi.iSelectedImage = 0;
		tvi.pszText = treeFolders[i]->m_lptTitle;
		tvi.lParam = (LPARAM)treeFolders[i];
		tvs.item = tvi;

		// Add it to this tree branch
		tvs.hInsertAfter = TVI_SORT; // sub items always sorted
		(void)TreeView_InsertItem(hTreeView, &tvs);
		tvs.hInsertAfter = TVI_LAST; // restore for next main item
	}
}

void SelectTreeViewFolder(int folder_id)
{
	HWND hTreeView = GetTreeView();
	HTREEITEM hti = TreeView_GetRoot(hTreeView);
	TVITEM tvi;

	memset(&tvi, 0, sizeof(TVITEM));

	while (hti != NULL)
	{
		tvi.hItem = hti;
		tvi.mask = TVIF_PARAM;

		(void)TreeView_GetItem(hTreeView, &tvi);

		if (((LPTREEFOLDER)tvi.lParam)->m_nFolderId == folder_id)
		{
			(void)TreeView_SelectItem(hTreeView,tvi.hItem);
			SetCurrentFolder((LPTREEFOLDER)tvi.lParam);
			return;
		}

		HTREEITEM hti_next = TreeView_GetChild(hTreeView, hti);

		if (hti_next == NULL)
		{
			hti_next = TreeView_GetNextSibling(hTreeView, hti);

			if (hti_next == NULL)
			{
				hti_next = TreeView_GetParent(hTreeView, hti);

				if (hti_next != NULL)
					hti_next = TreeView_GetNextSibling(hTreeView, hti_next);
			}
		}

		hti = hti_next;
	}

	// could not find folder to select
	// make sure we select something
	tvi.hItem = TreeView_GetRoot(hTreeView);
	tvi.mask = TVIF_PARAM;
	(void)TreeView_GetItem(hTreeView, &tvi);
	(void)TreeView_SelectItem(hTreeView, tvi.hItem);
	SetCurrentFolder((LPTREEFOLDER)tvi.lParam);
}

/*
 * Does this folder have an INI associated with it?
 * Currently only true for FOLDER_VECTOR and children
 * of FOLDER_SOURCE.
 */
static bool FolderHasIni(LPTREEFOLDER lpFolder) 
{
	if (FOLDER_RASTER == lpFolder->m_nFolderId || FOLDER_VECTOR == lpFolder->m_nFolderId ||
		FOLDER_VERTICAL == lpFolder->m_nFolderId || FOLDER_HORIZONTAL == lpFolder->m_nFolderId) 
			return true;

	if (lpFolder->m_nParent != -1 && FOLDER_SOURCE == treeFolders[lpFolder->m_nParent]->m_nFolderId) 
		return true;

	return false;
}

/* Add a folder to the list.  Does not allocate */
static bool AddFolder(LPTREEFOLDER lpFolder)
{
	TREEFOLDER **tmpTree = NULL;
	UINT oldFolderArrayLength = folderArrayLength;

	if (numFolders + 1 >= folderArrayLength)
	{
		folderArrayLength += 500;
		tmpTree = (TREEFOLDER **)malloc(sizeof(TREEFOLDER **) * folderArrayLength);
		memcpy(tmpTree, treeFolders, sizeof(TREEFOLDER **) * oldFolderArrayLength);

		if (treeFolders) 
			free(treeFolders);

		treeFolders = tmpTree;
	}

	/* Is there an folder.ini that can be edited? */
	if (FolderHasIni(lpFolder)) 
		lpFolder->m_dwFlags |= F_INIEDIT;

	treeFolders[numFolders] = lpFolder;
	numFolders++;
	return true;
}

/* Allocate and initialize a NEW TREEFOLDER */
static LPTREEFOLDER NewFolder(const char *lpTitle, UINT nFolderId, int nParent, UINT nIconId, DWORD dwFlags)
{
	LPTREEFOLDER lpFolder = (LPTREEFOLDER)malloc(sizeof(TREEFOLDER));
	memset(lpFolder, 0, sizeof(TREEFOLDER));
	lpFolder->m_lpTitle = (char *)malloc(strlen(lpTitle) + 1);
	strcpy((char *)lpFolder->m_lpTitle, lpTitle);
	lpFolder->m_lptTitle = win_wstring_from_utf8(lpFolder->m_lpTitle);
	lpFolder->m_lpGameBits = NewBits(driver_list::total());
	lpFolder->m_nFolderId = nFolderId;
	lpFolder->m_nParent = nParent;
	lpFolder->m_nIconId = nIconId;
	lpFolder->m_dwFlags = dwFlags;
	return lpFolder;
}

/* Deallocate the passed in LPTREEFOLDER */
static void DeleteFolder(LPTREEFOLDER lpFolder)
{
	if (lpFolder)
	{
		if (lpFolder->m_lpGameBits)
		{
			DeleteBits(lpFolder->m_lpGameBits);
			lpFolder->m_lpGameBits = 0;
		}

		free(lpFolder->m_lptTitle);
		lpFolder->m_lptTitle = 0;
		free(lpFolder->m_lpTitle);
		lpFolder->m_lpTitle = 0;
		free(lpFolder);
	}
}

/* Can be called to re-initialize the array of treeFolders */
static bool InitFolders(void)
{
	int i = 0;
	DWORD dwFolderFlags = 0;

	if (treeFolders)
	{
		for (i = numFolders - 1; i >= 0; i--)
		{
			DeleteFolder(treeFolders[i]);
			treeFolders[i] = 0;
			numFolders--;
		}
	}

	numFolders = 0;

	if (folderArrayLength == 0)
	{
		folderArrayLength = 200;
		treeFolders = (TREEFOLDER **)malloc(sizeof(TREEFOLDER **) * folderArrayLength);

		if (!treeFolders)
		{
			folderArrayLength = 0;
			return 0;
		}
		else
			memset(treeFolders, 0, sizeof(TREEFOLDER **) * folderArrayLength);
	}
	
	// built-in top level folders
	for (i = 0; g_lpFolderData[i].m_lpTitle; i++)
	{
		LPCFOLDERDATA fData = &g_lpFolderData[i];
		/* get the saved folder flags */
		dwFolderFlags = GetFolderFlags(numFolders);
		/* create the folder */
		AddFolder(NewFolder(fData->m_lpTitle, fData->m_nFolderId, -1, fData->m_nIconId, dwFolderFlags));
	}

	numExtraFolders = InitExtraFolders();

	for (i = 0; i < numExtraFolders; i++)
	{
		LPEXFOLDERDATA  fExData = ExtraFolderData[i];
		// OR in the saved folder flags
		dwFolderFlags = fExData->m_dwFlags | GetFolderFlags(numFolders);
		// create the folder
		AddFolder(NewFolder(fExData->m_szTitle, fExData->m_nFolderId, fExData->m_nParent, fExData->m_nIconId, dwFolderFlags));
	}

	CreateAllChildFolders();
	CreateTreeIcons();
	ResetWhichGamesInFolders();
	ResetTreeViewFolders();
	SelectTreeViewFolder(GetSavedFolderID());
	LoadFolderFlags();
	return true;
}

// create iconlist and Treeview control
static bool CreateTreeIcons(void)
{
	HICON hIcon = NULL;
	HINSTANCE hInst = GetModuleHandle(NULL);
	int numIcons = ICON_MAX + numExtraIcons;

	hTreeSmall = ImageList_Create (16, 16, ILC_COLORDDB | ILC_MASK, numIcons, numIcons);

	for (int i = 0; i < ICON_MAX; i++)
	{
		hIcon = LoadIconFromFile(treeIconNames[i].lpName);

		if (!hIcon)
			hIcon = LoadIcon(hInst, MAKEINTRESOURCE(treeIconNames[i].nResourceID));

		if (ImageList_AddIcon(hTreeSmall, hIcon) == -1)
		{
			ErrorMessageBox("Error creating icon on regular folder, %i %i", i, hIcon != NULL);
			return false;
		}
	}

	for (int i = 0; i < numExtraIcons; i++)
	{
		if ((hIcon = LoadIconFromFile(ExtraFolderIcons[i])) == 0)
			hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_FOLDER));

		if (ImageList_AddIcon(hTreeSmall, hIcon) == -1)
		{
			ErrorMessageBox("Error creating icon on extra folder, %i %i", i, hIcon != NULL);
			return false;
		}
	}

	// Be sure that all the small icons were added.
	if (ImageList_GetImageCount(hTreeSmall) < numIcons)
	{
		ErrorMessageBox("Error with icon list--too few images.  %i %i", ImageList_GetImageCount(hTreeSmall), numIcons);
		return false;
	}

	// Be sure that all the small icons were added.
	if (ImageList_GetImageCount (hTreeSmall) < ICON_MAX)
	{
		ErrorMessageBox("Error with icon list--too few images.  %i < %i", ImageList_GetImageCount(hTreeSmall), ICON_MAX);
		return false;
	}

	// Associate the image lists with the list view control.
	(void)TreeView_SetImageList(GetTreeView(), hTreeSmall, TVSIL_NORMAL);
	return true;
}

/* Header code - Directional Arrows */
static LRESULT CALLBACK TreeWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_KEYDOWN :
			if (wParam == VK_F2)
			{
				if (lpCurrentFolder->m_dwFlags & F_CUSTOM)
				{
					(void)TreeView_EditLabel(hWnd, TreeView_GetSelection(hWnd));
					return true;
				}
			}

			break;
	}

	/* message not handled */
	return CallWindowProc(g_lpTreeWndProc, hWnd, uMsg, wParam, lParam);
}

/*
 * Filter code - should be moved to filter.c/filter.h
 * Added 01/09/99 - MSH <mhaaland@hypertech.com>
 */

/* find a FOLDERDATA by folderID */
LPCFOLDERDATA FindFilter(DWORD folderID)
{
	for (int i = 0; g_lpFolderData[i].m_lpTitle; i++)
		if (g_lpFolderData[i].m_nFolderId == folderID)
			return &g_lpFolderData[i];

	return (LPFOLDERDATA) 0;
}

LPTREEFOLDER GetFolderByName(int nParentId, const char *pszFolderName)
{
	//First Get the Parent TreeviewItem
	//Enumerate Children
	for (int i = 0; i < numFolders; i++)
	{
		if (!strcmp(treeFolders[i]->m_lpTitle, pszFolderName))
		{
			int nParent = treeFolders[i]->m_nParent;

			if ((nParent >= 0) && treeFolders[nParent]->m_nFolderId == nParentId)
				return treeFolders[i];
		}
	}

	return NULL;
}

static int InitExtraFolders(void)
{
	WIN32_FIND_DATA FindFileData;
	int count = 0;
	char buf[256];
	char path[MAX_PATH];
	const char *dir = GetFolderDir();

	memset(ExtraFolderData, 0, (MAX_EXTRA_FOLDERS * MAX_EXTRA_SUBFOLDERS)* sizeof(LPEXFOLDERDATA));

	// Why create the directory if it doesn't exist, just return 0 folders.
	if (osd::directory::open(dir) == nullptr)
		return 0;

	snprintf(path, std::size(path), "%s\\*.*", dir);
	HANDLE hFind = winui_find_first_file_utf8(path, &FindFileData);

	for (int i = 0; i < MAX_EXTRA_FOLDERS; i++)
	{
		ExtraFolderIcons[i] = NULL;
	}

	numExtraIcons = 0;

	if (hFind != INVALID_HANDLE_VALUE)
	{
		while (FindNextFile (hFind, &FindFileData) != 0)
		{
			char *file = win_utf8_from_wstring(FindFileData.cFileName);
			char inifile[MAX_PATH];

			memset(&inifile, 0, sizeof(inifile));
			snprintf(inifile, std::size(inifile), "%s\\%s", dir, file);
			FILE *readfile = fopen(inifile, "r");

			if (readfile != NULL)
			{
				int icon[2] = { 0, 0 };

				while (fgets(buf, 256, readfile))
				{
					if (buf[0] == '[')
					{
						char *p = strchr(buf, ']');

						if (p == NULL)
							continue;

						*p = '\0';
						char *name = &buf[1];

						if (!strcmp(name, "FOLDER_SETTINGS"))
						{
							while (fgets(buf, 256, readfile))
							{
								name = strtok(buf, " =\r\n");

								if (name == NULL)
									break;

								if (!strcmp(name, "RootFolderIcon"))
								{
									name = strtok(NULL, " =\r\n");

									if (name != NULL)
										SetExtraIcons(name, &icon[0]);
								}
								if (!strcmp(name, "SubFolderIcon"))
								{
									name = strtok(NULL, " =\r\n");

									if (name != NULL)
										SetExtraIcons(name, &icon[1]);
								}
							}

							break;
						}
					}
				}

				fclose(readfile);
				strcpy(buf, file);
				char *ext = strrchr(buf, '.');
				free(file);

				if (ext && *(ext + 1) && !core_stricmp(ext + 1, "ini"))
				{
					ExtraFolderData[count] =(EXFOLDERDATA*) malloc(sizeof(EXFOLDERDATA));

					if (ExtraFolderData[count])
					{
						*ext = '\0';
						memset(ExtraFolderData[count], 0, sizeof(EXFOLDERDATA));
						strncpy(ExtraFolderData[count]->m_szTitle, buf, 63);
						ExtraFolderData[count]->m_nFolderId = next_folder_id++;
						ExtraFolderData[count]->m_nParent = -1;
						ExtraFolderData[count]->m_dwFlags = F_CUSTOM;
						ExtraFolderData[count]->m_nIconId = icon[0] ? -icon[0] : IDI_FOLDER;
						ExtraFolderData[count]->m_nSubIconId = icon[1] ? -icon[1] : IDI_FOLDER;
						count++;
					}
				}
			}
		}
	}

	return count;
}

void FreeExtraFolders(void)
{
	for (int i = 0; i < numExtraFolders; i++)
	{
		if (ExtraFolderData[i])
		{
			free(ExtraFolderData[i]);
			ExtraFolderData[i] = NULL;
		}
	}

	for (int i = 0; i < numExtraIcons; i++)
	{
		free(ExtraFolderIcons[i]);
	}

	numExtraIcons = 0;
}


static void SetExtraIcons(char *name, int *id)
{
	char *p = strchr(name, '.');

	if (p != NULL)
		*p = '\0';

	ExtraFolderIcons[numExtraIcons] = (char*)malloc(strlen(name) + 1);

	if (ExtraFolderIcons[numExtraIcons])
	{
		*id = ICON_MAX + numExtraIcons;
		strcpy(ExtraFolderIcons[numExtraIcons], name);
		numExtraIcons++;
	}
}


// Called to add child folders of the top level extra folders already created
bool TryAddExtraFolderAndChildren(int parent_index)
{
	char fname[MAX_PATH];
	char readbuf[256];
	char *name = NULL;
	LPTREEFOLDER lpTemp = NULL;
	LPTREEFOLDER lpFolder = treeFolders[parent_index];

	int current_id = lpFolder->m_nFolderId;
	int id = lpFolder->m_nFolderId - MAX_FOLDERS;
	snprintf(fname, std::size(fname), "%s\\%s.ini", GetFolderDir(), ExtraFolderData[id]->m_szTitle);
	FILE *f = fopen(fname, "r");
 
	if (f == NULL)
		return false;

	while (fgets(readbuf, 256, f))
	{
		/* do we have [...] ? */
		if (readbuf[0] == '[')
		{
			char *p = strchr(readbuf, ']');

			if (p == NULL)
				continue;

			*p = '\0';
			name = &readbuf[1];

			/* is it [FOLDER_SETTINGS]? */
			if (strcmp(name, "FOLDER_SETTINGS") == 0)
			{
				current_id = -1;
				continue;
			}
			else
			{
				/* is it [ROOT_FOLDER]? */
				if (!strcmp(name, "ROOT_FOLDER"))
				{
					current_id = lpFolder->m_nFolderId;
					lpTemp = lpFolder;
				}
				else
				{
					/* must be [folder name] */
					current_id = next_folder_id++;
					/* create a new folder with this name,
					and the flags for this folder as read from the registry */
					lpTemp = NewFolder(name, current_id, parent_index, ExtraFolderData[id]->m_nSubIconId, GetFolderFlags(numFolders) | F_CUSTOM);
					ExtraFolderData[current_id] = (EXFOLDERDATA*)malloc(sizeof(EXFOLDERDATA));
					memset(ExtraFolderData[current_id], 0, sizeof(EXFOLDERDATA));
					ExtraFolderData[current_id]->m_nFolderId = current_id - MAX_EXTRA_FOLDERS;
					ExtraFolderData[current_id]->m_nIconId = ExtraFolderData[id]->m_nSubIconId;
					ExtraFolderData[current_id]->m_nParent = ExtraFolderData[id]->m_nFolderId;
					ExtraFolderData[current_id]->m_nSubIconId = -1;
					strcpy(ExtraFolderData[current_id]->m_szTitle, name);
					ExtraFolderData[current_id]->m_dwFlags = ExtraFolderData[id]->m_dwFlags;
					AddFolder(lpTemp);
				}
			}
		}
		else if (current_id != -1)
		{
			/* string on a line by itself -- game name */
			name = strtok(readbuf, " \t\r\n");

			if (name == NULL)
			{
				current_id = -1;
				continue;
			}

			/* IMPORTANT: This assumes that all driver names are lowercase! */
			for (int i = 0; name[i]; i++)
				name[i] = tolower(name[i]);

			if (lpTemp == NULL)
			{
				ErrorMessageBox("Error parsing %s: missing [folder name] or [ROOT_FOLDER]", fname);
				current_id = lpFolder->m_nFolderId;
				lpTemp = lpFolder;
			}

			AddGame(lpTemp, GetGameNameIndex(name));
		}
	}

	fclose(f);
	return true;
}


void GetFolders(TREEFOLDER ***folders,int *num_folders)
{
	*folders = treeFolders;
	*num_folders = numFolders;
}

static bool TryRenameCustomFolderIni(LPTREEFOLDER lpFolder, const char *old_name, const char *new_name)
{
	char filename[MAX_PATH];
	char new_filename[MAX_PATH];

	if (lpFolder->m_nParent >= 0)
	{
		//it is a custom SubFolder
		LPTREEFOLDER lpParent = GetFolder(lpFolder->m_nParent);

		if(lpParent)
		{
			snprintf(filename, std::size(filename), "%s\\%s\\%s.ini", GetIniDir(), lpParent->m_lpTitle, old_name);
			snprintf(new_filename, std::size(new_filename), "%s\\%s\\%s.ini", GetIniDir(), lpParent->m_lpTitle, new_name);
			winui_move_file_utf8(filename, new_filename);
		}
	}
	else
	{
		//Rename the File, if it exists
		snprintf(filename, std::size(filename), "%s\\%s.ini", GetIniDir(), old_name);
		snprintf(new_filename, std::size(new_filename), "%s\\%s.ini", GetIniDir(), new_name);
		winui_move_file_utf8(filename, new_filename);
		//Rename the Directory, if it exists
		snprintf(filename, std::size(filename), "%s\\%s", GetIniDir(), old_name);
		snprintf(new_filename, std::size(new_filename), "%s\\%s", GetIniDir(), new_name);
		winui_move_file_utf8(filename, new_filename);
	}

	return true;
}

bool TryRenameCustomFolder(LPTREEFOLDER lpFolder, const char *new_name)
{
	char filename[MAX_PATH];
	char new_filename[MAX_PATH];

	if (lpFolder->m_nParent >= 0)
	{
		// a child extra folder was renamed, so do the rename and save the parent
		// save old title
		char *old_title = lpFolder->m_lpTitle;
		// set new title
		lpFolder->m_lpTitle = (char *)malloc(strlen(new_name) + 1);
		strcpy(lpFolder->m_lpTitle, new_name);

		// try to save
		if (TrySaveExtraFolder(lpFolder) == false)
		{
			// failed, so free newly allocated title and restore old
			free(lpFolder->m_lpTitle);
			lpFolder->m_lpTitle = old_title;
			return false;
		}
		
		TryRenameCustomFolderIni(lpFolder, old_title, new_name);
		// successful, so free old title
		free(old_title);
		return true;
	}

	// a parent extra folder was renamed, so rename the file
	snprintf(new_filename, std::size(new_filename), "%s\\%s.ini", GetFolderDir(), new_name);
	snprintf(filename, std::size(filename), "%s\\%s.ini", GetFolderDir(), lpFolder->m_lpTitle);
	bool retval = winui_move_file_utf8(filename, new_filename);

	if (retval)
	{
		TryRenameCustomFolderIni(lpFolder, lpFolder->m_lpTitle, new_name);
		free(lpFolder->m_lpTitle);
		lpFolder->m_lpTitle = (char *)malloc(strlen(new_name) + 1);
		strcpy(lpFolder->m_lpTitle, new_name);
	}
	else
		ErrorMessageBox("Error while renaming custom file %s to %s", filename, new_filename);

	return retval;
}

void AddToCustomFolder(LPTREEFOLDER lpFolder, int driver_index)
{
	if ((lpFolder->m_dwFlags & F_CUSTOM) == 0)
	{
		ErrorMessageBox("Unable to add game to non-custom folder");
		return;
	}

	if (TestBit(lpFolder->m_lpGameBits, driver_index) == 0)
	{
		AddGame(lpFolder, driver_index);

		if (TrySaveExtraFolder(lpFolder) == false)
			RemoveGame(lpFolder, driver_index); 	// undo on error
	}
}

void RemoveFromCustomFolder(LPTREEFOLDER lpFolder, int driver_index)
{
	if ((lpFolder->m_dwFlags & F_CUSTOM) == 0)
	{
		ErrorMessageBox("Unable to remove game from non-custom folder");
		return;
	}

	if (TestBit(lpFolder->m_lpGameBits, driver_index) != 0)
	{
		RemoveGame(lpFolder, driver_index);

		if (TrySaveExtraFolder(lpFolder) == false)
			AddGame(lpFolder, driver_index); // undo on error
	}
}

bool TrySaveExtraFolder(LPTREEFOLDER lpFolder)
{
	char fname[MAX_PATH];
	bool error = false;
	LPTREEFOLDER root_folder = NULL;
	LPEXFOLDERDATA extra_folder = NULL;

	for (int i = 0; i < numExtraFolders; i++)
	{
		if (ExtraFolderData[i]->m_nFolderId == lpFolder->m_nFolderId)
		{
			root_folder = lpFolder;
			extra_folder = ExtraFolderData[i];
			break;
		}

		if (lpFolder->m_nParent >= 0 && ExtraFolderData[i]->m_nFolderId == treeFolders[lpFolder->m_nParent]->m_nFolderId)
		{
			root_folder = treeFolders[lpFolder->m_nParent];
			extra_folder = ExtraFolderData[i];
			break;
		}
	}

	if (extra_folder == NULL || root_folder == NULL)
	{
		ErrorMessageBox("Error finding custom file name to save");
		return false;
	}

	snprintf(fname, std::size(fname), "%s\\%s.ini", GetFolderDir(), extra_folder->m_szTitle);
	wchar_t *temp = win_wstring_from_utf8(GetFolderDir());
	CreateDirectory(temp, NULL);
	free(temp);  	
	FILE *f = fopen(fname, "w");

	if (f == NULL)
		error = true;
	else
	{
		TREEFOLDER *folder_data;

		fprintf(f, "[FOLDER_SETTINGS]\n");
		
		// negative values for icons means it's custom, so save 'em
		if (extra_folder->m_nIconId < 0)
			fprintf(f, "RootFolderIcon %s\n", ExtraFolderIcons[(-extra_folder->m_nIconId) - ICON_MAX]);

		if (extra_folder->m_nSubIconId < 0)
			fprintf(f, "SubFolderIcon %s\n", ExtraFolderIcons[(-extra_folder->m_nSubIconId) - ICON_MAX]);

		/* need to loop over all our TREEFOLDERs--first the root one, then each child.
		   start with the root */
		folder_data = root_folder;
		fprintf(f, "\n[ROOT_FOLDER]\n");

		for (int i = 0; i < driver_list::total(); i++)
		{
			if (TestBit(folder_data->m_lpGameBits, i))
				fprintf(f, "%s\n", GetDriverGameName(i));
		}

		/* look through the custom folders for ones with our root as parent */
		for (int j = 0; j < numFolders; j++)
		{
			folder_data = treeFolders[j];

			if (folder_data->m_nParent >= 0 && treeFolders[folder_data->m_nParent] == root_folder)
			{
				fprintf(f, "\n[%s]\n", folder_data->m_lpTitle);

				for (int i = 0; i < driver_list::total(); i++)
				{
					if (TestBit(folder_data->m_lpGameBits, i))
						fprintf(f, "%s\n", GetDriverGameName(i));
				}
			}
		}

		fclose(f);
	}

	if (error)
		ErrorMessageBox("Error while saving custom file %s", fname);

	return !error;
}

HIMAGELIST GetTreeViewIconList(void)
{
	return hTreeSmall;
}

// 修改的 代码来源 (加斯顿90)
/****************************************************************************/
void CreateCOLLECTIONFolders(int parent_index)
{
	int jj;
	int nGames = GetNumGames();
	LPTREEFOLDER lpFolder = treeFolders[parent_index];
    LPTREEFOLDER lpCapcom, lpPGM, lpNanco, lpTaito, lpKonami, lpSega, lpMisc, lpMidway, lpToaplan, lpNintendo, lpDataEast, lpSeta;

	// no games in top level folder
	SetAllBits(lpFolder->m_lpGameBits,FALSE);

	// create our two subfolders
    lpCapcom = NewFolder("Capcom", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpPGM = NewFolder("PGM", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
    lpNanco = NewFolder("Nanco", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpTaito = NewFolder("Taito", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpKonami = NewFolder("Konami", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
    lpSega = NewFolder("Sega", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
	lpMisc = NewFolder("Misc", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
    lpMidway = NewFolder("Midway", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
    lpToaplan = NewFolder("Toaplan", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
    lpNintendo = NewFolder("Nintendo", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
    lpDataEast = NewFolder("DataEast", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));
    lpSeta = NewFolder("Seta", next_folder_id++, parent_index, IDI_FOLDER, GetFolderFlags(numFolders));

	AddFolder(lpCapcom);
	AddFolder(lpPGM);
	AddFolder(lpNanco);
	AddFolder(lpTaito);
	AddFolder(lpKonami);	
	AddFolder(lpSega);
	AddFolder(lpMisc);
	AddFolder(lpMidway);
	AddFolder(lpToaplan);
	AddFolder(lpNintendo);
	AddFolder(lpDataEast);	
	AddFolder(lpSeta);	

	for (jj = 0; jj < nGames; jj++)
	{
		const char *s = GetDriverFileName(jj);

		if (s == NULL || s[0] == '\0')
			continue;
 
        // Capcom
		if (!strcmp("1942.cpp", s))			    AddGame(lpCapcom, jj);
		if (!strcmp("1943.cpp", s))		        AddGame(lpCapcom, jj);
		if (!strcmp("alien.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("bionicc.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("supduck.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("blktiger.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("blktiger_ms.cpp", s))	    AddGame(lpCapcom, jj);
		if (!strcmp("cbasebal.cpp", s))		    AddGame(lpCapcom, jj);
		if (!strcmp("commando.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("cps1.cpp", s))			    AddGame(lpCapcom, jj);
		if (!strcmp("cps1hb.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("cps1bl_5205.cpp", s))	    AddGame(lpCapcom, jj);
		if (!strcmp("cps1bl_pic.cpp", s))	    AddGame(lpCapcom, jj);
		if (!strcmp("kenseim.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("cps2.cpp", s))		        AddGame(lpCapcom, jj);
		if (!strcmp("cps2hb.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("cps3.cpp", s))			    AddGame(lpCapcom, jj);
		if (!strcmp("egghunt.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("exedexes.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("fcrash.cpp", s))		    AddGame(lpCapcom, jj);
		if (!strcmp("gng.cpp", s))			    AddGame(lpCapcom, jj);
		if (!strcmp("gunsmoke.cpp", s))		    AddGame(lpCapcom, jj);
		if (!strcmp("higemaru.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("lastduel.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("lwings.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("mitchell.cpp", s))		    AddGame(lpCapcom, jj);
		if (!strcmp("psrockman.cpp", s))	    AddGame(lpCapcom, jj);
		if (!strcmp("sf.cpp", s))			    AddGame(lpCapcom, jj);
		if (!strcmp("sidearms.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("sonson.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("srumbler.cpp", s))		    AddGame(lpCapcom, jj);
		if (!strcmp("tigeroad.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("vulgus.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("tvcapcom.cpp", s))			AddGame(lpCapcom, jj);
		if (!strcmp("instantm.cpp", s))			AddGame(lpCapcom, jj);

        // PGM
		if (!strcmp("cabaret.cpp", s))		    AddGame(lpPGM, jj);
		if (!strcmp("dunhuang.cpp", s))		    AddGame(lpPGM, jj);
		if (!strcmp("goldstar.cpp", s))			AddGame(lpPGM, jj);
		if (!strcmp("funtech.cpp", s))			AddGame(lpPGM, jj);
		if (!strcmp("jackie.cpp", s))			AddGame(lpPGM, jj);
		if (!strcmp("igspoker.cpp", s))			AddGame(lpPGM, jj);
		if (!strcmp("igs009.cpp", s))			AddGame(lpPGM, jj);
		if (!strcmp("igs011.cpp", s))		    AddGame(lpPGM, jj);
		if (!strcmp("igs017.cpp", s))			AddGame(lpPGM, jj);
		if (!strcmp("igs_fear.cpp", s))			AddGame(lpPGM, jj);
		if (!strcmp("igs_m027.cpp", s))			AddGame(lpPGM, jj);
		if (!strcmp("igs_m036.cpp", s))			AddGame(lpPGM, jj);
		if (!strcmp("iqblock.cpp", s))		    AddGame(lpPGM, jj);
		if (!strcmp("lordgun.cpp", s))		    AddGame(lpPGM, jj);
		if (!strcmp("pgm.cpp", s))			    AddGame(lpPGM, jj);
		if (!strcmp("pgm2.cpp", s))			    AddGame(lpPGM, jj);
		if (!strcmp("pgm3.cpp", s))		        AddGame(lpPGM, jj);
		if (!strcmp("spoker.cpp", s))			AddGame(lpPGM, jj);

        // Nanco
		if (!strcmp("20pacgal.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("30test.cpp", s))           AddGame(lpNanco, jj);
		if (!strcmp("baraduke.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("cgang.cpp", s))            AddGame(lpNanco, jj);
		if (!strcmp("cswat.cpp", s))            AddGame(lpNanco, jj);
		if (!strcmp("dambustr.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("dangbar.cpp", s))          AddGame(lpNanco, jj);
		if (!strcmp("dkmb.cpp", s))             AddGame(lpNanco, jj);
		if (!strcmp("gal3.cpp", s))             AddGame(lpNanco, jj);
		if (!strcmp("galaga.cpp", s))           AddGame(lpNanco, jj);
		if (!strcmp("galaxian.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("galaxold.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("gaplus.cpp", s))           AddGame(lpNanco, jj);
		if (!strcmp("kungfur.cpp", s))          AddGame(lpNanco, jj);
		if (!strcmp("mappy.cpp", s))            AddGame(lpNanco, jj);
		if (!strcmp("namcofl.cpp", s))          AddGame(lpNanco, jj);
		if (!strcmp("namcona1.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("namconb1.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("namcond1.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("namcops2.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("namcos1.cpp", s))          AddGame(lpNanco, jj);
		if (!strcmp("namcos1b.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("puckman.cpp", s))          AddGame(lpNanco, jj);
		if (!strcmp("mspacman.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("multipac.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("maketrax.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("pengo.cpp", s))            AddGame(lpNanco, jj);
		if (!strcmp("namcos10.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("namcos11.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("namcos12.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("namcos2.cpp", s))          AddGame(lpNanco, jj);
		if (!strcmp("pacland.cpp", s))          AddGame(lpNanco, jj);
		if (!strcmp("namcos21.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("namcos21_de.cpp", s))      AddGame(lpNanco, jj);
		if (!strcmp("namcos21_c67.cpp", s))     AddGame(lpNanco, jj);
		if (!strcmp("namcos22.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("namcos23.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("namcos86.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("polepos.cpp", s))          AddGame(lpNanco, jj);
		if (!strcmp("rallyx.cpp", s))           AddGame(lpNanco, jj);
		if (!strcmp("rbowlorama.cpp", s))       AddGame(lpNanco, jj);
		if (!strcmp("shootaway2.cpp", s))       AddGame(lpNanco, jj);
		if (!strcmp("skykid.cpp", s))           AddGame(lpNanco, jj);
		if (!strcmp("sweetland.cpp", s))        AddGame(lpNanco, jj);
		if (!strcmp("tankbatt.cpp", s))         AddGame(lpNanco, jj);
		if (!strcmp("tceptor.cpp", s))          AddGame(lpNanco, jj);
		if (!strcmp("toypop.cpp", s))           AddGame(lpNanco, jj);
		if (!strcmp("turrett.cpp", s))          AddGame(lpNanco, jj);
		if (!strcmp("wacky_gator.cpp", s))      AddGame(lpNanco, jj);
		if (!strcmp("warpwarp.cpp", s))         AddGame(lpNanco, jj);

        // Taito
		if (!strcmp("2mindril.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("40love.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("arkanoid.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("ashnojoe.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("asuka.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("bigevglf.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("bingowav.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("bking.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("bublbobl.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("buggychl.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("cchance.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("chaknpop.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("champbwl.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("changela.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("crbaloon.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("cyclemb.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("darius.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("exzisus.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("fgoal.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("flstory.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("galastrm.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("gladiatr.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("grchamp.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("groundfx.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("gsword.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("gunbustr.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("halleys.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("invqix.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("jollyjgr.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("ksayakyu.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("ikage.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("lsasquad.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("marinedt.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("kikikai.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("minivadr.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("missb2.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("mlanding.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("msisaac.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("ninjaw.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("nycaptor.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("opwolf.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("othunder.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("pitnrun.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("qix.cpp", s))			    AddGame(lpTaito, jj);
		if (!strcmp("rbisland.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("rastan.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("retofinv.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("rollrace.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("sbmjb.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("sbowling.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("scyclone.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("slapshot.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("spdheat.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("ssrj.cpp", s))			    AddGame(lpTaito, jj);
		if (!strcmp("superchs.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("superqix.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("taito_b.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("taito_f2.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("taito_f3.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("taito_h.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("taito_l.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("taito_x.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("taito_z.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("taito_o.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("taitoair.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("taitogn.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("taitojc.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("taitopjc.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("taitosj.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("tnzs.cpp", s))			    AddGame(lpTaito, jj);
		if (!strcmp("topspeed.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("tsamurai.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("undrfire.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("volfied.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("warriorb.cpp", s))			AddGame(lpTaito, jj);
		if (!strcmp("wgp.cpp", s))			    AddGame(lpTaito, jj);
		if (!strcmp("wyvernf0.cpp", s))			AddGame(lpTaito, jj);
	    if (!strcmp("lkage.cpp", s))			AddGame(lpTaito, jj);

        // Konami
		if (!strcmp("88games.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("ajax.cpp", s))			    AddGame(lpKonami, jj);
		if (!strcmp("aliens.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("asterix.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("battlnts.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("bishi.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("bladestl.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("blockhl.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("bottom9.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("chqflag.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("circusc.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("cobra.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("combatsc.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("contra.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("crimfght.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("dbz.cpp", s))			    AddGame(lpKonami, jj);
		if (!strcmp("ddribble.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("divebomb.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("djmain.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("fastfred.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("fastlane.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("finalizr.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("firebeat.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("flkatck.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("gberet.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("gijoe.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("gradius3.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("gticlub.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("gyruss.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("hcastle.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("hexion.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("hornet.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("hyperspt.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("ironhors.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("jackal.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("jailbrek.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("junofrst.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("konamigq.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("konamigs.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("konamigv.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("konamigx.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("konamim2.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("konmedal.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("konmedal68k.cpp", s))		AddGame(lpKonami, jj);
		if (!strcmp("ksys573.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("labyrunr.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("lethal.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("mainevt.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("megazone.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("mikie.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("mogura.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("moo.cpp", s))			    AddGame(lpKonami, jj);
		if (!strcmp("mystwarr.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("nemesis.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("nwk-tr.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("overdriv.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("pandoras.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("parodius.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("pingpong.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("piratesh.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("plygonet.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("pooyan.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("qdrmfgp.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("quickpick5.cpp", s))	    AddGame(lpKonami, jj);
		if (!strcmp("rockrage.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("rocnrope.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("rollerg.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("rungun.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("sbasketb.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("scobra.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("scotrsht.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("scramble.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("shaolins.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("simpsons.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("spy.cpp", s))			    AddGame(lpKonami, jj);
		if (!strcmp("surpratk.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("thunderx.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("timeplt.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("tmnt.cpp", s))			    AddGame(lpKonami, jj);
		if (!strcmp("tp84.cpp", s))			    AddGame(lpKonami, jj);
		if (!strcmp("trackfld.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("tutankhm.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("twin16.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("twinkle.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("ultrsprt.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("ultraman.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("vendetta.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("wecleman.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("xexex.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("yiear.cpp", s))			AddGame(lpKonami, jj);
		if (!strcmp("zr107.cpp", s))			AddGame(lpKonami, jj);

        // Sega
		if (!strcmp("angelkds.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("blockade.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("calorie.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("coolridr.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("deniam.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("dotrikun.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("kopunch.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segabb.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("megadriv.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("megadriv_acbl.cpp", s))	AddGame(lpSega, jj);
		if (!strcmp("megaplay.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("megatech.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("calcune.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("model1.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("s32comm.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("model2.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("model3.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("naomi.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("dc_atomiswave.cpp", s))	AddGame(lpSega, jj);
		if (!strcmp("puckpkmn.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segac2.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segae.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("sms.cpp", s))	            AddGame(lpSega, jj);
		if (!strcmp("segag80r.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segag80v.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segahang.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segajw.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segaorun.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segas16a.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segas16b.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segas16b_isgsm.cpp", s))	AddGame(lpSega, jj);
		if (!strcmp("segas18.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segas18_astormbl.cpp", s))	AddGame(lpSega, jj);
		if (!strcmp("segas24.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segas32.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segaxbd.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("segaybd.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("sg1000a.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("stactics.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("stv.cpp", s))			    AddGame(lpSega, jj);
		if (!strcmp("suprloco.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("system1.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("system16.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("timetrv.cpp", s))		    AddGame(lpSega, jj);
		if (!strcmp("turbo.cpp", s))		    AddGame(lpSega, jj);
		if (!strcmp("vicdual.cpp", s))			AddGame(lpSega, jj);
		if (!strcmp("zaxxon.cpp", s))			AddGame(lpSega, jj);

        // lpMisc
		if (!strcmp("39in1.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("4enraya.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("5clown.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("acefruit.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("alinvade.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("amspdwy.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("amusco.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("apple2.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("artmagic.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("astrcorp.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("attckufo.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("avt.cpp", s))			    AddGame(lpMisc, jj);
		if (!strcmp("aztarac.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("beaminv.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("beezer.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("cardline.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("carrera.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("cave.cpp", s))			    AddGame(lpMisc, jj);
		if (!strcmp("cavepc.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("cv1k.cpp", s))			    AddGame(lpMisc, jj);
		if (!strcmp("cb2001.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("cdi.cpp", s))			    AddGame(lpMisc, jj);
		if (!strcmp("chameleonrx1.cpp", s))	    AddGame(lpMisc, jj);
		if (!strcmp("chance32.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("clpoker.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("cocoloco.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("coinmstr.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("comebaby.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("coolpool.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("megaphx.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("corona.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("crystal.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("trivrus.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("cubeqst.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("cybertnk.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("dcheese.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("dfruit.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("dgpix.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("discoboy.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("dominob.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("dorachan.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("dreamwld.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("dwarfd.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("dynadice.cpp", s))		    AddGame(lpMisc, jj);
		if (!strcmp("efdt.cpp", s))			    AddGame(lpMisc, jj);
		if (!strcmp("efg8080.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("epos.cpp", s))			    AddGame(lpMisc, jj);
		if (!strcmp("esd16.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("esripsys.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("ettrivia.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("flipjack.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("flower.cpp", s))		    AddGame(lpMisc, jj);
		if (!strcmp("fortecar.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("freekick.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("funkball.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("galaxi.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("galgame.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("gei.cpp", s))			    AddGame(lpMisc, jj);
		if (!strcmp("gluck2.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("goldnpkr.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("good.cpp", s))			    AddGame(lpMisc, jj);
		if (!strcmp("gotcha.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("gumbo.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("gunpey.cpp", s))	        AddGame(lpMisc, jj);
		if (!strcmp("highvdeo.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("homedata.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("hotblock.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("hotchili.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("imolagp.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("jackpool.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("jankenmn.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("joystand.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("jubilee.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("kingpin.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("krokha.cpp", s))		    AddGame(lpMisc, jj);
		if (!strcmp("kurukuru.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("kyugo.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("ladyfrog.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("laserbas.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("lependu.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("lethalj.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("limenko.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("ltcasino.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("magic10.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("magicfly.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("magtouch.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("majorpkr.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("malzak.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("mcatadv.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("meyc8080.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("meyc8088.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("micro3d.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("miniboy7.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("mirax.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("mjsenpu.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("mole.cpp", s))			    AddGame(lpMisc, jj);
		if (!strcmp("mosaic.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("mpu12wbk.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("murogem.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("murogmbl.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("news.cpp", s))			    AddGame(lpMisc, jj);
		if (!strcmp("norautp.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("oneshot.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("onetwo.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("othello.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("pachifev.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("pasha2.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("pass.cpp", s))			    AddGame(lpMisc, jj);
		if (!strcmp("photon.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("photon2.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("pipeline.cpp", s))		    AddGame(lpMisc, jj);
		if (!strcmp("pkscram.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("policetr.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("polyplay.cpp", s))	        AddGame(lpMisc, jj);
		if (!strcmp("quizo.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("quizpun2.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("rbmk.cpp", s))			    AddGame(lpMisc, jj);
		if (!strcmp("re900.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("sanremo.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("sealy_fr.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("sfbonus.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("shangkid.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("skimaxx.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("skyarmy.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("skylncr.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("sliver.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("smotor.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("smsmcorp.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("sothello.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("special_gambl.cpp", s))	AddGame(lpMisc, jj);
		if (!strcmp("sprcros2.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("ssingles.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("sstrangr.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("statriv2.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("stuntair.cpp", s))		    AddGame(lpMisc, jj);
		if (!strcmp("superga2.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("supertnk.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("tapatune.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("tattack.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("taxidriv.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("thedeep.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("tickee.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("triviaquiz.cpp", s))		AddGame(lpMisc, jj);
		if (!strcmp("truco.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("trucocl.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("trvmadns.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("trvquest.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("ttchamp.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("tugboat.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("tvg01.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("umipoker.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("unkhorse.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("usgames.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("vamphalf.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("vectrex.cpp", s))	        AddGame(lpMisc, jj);
		if (!strcmp("video21.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("vroulet.cpp", s))			AddGame(lpMisc, jj);
		if (!strcmp("xyonix.cpp", s))			AddGame(lpMisc, jj);

        // Midway
		if (!strcmp("astrocde.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("atlantis.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("balsente.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("gridlee.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("mcr.cpp", s))			    AddGame(lpMidway, jj);
		if (!strcmp("mcr3.cpp", s))				AddGame(lpMidway, jj);
		if (!strcmp("spyhuntertec.cpp", s)) 	AddGame(lpMidway, jj);
		if (!strcmp("mcr68.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("zwackery.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("midqslvr.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("midtunit.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("midvunit.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("midwunit.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("midxunit.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("midyunit.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("midzeus.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("omegrace.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("seattle.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("sspeedr.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("tmaster.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("vegas.cpp", s))			AddGame(lpMidway, jj);
		if (!strcmp("wmg.cpp", s))			    AddGame(lpMidway, jj);
		if (!strcmp("williams.cpp", s))			AddGame(lpMidway, jj);

        // Toaplan
		if (!strcmp("mjsister.cpp", s))			AddGame(lpToaplan, jj);
		if (!strcmp("slapfght.cpp", s))			AddGame(lpToaplan, jj);
		if (!strcmp("snowbros.cpp", s))			AddGame(lpToaplan, jj);
		if (!strcmp("toaplan1.cpp", s))			AddGame(lpToaplan, jj);
		if (!strcmp("toaplan2.cpp", s))			AddGame(lpToaplan, jj);
		if (!strcmp("twincobr.cpp", s))			AddGame(lpToaplan, jj);
		if (!strcmp("wardner.cpp", s))			AddGame(lpToaplan, jj);

        // Nintendo
		if (!strcmp("cham24.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("dkong.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("mario.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("mmagic.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("multigam.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("n8080.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("nss.cpp", s))			    AddGame(lpNintendo, jj);
		if (!strcmp("playch10.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("popeye.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("punchout.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("famibox.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("sfcbox.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("snesb51.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("snesb.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("spacefb.cpp", s))			AddGame(lpNintendo, jj);
		if (!strcmp("vsnes.cpp", s))			AddGame(lpNintendo, jj);

        // DataEast
	    if (!strcmp("actfancr.cpp", s))	        AddGame(lpDataEast, jj);
		if (!strcmp("astrof.cpp", s))		    AddGame(lpDataEast, jj);
		if (!strcmp("backfire.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("battlera.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("boogwing.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("brkthru.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("btime.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("bwing.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("cbuster.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("chanbara.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("cninja.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("cntsteer.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("compgolf.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("darkseal.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("dassault.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("dblewing.cpp", s))		    AddGame(lpDataEast, jj);
		if (!strcmp("dec0.cpp", s))			    AddGame(lpDataEast, jj);
		if (!strcmp("dec8.cpp", s))			    AddGame(lpDataEast, jj);
		if (!strcmp("deco_ld.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("deco_mlc.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("deco156.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("deco32.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("decocass.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("deshoros.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("dietgo.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("dreambal.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("exprraid.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("firetrap.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("funkyjet.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("karnov.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("kchamp.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("kingobox.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("lemmings.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("liberate.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("madalien.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("madmotor.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("metlclsh.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("mirage.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("pcktgal.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("pktgaldx.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("progolf.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("rohga.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("shootout.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("sidepckt.cpp", s))		    AddGame(lpDataEast, jj);
		if (!strcmp("simpl156.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("sshangha.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("stadhero.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("supbtime.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("tryout.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("tumbleb.cpp", s))			AddGame(lpDataEast, jj);
		if (!strcmp("vaportra.cpp", s))			AddGame(lpDataEast, jj);

        // Seta
		if (!strcmp("zn.cpp", s))			    AddGame(lpSeta, jj);
		if (!strcmp("znmcu.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("cat702.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("acommand.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("cultures.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("ddealer.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("jalmah.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("macrossp.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("nmk16.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("powerins.cpp", s))	        AddGame(lpSeta, jj);
		if (!strcmp("quizdna.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("quizpani.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("aleck64.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("hanaawas.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("jclub2.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("macs.cpp", s))			    AddGame(lpSeta, jj);
		if (!strcmp("seta.cpp", s))			    AddGame(lpSeta, jj);
		if (!strcmp("seta2.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("speedatk.cpp", s))	        AddGame(lpSeta, jj);
		if (!strcmp("speglsht.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("srmp2.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("srmp5.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("srmp6.cpp", s))	        AddGame(lpSeta, jj);
		if (!strcmp("ssv.cpp", s))			    AddGame(lpSeta, jj);
		if (!strcmp("simple_st0016.cpp", s))	AddGame(lpSeta, jj);
		if (!strcmp("thedealr.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("airraid.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("banprestoms.cpp", s))		AddGame(lpSeta, jj);
		if (!strcmp("bloodbro.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("cabal.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("darkmist.cpp", s))	        AddGame(lpSeta, jj);
		if (!strcmp("dcon.cpp", s))			    AddGame(lpSeta, jj);
		if (!strcmp("deadang.cpp", s))	        AddGame(lpSeta, jj);
		if (!strcmp("dynduke.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("feversoc.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("goal92.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("goodejan.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("kncljoe.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("legionna.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("seicupbl.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("metlfrzr.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("mustache.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("panicr.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("raiden.cpp", s))		    AddGame(lpSeta, jj);
		if (!strcmp("raiden_ms.cpp", s))		AddGame(lpSeta, jj);
		if (!strcmp("raiden2.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("r2dx_v33.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("seibuspi.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("sengokmj.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("stfight.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("toki.cpp", s))			    AddGame(lpSeta, jj);
		if (!strcmp("toki_ms.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("wiz.cpp", s))			    AddGame(lpSeta, jj);
		if (!strcmp("airbustr.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("djboy.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("expro02.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("galpanic.cpp", s))	        AddGame(lpSeta, jj);
		if (!strcmp("galpanic_ms.cpp", s))	    AddGame(lpSeta, jj);
		if (!strcmp("galpani2.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("galpani3.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("hvyunit.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("jchan.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("kaneko16.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("sandscrp.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("suprnova.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("aerofgt.cpp", s))	        AddGame(lpSeta, jj);
		if (!strcmp("crshrace.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("f1gp.cpp", s))			    AddGame(lpSeta, jj);
		if (!strcmp("fromance.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("fromanc2.cpp", s))	        AddGame(lpSeta, jj);
		if (!strcmp("gstriker.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("inufuku.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("ojankohs.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("pipedrm.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("rpunch.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("suprslam.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("tail2nos.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("taotaido.cpp", s))	        AddGame(lpSeta, jj);
		if (!strcmp("welltris.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("fuukifg2.cpp", s))	        AddGame(lpSeta, jj);
		if (!strcmp("fuukifg3.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("hyprduel.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("metro.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("rabbit.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("tmmjprd.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("psikyo.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("psikyo4.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("psikyosh.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("aeroboto.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("argus.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("bestleag.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("bigstrkb.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("blueprnt.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("bnstars.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("cischeat.cpp", s))	        AddGame(lpSeta, jj);
		if (!strcmp("citycon.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("ddayjlc.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("exerion.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("fcombat.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("ginganin.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("homerun.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("megasys1.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("momoko.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("ms32.cpp", s))	            AddGame(lpSeta, jj);
		if (!strcmp("psychic5.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("pturn.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("skyfox.cpp", s))			AddGame(lpSeta, jj);
		if (!strcmp("tetrisp2.cpp", s))	        AddGame(lpSeta, jj);
	}

}

/****************************************************************************/

int GetTreeViewIconIndex(int icon_id)
{
	if (icon_id < 0)
		return -icon_id;

	for (int i = 0; i < std::size(treeIconNames); i++)
	{
		if (icon_id == treeIconNames[i].nResourceID)
			return i;
	}

	return -1;
}

static bool FilterAvailable(int driver_index)
{
	if (!DriverUsesRoms(driver_index))
	{
		if (GetDisplayNoRomsGames())
			return true;
		else
			return false;
	}

	return IsAuditResultYes(GetRomAuditResults(driver_index));
}
