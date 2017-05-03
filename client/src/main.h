#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // need sum coños and vaginas
#include <windows.h>
#include "../../common/common.h"

#include <nb30.h> 
#pragma comment(lib,"Netapi32.lib")

#include <mmsystem.h> 
#pragma comment(lib,"winmm.lib")

// window stuff
#include <commctrl.h>
#include "resource.h"

// raknet stuff
#include "PacketEnumerations.h"
#include "RakNetworkFactory.h"
#include "RakClientInterface.h"
#include "NetworkTypes.h"
#include "BitStream.h"
#include "StringCompressor.h"

enum eRunModes
{
	RUNMODE_RCON,
	RUNMODE_BARE,
	RUNMODE_STILL,
	RUNMODE_NORMAL,
	RUNMODE_FOLLOWPLAYER,
	RUNMODE_FOLLOWPLAYERSVEHICLE,
	RUNMODE_PLAYROUTES,
	RUNMODE_FOLLOWPLAYER1,
	RUNMODE_FOLLOWPLAYER2,
	RUNMODE_FOLLOWPLAYER3,
	RUNMODE_FOLLOWPLAYER4,
	RUNMODE_FOLLOWPLAYER5,
	DoS,
};

#pragma warning(disable:4996)

#include "samp_netencr.h"
#include "SAMPRPC.h"
#include "SAMP_VER.h"

#include "netgame.h"
#include "netrpc.h"
#include "localplayer.h"
#include "misc_funcs.h"
#include "CVector.h"
#include "math_stuff.h"
#include "rcon.h"

#include "../../tinyxml/tinyxml.h"
#include "sqlite3/sqlite3.h"
#include "console.h"
#include "window.h"
#include "vehplayer.h"
#include "cmds.h"
#include "xmlsets.h"

struct stVehiclePool
{
	int iDoesExist;
	float fPos[3];
	int iModelID;
};

extern int iAreWeConnected, iConnectionRequested, iSpawned, iGameInited;
extern int iReconnectTime;
extern PLAYERID g_myPlayerID;
extern char g_szNickName[32];

extern struct stPlayerInfo playerInfo[MAX_PLAYERS];
extern struct stVehiclePool vehiclePool[MAX_VEHICLES];

extern PLAYERID normalMode_goto;
extern PLAYERID imitateID;

void handleQueries(char *s, int len);
void Log ( char *fmt, ... );
void gen_random(char *s, const int len);
void gen_random1(char *s, const int len);
extern RakClientInterface *pRakClient;


#include "samp.h"
extern SAMP* pSamp;