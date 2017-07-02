#include "Res.h"
#include "SexyAppFramework/ResourceManager.h"

using namespace FrameworkX;

#pragma warning(disable:4311 4312)

static bool gNeedRecalcVariableToIdMap = false;

bool FrameworkX::ExtractResourcesByName(ResourceManager *theManager, const char *theName)
{
	if (strcmp(theName,"Game")==0) return ExtractGameResources(theManager);
	if (strcmp(theName,"Init")==0) return ExtractInitResources(theManager);
	if (strcmp(theName,"TitleScreen")==0) return ExtractTitleScreenResources(theManager);
	return false;
}

FrameworkX::ResourceId FrameworkX::GetIdByStringId(const char *theStringId)
{
	typedef std::map<std::string,int> MyMap;
	static MyMap aMap;
	if(aMap.empty())
	{
		for(int i=0; i<RESOURCE_ID_MAX; i++)
			aMap[GetStringIdById(i)] = i;
	}

	MyMap::iterator anItr = aMap.find(theStringId);
	if (anItr == aMap.end())
		return RESOURCE_ID_MAX;
	else
		return (ResourceId) anItr->second;
}

// Game Resources
Image* FrameworkX::IMAGE_BONUS_BLACK_SCREEN;
Image* FrameworkX::IMAGE_BONUS_BLINKING_BALL;
Image* FrameworkX::IMAGE_BONUS_BLUEGEM;
Image* FrameworkX::IMAGE_BONUS_BOTTOM_BLOCK;
Image* FrameworkX::IMAGE_BONUS_FIRE;
Image* FrameworkX::IMAGE_BONUS_GREENGEM;
Image* FrameworkX::IMAGE_BONUS_LASER;
Image* FrameworkX::IMAGE_BONUS_LIFE;
Image* FrameworkX::IMAGE_BONUS_MISSILE;
Image* FrameworkX::IMAGE_BONUS_REDGEM;
Image* FrameworkX::IMAGE_BONUS_REVERSE_MOTION;
Image* FrameworkX::IMAGE_BOTTOM_SHIELD;
Image* FrameworkX::IMAGE_BRICK_BLACK;
Image* FrameworkX::IMAGE_BRICK_GOLD;
Image* FrameworkX::IMAGE_BRICK_LASER;
Image* FrameworkX::IMAGE_BRICK_MISSILE;
Image* FrameworkX::IMAGE_BRICK_RED;
Image* FrameworkX::IMAGE_BRICK_SILVER;
Image* FrameworkX::IMAGE_BRICK_T_LOCKED;
Image* FrameworkX::IMAGE_BRICK_T_UNLOCKED;
Image* FrameworkX::IMAGE_CHECKBOX;
Image* FrameworkX::IMAGE_CREDITS_FRAME;
Image* FrameworkX::IMAGE_DIALOG_BOX;
Image* FrameworkX::IMAGE_DIALOG_BUTTON;
Image* FrameworkX::IMAGE_DISC;
Image* FrameworkX::IMAGE_END_SCREEN;
Image* FrameworkX::IMAGE_EXPLOSION2;
Image* FrameworkX::IMAGE_EXPLOSION3;
Image* FrameworkX::IMAGE_FIRE_BALL;
Image* FrameworkX::IMAGE_FIRE_EXPLOSION;
Image* FrameworkX::IMAGE_GALAXY;
Image* FrameworkX::IMAGE_HIGH_SCORE;
Image* FrameworkX::IMAGE_INSTRUCTIONS_BASE;
Image* FrameworkX::IMAGE_INSTRUCTIONS_BONUS;
Image* FrameworkX::IMAGE_INSTRUCTIONS_BONUS_2;
Image* FrameworkX::IMAGE_INSTRUCTIONS_BRICKS;
Image* FrameworkX::IMAGE_INSTRUCTIONS_BTN_NORMAL;
Image* FrameworkX::IMAGE_INSTRUCTIONS_BTN_OVER;
Image* FrameworkX::IMAGE_INSTRUCTIONS_GENERAL;
Image* FrameworkX::IMAGE_LASER_CIRCLEOVER;
Image* FrameworkX::IMAGE_LASER_CIRCLEUNDER;
Image* FrameworkX::IMAGE_LASER_MAIN;
Image* FrameworkX::IMAGE_LASER_PAD;
Image* FrameworkX::IMAGE_LEVELUP_SCREEN;
Image* FrameworkX::IMAGE_LEVEL_SELECT_BASE;
Image* FrameworkX::IMAGE_LEVEL_SELECT_PAGE1;
Image* FrameworkX::IMAGE_LEVEL_SELECT_PAGE2;
Image* FrameworkX::IMAGE_LS_1_BTN_NORMAL;
Image* FrameworkX::IMAGE_LS_1_BTN_OVER;
Image* FrameworkX::IMAGE_LS_2_BTN_NORMAL;
Image* FrameworkX::IMAGE_LS_2_BTN_OVER;
Image* FrameworkX::IMAGE_LS_3_BTN_NORMAL;
Image* FrameworkX::IMAGE_LS_3_BTN_OVER;
Image* FrameworkX::IMAGE_LS_4_BTN_NORMAL;
Image* FrameworkX::IMAGE_LS_4_BTN_OVER;
Image* FrameworkX::IMAGE_LS_5_BTN_NORMAL;
Image* FrameworkX::IMAGE_LS_5_BTN_OVER;
Image* FrameworkX::IMAGE_LS_6_BTN_NORMAL;
Image* FrameworkX::IMAGE_LS_6_BTN_OVER;
Image* FrameworkX::IMAGE_MAIN_MENU;
Image* FrameworkX::IMAGE_MISSILE;
Image* FrameworkX::IMAGE_MM_BTN_NORMAL;
Image* FrameworkX::IMAGE_MM_BTN_OVER;
Image* FrameworkX::IMAGE_MM_SPACE;
Image* FrameworkX::IMAGE_NEBULA_1;
Image* FrameworkX::IMAGE_NEBULA_2;
Image* FrameworkX::IMAGE_PLANET_1;
Image* FrameworkX::IMAGE_PLANET_2;
Image* FrameworkX::IMAGE_PLANET_3;
Image* FrameworkX::IMAGE_PLANET_4;
Image* FrameworkX::IMAGE_PLANET_5;
Image* FrameworkX::IMAGE_PLANET_6;
Image* FrameworkX::IMAGE_PLAYER;
Image* FrameworkX::IMAGE_RFF;
Image* FrameworkX::IMAGE_ROTATING_EFFECTS;
Image* FrameworkX::IMAGE_SCORE_BOARD;
Image* FrameworkX::IMAGE_SLIDER_THUMB;
Image* FrameworkX::IMAGE_SLIDER_TRACK;
Image* FrameworkX::IMAGE_SPACE_BG;
Image* FrameworkX::IMAGE_SPACE_BG_BLUE;
Image* FrameworkX::IMAGE_SPACE_BG_GREEN;
Image* FrameworkX::IMAGE_SPACE_BG_RED;
Image* FrameworkX::IMAGE_STARS;
Image* FrameworkX::IMAGE_WAVE_DES;
int FrameworkX::SOUND_BALL_COLLISION;
int FrameworkX::SOUND_BOARDMOUSEDOWN;
int FrameworkX::SOUND_BONUSSFX;
int FrameworkX::SOUND_BONUS_LASERSFX;
int FrameworkX::SOUND_GAMEOVER;
int FrameworkX::SOUND_GAMEOVERSFX;
int FrameworkX::SOUND_LASERSFX;
int FrameworkX::SOUND_LEVELUPSFX;
int FrameworkX::SOUND_LSMOUSEDOWN;
int FrameworkX::SOUND_LSMOUSEOVER;
int FrameworkX::SOUND_LU_DING;
int FrameworkX::SOUND_MISSILESFX;
int FrameworkX::SOUND_MMOUSEOVER;
int FrameworkX::SOUND_ONEUPSFX;
int FrameworkX::SOUND_PLAYMOUSEDOWN;

