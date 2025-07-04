/*

            ooo        ooooo       .o.       ooooooooo.   ooooo ooooo      ooo ooooo   ooooo   .oooooo.   
            `88.       .888'      .888.      `888   `Y88. `888' `888b.     `8' `888'   `888'  d8P'  `Y8b  
            888b     d'888      .8"888.      888   .d88'  888   8 `88b.    8   888     888  888      888 
            8 Y88. .P  888     .8' `888.     888ooo88P'   888   8   `88b.  8   888ooooo888  888      888 
            8  `888'   888    .88ooo8888.    888`88b.     888   8     `88b.8   888     888  888      888 
            8    Y     888   .8'     `888.   888  `88b.   888   8       `888   888     888  `88b    d88' 
            o8o        o888o o88o     o8888o o888o  o888o o888o o8o        `8  o888o   o888o  `Y8bood8P'  

*/

/*
    Inclues
*/
#include <a_samp>
#include <streamer>
#include <Pawn.CMD>
#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_iterate>
/*
    DEFINES
*/
#define  AIRDROP_OBJECTS_COUNT 2

static const Float:E_AIRDROP_SPEED = 2.0;
/*
        Forwards
*/
forward AirdropSystemUpdate();
forward OnTimerCollectAirdrop(playerid);

enum{
    SINALIZADOR,
    AIRDROP
}

enum E_AIRDROP_DATA{
    E_AIRDROP_OBJECTS[AIRDROP_OBJECTS_COUNT],
    bool:E_AIRDROP_EXISTS,
    Text3D:E_AIDROP_LABEL,
    E_AIRDROP_MAPICON,
    E_AIRDROP_AREA,
    E_AIRDROP_ZONE,
    Float:E_AIRDROP_POSX,
    Float:E_AIRDROP_POSY,
    Float:E_AIRDROP_POSZ
}

static 
    ServerAirdrop[E_AIRDROP_DATA];

static 
    Player_AirDropTimer[MAX_PLAYERS],
    Iterator:PlayerAirDrop<MAX_PLAYERS>;


/*
                    oooo   oooo   .oooooo.    .oooooo.   oooo    oooo  .oooooo..o
                    `888   `888  d8P'  `Y8b  d8P'  `Y8b  `888   .8P'  d8P'    `Y8
                     888   888  888    888 888      888  888  d8'    Y88bo.     
                     888   888  888    888 888      888  88888[      `"Y8888o.  
                     888   888  888    888 888      888  888`88b.        `"Y88b 
                     888   888  `88b  d88' `88b    d88'  888  `88b.  oo     .d8P 
                    o888o o888o  `Y8bd8P'   `Y8bood8P'  o888o  o888o 8""88888P'  
*/

