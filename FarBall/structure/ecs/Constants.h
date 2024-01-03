#pragma once
using namespace std;

// Los distintos estados del juego
enum STATE {
	MAINMENU_STATE, PLAY_STATE, MULTI_PLAYER, PAUSE_STATE, GAMEOVER_STATE, WIN_STATE
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
	_sys_RIGIDBODY,

	//DO NOT REMOVE THIS
	_LAST_SYS_ID
};

constexpr sysId_type maxSystemId = _LAST_SYS_ID;