bool FrameworkX::ExtractGameResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BONUS_BLACK_SCREEN = aMgr.GetImageThrow("IMAGE_BONUS_BLACK_SCREEN");
		IMAGE_BONUS_BLINKING_BALL = aMgr.GetImageThrow("IMAGE_BONUS_BLINKING_BALL");
		IMAGE_BONUS_BLUEGEM = aMgr.GetImageThrow("IMAGE_BONUS_BLUEGEM");
		IMAGE_BONUS_BOTTOM_BLOCK = aMgr.GetImageThrow("IMAGE_BONUS_BOTTOM_BLOCK");
		IMAGE_BONUS_FIRE = aMgr.GetImageThrow("IMAGE_BONUS_FIRE");
		IMAGE_BONUS_GREENGEM = aMgr.GetImageThrow("IMAGE_BONUS_GREENGEM");
		IMAGE_BONUS_LASER = aMgr.GetImageThrow("IMAGE_BONUS_LASER");
		IMAGE_BONUS_LIFE = aMgr.GetImageThrow("IMAGE_BONUS_LIFE");
		IMAGE_BONUS_MISSILE = aMgr.GetImageThrow("IMAGE_BONUS_MISSILE");
		IMAGE_BONUS_REDGEM = aMgr.GetImageThrow("IMAGE_BONUS_REDGEM");
		IMAGE_BONUS_REVERSE_MOTION = aMgr.GetImageThrow("IMAGE_BONUS_REVERSE_MOTION");
		IMAGE_BOTTOM_SHIELD = aMgr.GetImageThrow("IMAGE_BOTTOM_SHIELD");
		IMAGE_BRICK_BLACK = aMgr.GetImageThrow("IMAGE_BRICK_BLACK");
		IMAGE_BRICK_GOLD = aMgr.GetImageThrow("IMAGE_BRICK_GOLD");
		IMAGE_BRICK_LASER = aMgr.GetImageThrow("IMAGE_BRICK_LASER");
		IMAGE_BRICK_MISSILE = aMgr.GetImageThrow("IMAGE_BRICK_MISSILE");
		IMAGE_BRICK_RED = aMgr.GetImageThrow("IMAGE_BRICK_RED");
		IMAGE_BRICK_SILVER = aMgr.GetImageThrow("IMAGE_BRICK_SILVER");
		IMAGE_BRICK_T_LOCKED = aMgr.GetImageThrow("IMAGE_BRICK_T_LOCKED");
		IMAGE_BRICK_T_UNLOCKED = aMgr.GetImageThrow("IMAGE_BRICK_T_UNLOCKED");
		IMAGE_CHECKBOX = aMgr.GetImageThrow("IMAGE_CHECKBOX");
		IMAGE_CREDITS_FRAME = aMgr.GetImageThrow("IMAGE_CREDITS_FRAME");
		IMAGE_DIALOG_BOX = aMgr.GetImageThrow("IMAGE_DIALOG_BOX");
		IMAGE_DIALOG_BUTTON = aMgr.GetImageThrow("IMAGE_DIALOG_BUTTON");
		IMAGE_DISC = aMgr.GetImageThrow("IMAGE_DISC");
		IMAGE_END_SCREEN = aMgr.GetImageThrow("IMAGE_END_SCREEN");
		IMAGE_EXPLOSION2 = aMgr.GetImageThrow("IMAGE_EXPLOSION2");
		IMAGE_EXPLOSION3 = aMgr.GetImageThrow("IMAGE_EXPLOSION3");
		IMAGE_FIRE_BALL = aMgr.GetImageThrow("IMAGE_FIRE_BALL");
		IMAGE_FIRE_EXPLOSION = aMgr.GetImageThrow("IMAGE_FIRE_EXPLOSION");
		IMAGE_GALAXY = aMgr.GetImageThrow("IMAGE_GALAXY");
		IMAGE_HIGH_SCORE = aMgr.GetImageThrow("IMAGE_HIGH_SCORE");
		IMAGE_INSTRUCTIONS_BASE = aMgr.GetImageThrow("IMAGE_INSTRUCTIONS_BASE");
		IMAGE_INSTRUCTIONS_BONUS = aMgr.GetImageThrow("IMAGE_INSTRUCTIONS_BONUS");
		IMAGE_INSTRUCTIONS_BONUS_2 = aMgr.GetImageThrow("IMAGE_INSTRUCTIONS_BONUS_2");
		IMAGE_INSTRUCTIONS_BRICKS = aMgr.GetImageThrow("IMAGE_INSTRUCTIONS_BRICKS");
		IMAGE_INSTRUCTIONS_BTN_NORMAL = aMgr.GetImageThrow("IMAGE_INSTRUCTIONS_BTN_NORMAL");
		IMAGE_INSTRUCTIONS_BTN_OVER = aMgr.GetImageThrow("IMAGE_INSTRUCTIONS_BTN_OVER");
		IMAGE_INSTRUCTIONS_GENERAL = aMgr.GetImageThrow("IMAGE_INSTRUCTIONS_GENERAL");
		IMAGE_LASER_CIRCLEOVER = aMgr.GetImageThrow("IMAGE_LASER_CIRCLEOVER");
		IMAGE_LASER_CIRCLEUNDER = aMgr.GetImageThrow("IMAGE_LASER_CIRCLEUNDER");
		IMAGE_LASER_MAIN = aMgr.GetImageThrow("IMAGE_LASER_MAIN");
		IMAGE_LASER_PAD = aMgr.GetImageThrow("IMAGE_LASER_PAD");
		IMAGE_LEVELUP_SCREEN = aMgr.GetImageThrow("IMAGE_LEVELUP_SCREEN");
		IMAGE_LEVEL_SELECT_BASE = aMgr.GetImageThrow("IMAGE_LEVEL_SELECT_BASE");
		IMAGE_LEVEL_SELECT_PAGE1 = aMgr.GetImageThrow("IMAGE_LEVEL_SELECT_PAGE1");
		IMAGE_LEVEL_SELECT_PAGE2 = aMgr.GetImageThrow("IMAGE_LEVEL_SELECT_PAGE2");
		IMAGE_LS_1_BTN_NORMAL = aMgr.GetImageThrow("IMAGE_LS_1_BTN_NORMAL");
		IMAGE_LS_1_BTN_OVER = aMgr.GetImageThrow("IMAGE_LS_1_BTN_OVER");
		IMAGE_LS_2_BTN_NORMAL = aMgr.GetImageThrow("IMAGE_LS_2_BTN_NORMAL");
		IMAGE_LS_2_BTN_OVER = aMgr.GetImageThrow("IMAGE_LS_2_BTN_OVER");
		IMAGE_LS_3_BTN_NORMAL = aMgr.GetImageThrow("IMAGE_LS_3_BTN_NORMAL");
		IMAGE_LS_3_BTN_OVER = aMgr.GetImageThrow("IMAGE_LS_3_BTN_OVER");
		IMAGE_LS_4_BTN_NORMAL = aMgr.GetImageThrow("IMAGE_LS_4_BTN_NORMAL");
		IMAGE_LS_4_BTN_OVER = aMgr.GetImageThrow("IMAGE_LS_4_BTN_OVER");
		IMAGE_LS_5_BTN_NORMAL = aMgr.GetImageThrow("IMAGE_LS_5_BTN_NORMAL");
		IMAGE_LS_5_BTN_OVER = aMgr.GetImageThrow("IMAGE_LS_5_BTN_OVER");
		IMAGE_LS_6_BTN_NORMAL = aMgr.GetImageThrow("IMAGE_LS_6_BTN_NORMAL");
		IMAGE_LS_6_BTN_OVER = aMgr.GetImageThrow("IMAGE_LS_6_BTN_OVER");
		IMAGE_MAIN_MENU = aMgr.GetImageThrow("IMAGE_MAIN_MENU");
		IMAGE_MISSILE = aMgr.GetImageThrow("IMAGE_MISSILE");
		IMAGE_MM_BTN_NORMAL = aMgr.GetImageThrow("IMAGE_MM_BTN_NORMAL");
		IMAGE_MM_BTN_OVER = aMgr.GetImageThrow("IMAGE_MM_BTN_OVER");
		IMAGE_MM_SPACE = aMgr.GetImageThrow("IMAGE_MM_SPACE");
		IMAGE_NEBULA_1 = aMgr.GetImageThrow("IMAGE_NEBULA_1");
		IMAGE_NEBULA_2 = aMgr.GetImageThrow("IMAGE_NEBULA_2");
		IMAGE_PLANET_1 = aMgr.GetImageThrow("IMAGE_PLANET_1");
		IMAGE_PLANET_2 = aMgr.GetImageThrow("IMAGE_PLANET_2");
		IMAGE_PLANET_3 = aMgr.GetImageThrow("IMAGE_PLANET_3");
		IMAGE_PLANET_4 = aMgr.GetImageThrow("IMAGE_PLANET_4");
		IMAGE_PLANET_5 = aMgr.GetImageThrow("IMAGE_PLANET_5");
		IMAGE_PLANET_6 = aMgr.GetImageThrow("IMAGE_PLANET_6");
		IMAGE_PLAYER = aMgr.GetImageThrow("IMAGE_PLAYER");
		IMAGE_RFF = aMgr.GetImageThrow("IMAGE_RFF");
		IMAGE_ROTATING_EFFECTS = aMgr.GetImageThrow("IMAGE_ROTATING_EFFECTS");
		IMAGE_SCORE_BOARD = aMgr.GetImageThrow("IMAGE_SCORE_BOARD");
		IMAGE_SLIDER_THUMB = aMgr.GetImageThrow("IMAGE_SLIDER_THUMB");
		IMAGE_SLIDER_TRACK = aMgr.GetImageThrow("IMAGE_SLIDER_TRACK");
		IMAGE_SPACE_BG = aMgr.GetImageThrow("IMAGE_SPACE_BG");
		IMAGE_SPACE_BG_BLUE = aMgr.GetImageThrow("IMAGE_SPACE_BG_BLUE");
		IMAGE_SPACE_BG_GREEN = aMgr.GetImageThrow("IMAGE_SPACE_BG_GREEN");
		IMAGE_SPACE_BG_RED = aMgr.GetImageThrow("IMAGE_SPACE_BG_RED");
		IMAGE_STARS = aMgr.GetImageThrow("IMAGE_STARS");
		IMAGE_WAVE_DES = aMgr.GetImageThrow("IMAGE_WAVE_DES");
		SOUND_BALL_COLLISION = aMgr.GetSoundThrow("SOUND_BALL_COLLISION");
		SOUND_BOARDMOUSEDOWN = aMgr.GetSoundThrow("SOUND_BOARDMOUSEDOWN");
		SOUND_BONUSSFX = aMgr.GetSoundThrow("SOUND_BONUSSFX");
		SOUND_BONUS_LASERSFX = aMgr.GetSoundThrow("SOUND_BONUS_LASERSFX");
		SOUND_GAMEOVER = aMgr.GetSoundThrow("SOUND_GAMEOVER");
		SOUND_GAMEOVERSFX = aMgr.GetSoundThrow("SOUND_GAMEOVERSFX");
		SOUND_LASERSFX = aMgr.GetSoundThrow("SOUND_LASERSFX");
		SOUND_LEVELUPSFX = aMgr.GetSoundThrow("SOUND_LEVELUPSFX");
		SOUND_LSMOUSEDOWN = aMgr.GetSoundThrow("SOUND_LSMOUSEDOWN");
		SOUND_LSMOUSEOVER = aMgr.GetSoundThrow("SOUND_LSMOUSEOVER");
		SOUND_LU_DING = aMgr.GetSoundThrow("SOUND_LU_DING");
		SOUND_MISSILESFX = aMgr.GetSoundThrow("SOUND_MISSILESFX");
		SOUND_MMOUSEOVER = aMgr.GetSoundThrow("SOUND_MMOUSEOVER");
		SOUND_ONEUPSFX = aMgr.GetSoundThrow("SOUND_ONEUPSFX");
		SOUND_PLAYMOUSEDOWN = aMgr.GetSoundThrow("SOUND_PLAYMOUSEDOWN");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// Init Resources