hook OnPlayerDisconnect(playerid, reason)
{
    if(IsPlayerCollectAidrop(playerid))
        IsPlayerRemoveCollect(playerid);

    return Y_HOOKS_CONTINUE_RETURN_1;
}
hook OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == ServerAirdrop[E_AIRDROP_AREA])
        SendClientMessage(playerid, 0xFF0000FF,"AIRDROP: Voce entrou em uma zona de perigo!");

    return Y_HOOKS_CONTINUE_RETURN_1;
}
hook OnPlayerConnect(playerid)
{
    if(IsAirdropStart())
        GangZoneShowForPlayer(playerid, ServerAirdrop[E_AIRDROP_ZONE], 0xFF000099);

    return Y_HOOKS_CONTINUE_RETURN_1;
}
/*

                    .oooooo.     .oooooo.   ooo        ooooo       .o.       ooooo      ooo oooooooooo.     .oooooo.    .oooooo..o 
                    d8P'  `Y8b   d8P'  `Y8b  `88.       .888'      .888.      `888b.     `8' `888'   `Y8b   d8P'  `Y8b  d8P'    `Y8 
                    888          888      888  888b     d'888      .8"888.      8 `88b.    8   888      888 888      888 Y88bo.      
                    888          888      888  8 Y88. .P  888     .8' `888.     8   `88b.  8   888      888 888      888  `"Y8888o.  
                    888          888      888  8  `888'   888    .88ooo8888.    8     `88b.8   888      888 888      888      `"Y88b 
                    `88b    ooo  `88b    d88'  8    Y     888   .8'     `888.   8       `888   888     d88' `88b    d88' oo     .d8P 
                    `Y8bood8P'   `Y8bood8P'  o8o        o888o o88o     o8888o o8o        `8  o888bood8P'    `Y8bood8P'  8""88888P'  

*/
Command:Airdrop(playerid)
{
    if(IsAirdropStart())
        return SendClientMessage(playerid, 0xFFFFFFFF, "AIRDROP: O evento de airdrop ja foi iniciado");

    new 
        Float:Airdrop_PosX,
        Float:Airdrop_PosY,
        Float:Airdrop_PosZ;

    GetPlayerPos(playerid,Airdrop_PosX,Airdrop_PosY,Airdrop_PosZ);

    AirDropStart(Airdrop_PosX,Airdrop_PosY,Airdrop_PosZ);
    return true;
}
Command:pAirdrop(playerid)
{
    if(!IsAirdropStart() || !IsPlayerInAreaAirDrop(playerid))
        return true;

    if(AirDropTheFloor())
        return SendClientMessage(playerid, 0xFFFFFFFF, "AIRDROP: O airdrop ainda nao caiu no chao");

    if(!IsPlayerInAirdrop(playerid))
        return SendClientMessage(playerid, 0xFFFFFFFF, "AIRDROP: Voce nao esta perto do airdrop");

    if(IsPlayerCollectAidrop(playerid))
        return SendClientMessage(playerid, 0xFFFFFFFF, "AIRDROP: Voce ja esta coletando o airdrop");

    Iter_Add(PlayerAirDrop, playerid);
    Player_AirDropTimer[playerid] = SetTimerEx("OnTimerCollectAirdrop", 60000, false, "i", playerid);

    ApplyAnimation(playerid, "BOMBER", "BOM_PLANT_LOOP", 4.1, 1, 0, 0, 0, 0, 1);
    return true;
}
/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/
static stock IsPlayerCollectAidrop(playerid)
    return (!Iter_Contains(PlayerAirDrop, playerid) ? (false) : (true));


static stock AirDropTheFloor()
    return (IsDynamicObjectMoving(ServerAirdrop[E_AIRDROP_OBJECTS][AIRDROP]) ? (true) : (false));

static stock IsPlayerInAreaAirDrop(playerid)
    return (IsPlayerInAnyDynamicArea(playerid, ServerAirdrop[E_AIRDROP_AREA]) ? (true) : (false));

static stock IsPlayerInAirdrop(playerid)
    return (IsPlayerInRangeOfPoint(playerid, 2.0, ServerAirdrop[E_AIRDROP_POSX], ServerAirdrop[E_AIRDROP_POSY], ServerAirdrop[E_AIRDROP_POSZ]) ? (true) : (false));
    
static stock IsAirdropStart()
    return (ServerAirdrop[E_AIRDROP_EXISTS] ? (true) : (false));

static stock IsPlayerRemoveCollect(playerid){

    KillTimer(Player_AirDropTimer[playerid]);

    Iter_Remove(PlayerAirDrop, playerid);
    return true;
}

