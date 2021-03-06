#pragma once

//enum DIRECTION {DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN ,DIR_END};

enum OBJID { OBJ_OBJECT, OBJ_ITEM, OBJ_PARRY, OBJ_MONSTER, OBJ_PLAYER, OBJ_BULLET, OBJ_EFFECT, OBJ_MOUSE, OBJ_UI, OBJ_END };

enum SCENEID { SC_LOGO, SC_LOADING, SC_MENU, SC_WORLD, SC_EDIT, SC_STAGE, SC_TUTORIAL, SC_SHOP, SC_RUN, SC_CLEAR, SC_END };

enum OBJTAG { TAG_PLAYER, TAG_BULLET, TAG_MONSTER, TAG_TRAMPOLIN, TAG_BOSS, TAG_ITEM, TAG_END };

enum TILETAG { TILE_STAGE, TILE_TUTORIAL, TILE_SHOP, TILE_RUN, TILE_END, TILE_NPC,}; // TILE_END?? NORMAL??

enum LINENO { LINE_STAGE, LINE_TUTORIAL, LINE_RUN, LINE_END };

enum CHANNELID { SOUND_EFFECT, SOUND_BGM, SOUND_PLAYER, SOUND_MONSTER, SOUND_MACHINE, MAXCHANNEL };