Font* FrameworkX::FONT_DEFAULT;
Font* FrameworkX::FONT_DEFAULT1;
Font* FrameworkX::FONT_DEFAULT2;
Font* FrameworkX::FONT_DEFAULT3;
Font* FrameworkX::FONT_NGAGE1;
Font* FrameworkX::FONT_NGAGE2;
Font* FrameworkX::FONT_NGAGE3;
Image* FrameworkX::IMAGE_CUSTOM_DRAGGING;
Image* FrameworkX::IMAGE_CUSTOM_HAND;
Image* FrameworkX::IMAGE_CUSTOM_POINTER;
Image* FrameworkX::IMAGE_CUSTOM_TEXT;
Image* FrameworkX::IMAGE_LOGO;
Image* FrameworkX::IMAGE_LOGO_TEXT;

bool FrameworkX::ExtractInitResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		FONT_DEFAULT = aMgr.GetFontThrow("FONT_DEFAULT");
		FONT_DEFAULT1 = aMgr.GetFontThrow("FONT_DEFAULT1");
		FONT_DEFAULT2 = aMgr.GetFontThrow("FONT_DEFAULT2");
		FONT_DEFAULT3 = aMgr.GetFontThrow("FONT_DEFAULT3");
		FONT_NGAGE1 = aMgr.GetFontThrow("FONT_NGAGE1");
		FONT_NGAGE2 = aMgr.GetFontThrow("FONT_NGAGE2");
		FONT_NGAGE3 = aMgr.GetFontThrow("FONT_NGAGE3");
		IMAGE_CUSTOM_DRAGGING = aMgr.GetImageThrow("IMAGE_CUSTOM_DRAGGING");
		IMAGE_CUSTOM_HAND = aMgr.GetImageThrow("IMAGE_CUSTOM_HAND");
		IMAGE_CUSTOM_POINTER = aMgr.GetImageThrow("IMAGE_CUSTOM_POINTER");
		IMAGE_CUSTOM_TEXT = aMgr.GetImageThrow("IMAGE_CUSTOM_TEXT");
		IMAGE_LOGO = aMgr.GetImageThrow("IMAGE_LOGO");
		IMAGE_LOGO_TEXT = aMgr.GetImageThrow("IMAGE_LOGO_TEXT");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// TitleScreen Resources
