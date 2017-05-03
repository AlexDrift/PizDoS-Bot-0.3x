void onFootUpdateAtNormalPos();
void onFootUpdateFollow(PLAYERID followID);
void onFootUpdateFollow1(PLAYERID followID);
void onFootUpdateFollow2(PLAYERID followID);
void onFootUpdateFollow3(PLAYERID followID);
void onFootUpdateFollow4(PLAYERID followID);
void onFootUpdateFollow5(PLAYERID followPlayerID);
void inCarUpdateFollow(PLAYERID followID, VEHICLEID withVehicleID);
void onFootUpdateFollow5(PLAYERID followID);

int sampConnect(char *szHostname, int iPort, char *szNickname, char *szPassword, RakClientInterface *pRakClient);
void sampDisconnect(int iTimeout);
void sampRequestClass(int iClass);
void sampSmth();
void sampReg();
void sampFakeNpc();
void sampSpawn();
void sampSpam();
void sendServerCommand(char *szCommand);
void sendChat(char *szMessage);
void sendChat2(char *szMessage);
void sendRconCommand(char *szRCONCmd, int iIsLogin);
void SendScmEvent(int iEventType, DWORD dwParam1, DWORD dwParam2, DWORD dwParam3);
void sendDialogResponse(WORD wDialogID, BYTE bButtonID, WORD wListBoxItem, char *szInputResp);
void test24();
void test();
void sampChanger(int iClass);

int isPlayerConnected(PLAYERID iPlayerID);
int getPlayerID(char *szPlayerName);
char *getPlayerName(PLAYERID iPlayerID);
int getPlayerPos(PLAYERID iPlayerID, float *fPos);

PLAYERID getPlayerIDFromPlayerName(char *szName);
unsigned short getPlayerCount();

const struct vehicle_entry *gta_vehicle_get_by_id ( int id );