static stock AirDropStart(Float:PosX, Float:PosY, Float:PosZ)
{
    ServerAirdrop[E_AIRDROP_EXISTS] = true;
    ServerAirdrop[E_AIRDROP_POSX] = PosX;
    ServerAirdrop[E_AIRDROP_POSY] = PosY;
    ServerAirdrop[E_AIRDROP_POSZ] = PosZ;

    ServerAirdrop[E_AIRDROP_OBJECTS][SINALIZADOR] = CreateDynamicObject(18728,PosX,PosY,PosZ,0.0, 0.0, 0.0);
    ServerAirdrop[E_AIRDROP_OBJECTS][AIRDROP] = CreateDynamicObject(18849,PosX,PosY,PosZ + 100,0.0, 0.0, 0.0);

    MoveDynamicObject(ServerAirdrop[E_AIRDROP_OBJECTS][AIRDROP], PosX, PosY, PosZ + 6.3, E_AIRDROP_SPEED);

    ServerAirdrop[E_AIRDROP_MAPICON] = CreateDynamicMapIcon(PosX, PosY, PosZ, 5, -1, -1, -1, -1, 50000.0, 1);

    ServerAirdrop[E_AIRDROP_ZONE] = GangZoneCreate( PosX-100.0, PosY-100.0, PosX+100.0,  PosY+100.0);

    ServerAirdrop[E_AIRDROP_AREA] = CreateDynamicRectangle(PosX-100.0, PosY-100.0, PosX+100.0,  PosY+100.0, 0, 0);

    GangZoneShowForAll(ServerAirdrop[E_AIRDROP_ZONE], 0xFF000099);

    SetTimer("AirdropSystemUpdate", 46000, false);
    return true;
}

static stock DestroyAirdrop()
{
    if(!IsAirdropStart())
        return true;
    
    DestroyDynamicObject(ServerAirdrop[E_AIRDROP_OBJECTS][AIRDROP]);
    DestroyDynamicObject(ServerAirdrop[E_AIRDROP_OBJECTS][SINALIZADOR]);
    DestroyDynamicMapIcon(ServerAirdrop[E_AIRDROP_MAPICON]);
    DestroyDynamicArea(ServerAirdrop[E_AIRDROP_AREA]);
    GangZoneDestroy(ServerAirdrop[E_AIRDROP_ZONE]);
    DestroyDynamic3DTextLabel(ServerAirdrop[E_AIDROP_LABEL]);
    ServerAirdrop[E_AIRDROP_EXISTS] = false;

    static const Limpar[E_AIRDROP_DATA];
    ServerAirdrop = Limpar;   

    foreach(new i: PlayerAirDrop)
        IsPlayerRemoveCollect(i);

    return true;
}
/*

                    ooooooooo.   ooooo     ooo oooooooooo.  ooooo        ooooo   .oooooo.   
                    `888   `Y88. `888'     `8' `888'   `Y8b `888'        `888'  d8P'  `Y8b  
                    888   .d88'  888       8   888     888  888          888  888          
                    888ooo88P'   888       8   888oooo888'  888          888  888          
                    888          888       8   888    `88b  888          888  888          
                    888          `88.    .8'   888    .88P  888       o  888  `88b    ooo  
                    o888o           `YbodP'    o888bood8P'  o888ooooood8 o888o  `Y8bood8P'  

*/
public AirdropSystemUpdate ()
{
    DestroyDynamicObject(ServerAirdrop[E_AIRDROP_OBJECTS][AIRDROP]);

	ServerAirdrop[E_AIRDROP_OBJECTS][AIRDROP] = CreateDynamicObject (964, ServerAirdrop[E_AIRDROP_POSX], ServerAirdrop[E_AIRDROP_POSY], ServerAirdrop[E_AIRDROP_POSZ] - 1, 0.0, 0.0, 0.0);

    ServerAirdrop[E_AIDROP_LABEL] = CreateDynamic3DTextLabel("Evento {FA8072}Airdrop\n{ffffff}/pAirdrop", -1, ServerAirdrop[E_AIRDROP_POSX], ServerAirdrop[E_AIRDROP_POSY], ServerAirdrop[E_AIRDROP_POSZ],8.0);
    return true;
}
public OnTimerCollectAirdrop(playerid)
{
    Iter_Remove(PlayerAirDrop, playerid);

    if(!IsPlayerInAirdrop(playerid))
        return true;

    ClearAnimations(playerid, 1);

    DestroyAirdrop();

    GivePlayerWeapon(playerid, 31, 150);
    SendClientMessage(playerid, 0xFFFFFFFF, "AIRDROP: Voce pegou o airdrop");
    return true;
}