Image* FrameworkX::IMAGE_LOADER_BAR;
Image* FrameworkX::IMAGE_LOADER_BAR_BASE;
Image* FrameworkX::IMAGE_LOADER_LOADINGTXT;
Image* FrameworkX::IMAGE_LU_BTN_NORMAL;
Image* FrameworkX::IMAGE_LU_BTN_OVER;
Image* FrameworkX::IMAGE_TITLE_SCREEN;
int FrameworkX::SOUND_CONTINUE;

bool FrameworkX::ExtractTitleScreenResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_LOADER_BAR = aMgr.GetImageThrow("IMAGE_LOADER_BAR");
		IMAGE_LOADER_BAR_BASE = aMgr.GetImageThrow("IMAGE_LOADER_BAR_BASE");
		IMAGE_LOADER_LOADINGTXT = aMgr.GetImageThrow("IMAGE_LOADER_LOADINGTXT");
		IMAGE_LU_BTN_NORMAL = aMgr.GetImageThrow("IMAGE_LU_BTN_NORMAL");
		IMAGE_LU_BTN_OVER = aMgr.GetImageThrow("IMAGE_LU_BTN_OVER");
		IMAGE_TITLE_SCREEN = aMgr.GetImageThrow("IMAGE_TITLE_SCREEN");
		SOUND_CONTINUE = aMgr.GetSoundThrow("SOUND_CONTINUE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

static void* gResources[] =
{
	&FONT_DEFAULT,
	&FONT_DEFAULT1,
	&FONT_DEFAULT2,
	&FONT_DEFAULT3,
	&FONT_NGAGE1,
	&FONT_NGAGE2,
	&FONT_NGAGE3,
	&IMAGE_LOGO,
	&IMAGE_LOGO_TEXT,
	&IMAGE_CUSTOM_POINTER,
	&IMAGE_CUSTOM_HAND,
	&IMAGE_CUSTOM_DRAGGING,
	&IMAGE_CUSTOM_TEXT,
	&IMAGE_LOADER_BAR,
	&IMAGE_LOADER_LOADINGTXT,
	&IMAGE_TITLE_SCREEN,
	&IMAGE_LOADER_BAR_BASE,
	&IMAGE_LU_BTN_NORMAL,
	&IMAGE_LU_BTN_OVER,
	&SOUND_CONTINUE,
	&SOUND_MMOUSEOVER,
	&SOUND_LSMOUSEOVER,
	&SOUND_PLAYMOUSEDOWN,
	&SOUND_BOARDMOUSEDOWN,
	&SOUND_GAMEOVER,
	&SOUND_LSMOUSEDOWN,
	&SOUND_BONUSSFX,
	&SOUND_BONUS_LASERSFX,
	&SOUND_ONEUPSFX,
	&SOUND_LASERSFX,
	&SOUND_MISSILESFX,
	&SOUND_BALL_COLLISION,
	&SOUND_LEVELUPSFX,
	&SOUND_GAMEOVERSFX,
	&SOUND_LU_DING,
	&IMAGE_MAIN_MENU,
	&IMAGE_MM_SPACE,
	&IMAGE_INSTRUCTIONS_BASE,
	&IMAGE_INSTRUCTIONS_BRICKS,
	&IMAGE_INSTRUCTIONS_GENERAL,
	&IMAGE_INSTRUCTIONS_BONUS,
	&IMAGE_INSTRUCTIONS_BONUS_2,
	&IMAGE_INSTRUCTIONS_BTN_NORMAL,
	&IMAGE_INSTRUCTIONS_BTN_OVER,
	&IMAGE_LS_1_BTN_NORMAL,
	&IMAGE_LS_2_BTN_NORMAL,
	&IMAGE_LS_3_BTN_NORMAL,
	&IMAGE_LS_4_BTN_NORMAL,
	&IMAGE_LS_5_BTN_NORMAL,
	&IMAGE_LS_1_BTN_OVER,
	&IMAGE_LS_2_BTN_OVER,
	&IMAGE_LS_3_BTN_OVER,
	&IMAGE_LS_4_BTN_OVER,
	&IMAGE_LS_5_BTN_OVER,
	&IMAGE_LS_6_BTN_NORMAL,
	&IMAGE_LS_6_BTN_OVER,
	&IMAGE_LEVEL_SELECT_BASE,
	&IMAGE_LEVEL_SELECT_PAGE1,
	&IMAGE_LEVEL_SELECT_PAGE2,
	&IMAGE_CREDITS_FRAME,
	&IMAGE_CHECKBOX,
	&IMAGE_DIALOG_BOX,
	&IMAGE_DIALOG_BUTTON,
	&IMAGE_SLIDER_TRACK,
	&IMAGE_SLIDER_THUMB,
	&IMAGE_WAVE_DES,
	&IMAGE_MISSILE,
	&IMAGE_LASER_PAD,
	&IMAGE_RFF,
	&IMAGE_LASER_CIRCLEUNDER,
	&IMAGE_LASER_CIRCLEOVER,
	&IMAGE_LASER_MAIN,
	&IMAGE_SCORE_BOARD,
	&IMAGE_FIRE_BALL,
	&IMAGE_BOTTOM_SHIELD,
	&IMAGE_BONUS_GREENGEM,
	&IMAGE_BONUS_MISSILE,
	&IMAGE_BONUS_LIFE,
	&IMAGE_BONUS_LASER,
	&IMAGE_BONUS_BLUEGEM,
	&IMAGE_BONUS_REDGEM,
	&IMAGE_BONUS_FIRE,
	&IMAGE_BONUS_BOTTOM_BLOCK,
	&IMAGE_BONUS_BLACK_SCREEN,
	&IMAGE_BONUS_BLINKING_BALL,
	&IMAGE_BONUS_REVERSE_MOTION,
	&IMAGE_PLAYER,
	&IMAGE_BRICK_SILVER,
	&IMAGE_BRICK_BLACK,
	&IMAGE_BRICK_LASER,
	&IMAGE_BRICK_RED,
	&IMAGE_BRICK_GOLD,
	&IMAGE_BRICK_T_UNLOCKED,
	&IMAGE_BRICK_T_LOCKED,
	&IMAGE_BRICK_MISSILE,
	&IMAGE_DISC,
	&IMAGE_SPACE_BG,
	&IMAGE_SPACE_BG_GREEN,
	&IMAGE_SPACE_BG_RED,
	&IMAGE_SPACE_BG_BLUE,
	&IMAGE_NEBULA_1,
	&IMAGE_NEBULA_2,
	&IMAGE_STARS,
	&IMAGE_PLANET_1,
	&IMAGE_PLANET_2,
	&IMAGE_PLANET_3,
	&IMAGE_PLANET_4,
	&IMAGE_PLANET_5,
	&IMAGE_PLANET_6,
	&IMAGE_GALAXY,
	&IMAGE_ROTATING_EFFECTS,
	&IMAGE_EXPLOSION3,
	&IMAGE_EXPLOSION2,
	&IMAGE_FIRE_EXPLOSION,
	&IMAGE_LEVELUP_SCREEN,
	&IMAGE_HIGH_SCORE,
	&IMAGE_END_SCREEN,
	&IMAGE_MM_BTN_NORMAL,
	&IMAGE_MM_BTN_OVER,
	NULL
};

Image* FrameworkX::LoadImageById(ResourceManager *theManager, int theId)
{
	return (*((Image**)gResources[theId]) = theManager->LoadImage(GetStringIdById(theId)));
}

void FrameworkX::ReplaceImageById(ResourceManager *theManager, int theId, Image *theImage)
{
	theManager->ReplaceImage(GetStringIdById(theId),theImage);
	*(Image**)gResources[theId] = theImage;
}

Image* FrameworkX::GetImageById(int theId)
{
	return *(Image**)gResources[theId];
}

Font* FrameworkX::GetFontById(int theId)
{
	return *(Font**)gResources[theId];
}

int FrameworkX::GetSoundById(int theId)
{
	return *(int*)gResources[theId];
}

Image*& FrameworkX::GetImageRefById(int theId)
{
	return *(Image**)gResources[theId];
}

Font*& FrameworkX::GetFontRefById(int theId)
{
	return *(Font**)gResources[theId];
}

int& FrameworkX::GetSoundRefById(int theId)
{
	return *(int*)gResources[theId];
}

static FrameworkX::ResourceId GetIdByVariable(const void *theVariable)
{
	typedef std::map<int,int> MyMap;
	static MyMap aMap;
	if(gNeedRecalcVariableToIdMap)
	{
		gNeedRecalcVariableToIdMap = false;
		aMap.clear();
		for(int i=0; i<RESOURCE_ID_MAX; i++)
			aMap[*(int*)gResources[i]] = i;
	}

	MyMap::iterator anItr = aMap.find((int)theVariable);
	if (anItr == aMap.end())
		return RESOURCE_ID_MAX;
	else
		return (ResourceId) anItr->second;
}

FrameworkX::ResourceId FrameworkX::GetIdByImage(Image *theImage)
{
	return GetIdByVariable(theImage);
}

FrameworkX::ResourceId FrameworkX::GetIdByFont(Font *theFont)
{
	return GetIdByVariable(theFont);
}

FrameworkX::ResourceId FrameworkX::GetIdBySound(int theSound)
{
	return GetIdByVariable((void*)theSound);
}

const char* FrameworkX::GetStringIdById(int theId)
{
	switch(theId)
	{
		case FONT_DEFAULT_ID: return "FONT_DEFAULT";
		case FONT_DEFAULT1_ID: return "FONT_DEFAULT1";
		case FONT_DEFAULT2_ID: return "FONT_DEFAULT2";
		case FONT_DEFAULT3_ID: return "FONT_DEFAULT3";
		case FONT_NGAGE1_ID: return "FONT_NGAGE1";
		case FONT_NGAGE2_ID: return "FONT_NGAGE2";
		case FONT_NGAGE3_ID: return "FONT_NGAGE3";
		case IMAGE_LOGO_ID: return "IMAGE_LOGO";
		case IMAGE_LOGO_TEXT_ID: return "IMAGE_LOGO_TEXT";
		case IMAGE_CUSTOM_POINTER_ID: return "IMAGE_CUSTOM_POINTER";
		case IMAGE_CUSTOM_HAND_ID: return "IMAGE_CUSTOM_HAND";
		case IMAGE_CUSTOM_DRAGGING_ID: return "IMAGE_CUSTOM_DRAGGING";
		case IMAGE_CUSTOM_TEXT_ID: return "IMAGE_CUSTOM_TEXT";
		case IMAGE_LOADER_BAR_ID: return "IMAGE_LOADER_BAR";
		case IMAGE_LOADER_LOADINGTXT_ID: return "IMAGE_LOADER_LOADINGTXT";
		case IMAGE_TITLE_SCREEN_ID: return "IMAGE_TITLE_SCREEN";
		case IMAGE_LOADER_BAR_BASE_ID: return "IMAGE_LOADER_BAR_BASE";
		case IMAGE_LU_BTN_NORMAL_ID: return "IMAGE_LU_BTN_NORMAL";
		case IMAGE_LU_BTN_OVER_ID: return "IMAGE_LU_BTN_OVER";
		case SOUND_CONTINUE_ID: return "SOUND_CONTINUE";
		case SOUND_MMOUSEOVER_ID: return "SOUND_MMOUSEOVER";
		case SOUND_LSMOUSEOVER_ID: return "SOUND_LSMOUSEOVER";
		case SOUND_PLAYMOUSEDOWN_ID: return "SOUND_PLAYMOUSEDOWN";
		case SOUND_BOARDMOUSEDOWN_ID: return "SOUND_BOARDMOUSEDOWN";
		case SOUND_GAMEOVER_ID: return "SOUND_GAMEOVER";
		case SOUND_LSMOUSEDOWN_ID: return "SOUND_LSMOUSEDOWN";
		case SOUND_BONUSSFX_ID: return "SOUND_BONUSSFX";
		case SOUND_BONUS_LASERSFX_ID: return "SOUND_BONUS_LASERSFX";
		case SOUND_ONEUPSFX_ID: return "SOUND_ONEUPSFX";
		case SOUND_LASERSFX_ID: return "SOUND_LASERSFX";
		case SOUND_MISSILESFX_ID: return "SOUND_MISSILESFX";
		case SOUND_BALL_COLLISION_ID: return "SOUND_BALL_COLLISION";
		case SOUND_LEVELUPSFX_ID: return "SOUND_LEVELUPSFX";
		case SOUND_GAMEOVERSFX_ID: return "SOUND_GAMEOVERSFX";
		case SOUND_LU_DING_ID: return "SOUND_LU_DING";
		case IMAGE_MAIN_MENU_ID: return "IMAGE_MAIN_MENU";
		case IMAGE_MM_SPACE_ID: return "IMAGE_MM_SPACE";
		case IMAGE_INSTRUCTIONS_BASE_ID: return "IMAGE_INSTRUCTIONS_BASE";
		case IMAGE_INSTRUCTIONS_BRICKS_ID: return "IMAGE_INSTRUCTIONS_BRICKS";
		case IMAGE_INSTRUCTIONS_GENERAL_ID: return "IMAGE_INSTRUCTIONS_GENERAL";
		case IMAGE_INSTRUCTIONS_BONUS_ID: return "IMAGE_INSTRUCTIONS_BONUS";
		case IMAGE_INSTRUCTIONS_BONUS_2_ID: return "IMAGE_INSTRUCTIONS_BONUS_2";
		case IMAGE_INSTRUCTIONS_BTN_NORMAL_ID: return "IMAGE_INSTRUCTIONS_BTN_NORMAL";
		case IMAGE_INSTRUCTIONS_BTN_OVER_ID: return "IMAGE_INSTRUCTIONS_BTN_OVER";
		case IMAGE_LS_1_BTN_NORMAL_ID: return "IMAGE_LS_1_BTN_NORMAL";
		case IMAGE_LS_2_BTN_NORMAL_ID: return "IMAGE_LS_2_BTN_NORMAL";
		case IMAGE_LS_3_BTN_NORMAL_ID: return "IMAGE_LS_3_BTN_NORMAL";
		case IMAGE_LS_4_BTN_NORMAL_ID: return "IMAGE_LS_4_BTN_NORMAL";
		case IMAGE_LS_5_BTN_NORMAL_ID: return "IMAGE_LS_5_BTN_NORMAL";
		case IMAGE_LS_1_BTN_OVER_ID: return "IMAGE_LS_1_BTN_OVER";
		case IMAGE_LS_2_BTN_OVER_ID: return "IMAGE_LS_2_BTN_OVER";
		case IMAGE_LS_3_BTN_OVER_ID: return "IMAGE_LS_3_BTN_OVER";
		case IMAGE_LS_4_BTN_OVER_ID: return "IMAGE_LS_4_BTN_OVER";
		case IMAGE_LS_5_BTN_OVER_ID: return "IMAGE_LS_5_BTN_OVER";
		case IMAGE_LS_6_BTN_NORMAL_ID: return "IMAGE_LS_6_BTN_NORMAL";
		case IMAGE_LS_6_BTN_OVER_ID: return "IMAGE_LS_6_BTN_OVER";
		case IMAGE_LEVEL_SELECT_BASE_ID: return "IMAGE_LEVEL_SELECT_BASE";
		case IMAGE_LEVEL_SELECT_PAGE1_ID: return "IMAGE_LEVEL_SELECT_PAGE1";
		case IMAGE_LEVEL_SELECT_PAGE2_ID: return "IMAGE_LEVEL_SELECT_PAGE2";
		case IMAGE_CREDITS_FRAME_ID: return "IMAGE_CREDITS_FRAME";
		case IMAGE_CHECKBOX_ID: return "IMAGE_CHECKBOX";
		case IMAGE_DIALOG_BOX_ID: return "IMAGE_DIALOG_BOX";
		case IMAGE_DIALOG_BUTTON_ID: return "IMAGE_DIALOG_BUTTON";
		case IMAGE_SLIDER_TRACK_ID: return "IMAGE_SLIDER_TRACK";
		case IMAGE_SLIDER_THUMB_ID: return "IMAGE_SLIDER_THUMB";
		case IMAGE_WAVE_DES_ID: return "IMAGE_WAVE_DES";
		case IMAGE_MISSILE_ID: return "IMAGE_MISSILE";
		case IMAGE_LASER_PAD_ID: return "IMAGE_LASER_PAD";
		case IMAGE_RFF_ID: return "IMAGE_RFF";
		case IMAGE_LASER_CIRCLEUNDER_ID: return "IMAGE_LASER_CIRCLEUNDER";
		case IMAGE_LASER_CIRCLEOVER_ID: return "IMAGE_LASER_CIRCLEOVER";
		case IMAGE_LASER_MAIN_ID: return "IMAGE_LASER_MAIN";
		case IMAGE_SCORE_BOARD_ID: return "IMAGE_SCORE_BOARD";
		case IMAGE_FIRE_BALL_ID: return "IMAGE_FIRE_BALL";
		case IMAGE_BOTTOM_SHIELD_ID: return "IMAGE_BOTTOM_SHIELD";
		case IMAGE_BONUS_GREENGEM_ID: return "IMAGE_BONUS_GREENGEM";
		case IMAGE_BONUS_MISSILE_ID: return "IMAGE_BONUS_MISSILE";
		case IMAGE_BONUS_LIFE_ID: return "IMAGE_BONUS_LIFE";
		case IMAGE_BONUS_LASER_ID: return "IMAGE_BONUS_LASER";
		case IMAGE_BONUS_BLUEGEM_ID: return "IMAGE_BONUS_BLUEGEM";
		case IMAGE_BONUS_REDGEM_ID: return "IMAGE_BONUS_REDGEM";
		case IMAGE_BONUS_FIRE_ID: return "IMAGE_BONUS_FIRE";
		case IMAGE_BONUS_BOTTOM_BLOCK_ID: return "IMAGE_BONUS_BOTTOM_BLOCK";
		case IMAGE_BONUS_BLACK_SCREEN_ID: return "IMAGE_BONUS_BLACK_SCREEN";
		case IMAGE_BONUS_BLINKING_BALL_ID: return "IMAGE_BONUS_BLINKING_BALL";
		case IMAGE_BONUS_REVERSE_MOTION_ID: return "IMAGE_BONUS_REVERSE_MOTION";
		case IMAGE_PLAYER_ID: return "IMAGE_PLAYER";
		case IMAGE_BRICK_SILVER_ID: return "IMAGE_BRICK_SILVER";
		case IMAGE_BRICK_BLACK_ID: return "IMAGE_BRICK_BLACK";
		case IMAGE_BRICK_LASER_ID: return "IMAGE_BRICK_LASER";
		case IMAGE_BRICK_RED_ID: return "IMAGE_BRICK_RED";
		case IMAGE_BRICK_GOLD_ID: return "IMAGE_BRICK_GOLD";
		case IMAGE_BRICK_T_UNLOCKED_ID: return "IMAGE_BRICK_T_UNLOCKED";
		case IMAGE_BRICK_T_LOCKED_ID: return "IMAGE_BRICK_T_LOCKED";
		case IMAGE_BRICK_MISSILE_ID: return "IMAGE_BRICK_MISSILE";
		case IMAGE_DISC_ID: return "IMAGE_DISC";
		case IMAGE_SPACE_BG_ID: return "IMAGE_SPACE_BG";
		case IMAGE_SPACE_BG_GREEN_ID: return "IMAGE_SPACE_BG_GREEN";
		case IMAGE_SPACE_BG_RED_ID: return "IMAGE_SPACE_BG_RED";
		case IMAGE_SPACE_BG_BLUE_ID: return "IMAGE_SPACE_BG_BLUE";
		case IMAGE_NEBULA_1_ID: return "IMAGE_NEBULA_1";
		case IMAGE_NEBULA_2_ID: return "IMAGE_NEBULA_2";
		case IMAGE_STARS_ID: return "IMAGE_STARS";
		case IMAGE_PLANET_1_ID: return "IMAGE_PLANET_1";
		case IMAGE_PLANET_2_ID: return "IMAGE_PLANET_2";
		case IMAGE_PLANET_3_ID: return "IMAGE_PLANET_3";
		case IMAGE_PLANET_4_ID: return "IMAGE_PLANET_4";
		case IMAGE_PLANET_5_ID: return "IMAGE_PLANET_5";
		case IMAGE_PLANET_6_ID: return "IMAGE_PLANET_6";
		case IMAGE_GALAXY_ID: return "IMAGE_GALAXY";
		case IMAGE_ROTATING_EFFECTS_ID: return "IMAGE_ROTATING_EFFECTS";
		case IMAGE_EXPLOSION3_ID: return "IMAGE_EXPLOSION3";
		case IMAGE_EXPLOSION2_ID: return "IMAGE_EXPLOSION2";
		case IMAGE_FIRE_EXPLOSION_ID: return "IMAGE_FIRE_EXPLOSION";
		case IMAGE_LEVELUP_SCREEN_ID: return "IMAGE_LEVELUP_SCREEN";
		case IMAGE_HIGH_SCORE_ID: return "IMAGE_HIGH_SCORE";
		case IMAGE_END_SCREEN_ID: return "IMAGE_END_SCREEN";
		case IMAGE_MM_BTN_NORMAL_ID: return "IMAGE_MM_BTN_NORMAL";
		case IMAGE_MM_BTN_OVER_ID: return "IMAGE_MM_BTN_OVER";
		default: return "";
	}
}

