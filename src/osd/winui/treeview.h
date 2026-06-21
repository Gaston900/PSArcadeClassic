// license:BSD-3-Clause
// For licensing and usage information, read docs/release/winui_license.txt

#ifndef TREEVIEW_H
#define TREEVIEW_H

#define MAX_EXTRA_FOLDERS 			256
#define MAX_EXTRA_SUBFOLDERS 		256
#define ICON_MAX 		std::size(treeIconNames)

/***************************************************************************
    Folder And Filter Definitions
 ***************************************************************************/

typedef struct
{
	const char *m_lpTitle; // Folder Title
	const char *short_name;  // for saving in the .ini
	UINT        m_nFolderId; // ID
	UINT        m_nIconId; // if >= 0, resource id of icon (IDI_xxx), otherwise index in image list
	UINT        m_nIconId2; // icon for subfolders
	DWORD       m_dwUnset; // Excluded filters
	DWORD       m_dwSet;   // Implied filters
	BOOL        m_process;  // Cached y/n
	void        (*m_pfnCreateFolders)(int parent_index); // Constructor for special folders
	bool        (*m_pfnQuery)(int nDriver);             // Query function
	bool        m_bExpectedResult;                      // Expected query result
} FOLDERDATA, *LPFOLDERDATA;

typedef const FOLDERDATA *LPCFOLDERDATA;

typedef struct
{
	DWORD m_dwFilterType;				/* Filter value */
	DWORD m_dwCtrlID;					/* Control ID that represents it */
	bool (*m_pfnQuery)(int nDriver);	/* Query function */
	bool m_bExpectedResult;				/* Expected query result */
} FILTER_ITEM, *LPFILTER_ITEM;

typedef const FILTER_ITEM *LPCFILTER_ITEM;

// TreeView structures - keep the complete list including the currently unused ones
enum
{
	FOLDER_NONE = 0,
	FOLDER_ALL,
	FOLDER_AVAIL,
	FOLDER_ARCADE,
	FOLDER_BIOS,
	FOLDER_CLONES,
	FOLDER_CPU,
	FOLDER_IMP,
	FOLDER_DUMP,
	FOLDER_FPS,
	FOLDER_HARDDISK,
	FOLDER_HORI,
	FOLDER_LIGHTGUN,
	FOLDER_MANU,
	FOLDER_MECH,
	FOLDER_MODIFIED,
	FOLDER_MOUSE,
	FOLDER_NONMECH,
	FOLDER_NW,
	FOLDER_PARENTS,
	FOLDER_RASTER,
	FOLDER_RESOL,
	FOLDER_SAMPLES,
	FOLDER_SAVESTATE,
	FOLDER_SCREENS,
	FOLDER_SOUND,
	FOLDER_SOURCE,
	FOLDER_STEREO,
	FOLDER_TRACKBALL,
	FOLDER_UNAVAIL,
	FOLDER_VECTOR,
	FOLDER_VERT,
	FOLDER_W,
	FOLDER_YEAR,
// 修改的 代码来源 (加斯顿90)
/******************/
    FOLDER_CONSOLE,
	FOLDER_COLLECTION,
/******************/
	MAX_FOLDERS,
};

typedef enum
{
	FI_CLONES        = 0x00000001,
	FI_NW            = 0x00000002,
	FI_UNAVAIL       = 0x00000004,
	FI_VECTOR        = 0x00000008,
	FI_RASTER        = 0x00000010,
	FI_PARENTS       = 0x00000020,
	FI_W             = 0x00000040,
	FI_AVAIL         = 0x00000080,
	FI_HORI          = 0x00001000,
	FI_VERT          = 0x00002000,
	FI_MECH          = 0x00004000,
	FI_MASK          = 0x0000FFFF,
	FI_INIEDIT       = 0x00010000, // There is an .ini that can be edited.
	FI_CUSTOM        = 0x01000000  // for current .ini custom folders
} FOLDERFLAG;

typedef struct
{
	char       *m_lpTitle;        // String contains the folder name
	wchar_t    *m_lptTitle;       // String contains the folder name as wchar_t*
	UINT        m_nFolderId;      // Index / Folder ID number
	int         m_nParent;        // Parent folder index in treeFolders[]
	int         m_nIconId;        // negative icon index into the ImageList, or IDI_xxx resource id
	DWORD       m_dwFlags;        // Misc flags
	LPBITS      m_lpGameBits;     // Game bits, represent game indices
} TREEFOLDER, *LPTREEFOLDER;

typedef struct
{
	char        m_szTitle[64];    // Folder Title
	UINT        m_nFolderId;      // ID
	int         m_nParent;        // Parent Folder index in treeFolders[]
	DWORD       m_dwFlags;        // Flags - Customizable and Filters
	int         m_nIconId;        // negative icon index into the ImageList, or IDI_xxx resource id
	int         m_nSubIconId;     // negative icon index into the ImageList, or IDI_xxx resource id
} EXFOLDERDATA, *LPEXFOLDERDATA;

typedef struct
{
	int nResourceID;
	const char* lpName;
} TREEICON;

void FreeFolders(void);
void ResetFilters(void);
void InitTree(LPCFOLDERDATA lpFolderData, LPCFILTER_ITEM lpFilterList);
void SetCurrentFolder(LPTREEFOLDER lpFolder);
UINT GetCurrentFolderID(void);
LPTREEFOLDER GetCurrentFolder(void);
int GetNumFolders(void);
LPTREEFOLDER GetFolder(UINT nFolder);
LPTREEFOLDER GetFolderByID(UINT nID);
LPTREEFOLDER GetFolderByName(int nParentId, const char *pszFolderName);
void AddGame(LPTREEFOLDER lpFolder, UINT nGame);
void RemoveGame(LPTREEFOLDER lpFolder, UINT nGame);
int  FindGame(LPTREEFOLDER lpFolder, int nGame);
void ResetWhichGamesInFolders(void);
LPCFOLDERDATA FindFilter(DWORD folderID);
bool GameFiltered(int nGame, DWORD dwFlags);
bool GetParentFound(int nGame);
LPCFILTER_ITEM GetFilterList(void);
void SetTreeIconSize(HWND hWnd, bool bLarge);
bool GetTreeIconSize(void);
void GetFolders(TREEFOLDER ***folders,int *num_folders);
bool TryRenameCustomFolder(LPTREEFOLDER lpFolder,const char *new_name);
void AddToCustomFolder(LPTREEFOLDER lpFolder,int driver_index);
void RemoveFromCustomFolder(LPTREEFOLDER lpFolder,int driver_index);
HIMAGELIST GetTreeViewIconList(void);
int GetTreeViewIconIndex(int icon_id);
void ResetTreeViewFolders(void);
void SelectTreeViewFolder(int folder_id);

// 修改的 代码来源 (加斯顿90)
/**********************************************/
void CreateCOLLECTIONFolders(int parent_index);
/**********************************************/
#endif
