#pragma once
using namespace std;

// Los distintos estados del juego
enum STATE {
	MAINMENU_STATE, PLAY_STATE, PAUSE_STATE, GAMEOVER_STATE, WIN_STATE
};

enum Texts { 
	NAME, TITLE, START, DISTANCE 
};

// GRUPOS
using grpId_type = unsigned int;

enum grpId : grpId_type {
	_grp_GENERAL,

	//DO NOT REMOVE THIS
	_LAST_GRP_ID
};

constexpr grpId_type maxGroupId = _LAST_GRP_ID;

// HANDLER
using hdlrId_type = unsigned int;

enum hdlrId : hdlrId_type {
	_hdlr_BALL,

	//DO NOT REMOVE THIS
	_LAST_HDLR_ID
};

constexpr hdlrId_type maxHandlerId = _LAST_HDLR_ID;

// SYSTEMS
using sysId_type = unsigned int;

enum sysId : sysId_type {
	_sys_TEXT,
	_sys_FLOOR,
	_sys_PENGUIN,

	//DO NOT REMOVE THIS
	_LAST_SYS_ID
};

// MESSAGES
using msgId_type = unsigned int;
enum msgId : msgId_type {
	_m_INIT_STATE,
	_m_PENGUIN_POS_UPDATE,
};

struct Message {
	msgId_type id;
	// _m_INIT_STARTE
	struct {
		STATE st;
	} state_data;
	// _m_PENGUIN_POS_UPDATE
	struct {
		float x;
		float z;
	} penguin_pos_data;
};


constexpr sysId_type maxSystemId = _LAST_SYS_ID;