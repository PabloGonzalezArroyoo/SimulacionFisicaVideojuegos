#pragma once
using namespace std;

// Los distintos estados del juego
enum STATE {
	MAINMENU_STATE, PLAY_STATE, PAUSE_STATE, GAMEOVER_STATE, WIN_STATE
};

enum Texts { 
	NAME, TITLE, START, DISTANCE, FUEL
};

// GRUPOS
using grpId_type = unsigned int;

enum grpId : grpId_type {
	_grp_GENERAL,
	_grp_BACKGROUND,
	_grp_FOREGROUND,
	_grp_FOLLOW_PARTICLES,
	_grp_EXPLODE_PARTICLES,

	//DO NOT REMOVE THIS
	_LAST_GRP_ID
};

constexpr grpId_type maxGroupId = _LAST_GRP_ID;

// HANDLER
using hdlrId_type = unsigned int;

enum hdlrId : hdlrId_type {
	_hdlr_JETPACK,

	//DO NOT REMOVE THIS
	_LAST_HDLR_ID
};

constexpr hdlrId_type maxHandlerId = _LAST_HDLR_ID;

// SYSTEMS
using sysId_type = unsigned int;

enum sysId : sysId_type {
	_sys_TEXT,
	_sys_JETPACK,
	_sys_FLOOR,
	_sys_OBSTACLES,

	//DO NOT REMOVE THIS
	_LAST_SYS_ID
};

constexpr sysId_type maxSystemId = _LAST_SYS_ID;

// MESSAGES
using msgId_type = unsigned int;
enum msgId : msgId_type {
	_m_INIT_STATE,
	_m_USE_FUEL,
	_m_UPDATE_FUEL,
};

struct Message {
	msgId_type id;
	// _m_INIT_STARTE
	struct {
		STATE st;
	} state_data;
	// _m_USE_FUEL && _m_UPDATE_FUEL
	struct {
		int fuel;
	} fuel_data;
};

const int JETPACK_FUEL = 100;
const int CONSTANT_X_VEL = 200;