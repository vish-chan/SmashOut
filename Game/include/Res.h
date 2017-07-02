#ifndef __Res_H__
#define __Res_H__

namespace FrameworkX
{
	class ResourceManager;
	class Image;
	class Font;

	Image* LoadImageById(ResourceManager *theManager, int theId);
	void ReplaceImageById(ResourceManager *theManager, int theId, Image *theImage);
	bool ExtractResourcesByName(ResourceManager *theManager, const char *theName);

	// Game Resources
	bool ExtractGameResources(ResourceManager *theMgr);
	extern Image* IMAGE_BONUS_BLACK_SCREEN;
	extern Image* IMAGE_BONUS_BLINKING_BALL;
	extern Image* IMAGE_BONUS_BLUEGEM;
	extern Image* IMAGE_BONUS_BOTTOM_BLOCK;
	extern Image* IMAGE_BONUS_FIRE;
	extern Image* IMAGE_BONUS_GREENGEM;
	extern Image* IMAGE_BONUS_LASER;
	extern Image* IMAGE_BONUS_LIFE;
	extern Image* IMAGE_BONUS_MISSILE;
	extern Image* IMAGE_BONUS_REDGEM;
	extern Image* IMAGE_BONUS_REVERSE_MOTION;
	extern Image* IMAGE_BOTTOM_SHIELD;
	extern Image* IMAGE_BRICK_BLACK;
	extern Image* IMAGE_BRICK_GOLD;
	extern Image* IMAGE_BRICK_LASER;
	extern Image* IMAGE_BRICK_MISSILE;
	extern Image* IMAGE_BRICK_RED;
	extern Image* IMAGE_BRICK_SILVER;
	extern Image* IMAGE_BRICK_T_LOCKED;
	extern Image* IMAGE_BRICK_T_UNLOCKED;
	extern Image* IMAGE_CHECKBOX;
	extern Image* IMAGE_CREDITS_FRAME;
	extern Image* IMAGE_DIALOG_BOX;
	extern Image* IMAGE_DIALOG_BUTTON;
	extern Image* IMAGE_DISC;
	extern Image* IMAGE_END_SCREEN;
	extern Image* IMAGE_EXPLOSION2;
	extern Image* IMAGE_EXPLOSION3;
	extern Image* IMAGE_FIRE_BALL;
	extern Image* IMAGE_FIRE_EXPLOSION;
	extern Image* IMAGE_GALAXY;
	extern Image* IMAGE_HIGH_SCORE;
	extern Image* IMAGE_INSTRUCTIONS_BASE;
	extern Image* IMAGE_INSTRUCTIONS_BONUS;
	extern Image* IMAGE_INSTRUCTIONS_BONUS_2;
	extern Image* IMAGE_INSTRUCTIONS_BRICKS;
	extern Image* IMAGE_INSTRUCTIONS_BTN_NORMAL;
	extern Image* IMAGE_INSTRUCTIONS_BTN_OVER;
	extern Image* IMAGE_INSTRUCTIONS_GENERAL;
	extern Image* IMAGE_LASER_CIRCLEOVER;
	extern Image* IMAGE_LASER_CIRCLEUNDER;
	extern Image* IMAGE_LASER_MAIN;
	extern Image* IMAGE_LASER_PAD;
	extern Image* IMAGE_LEVELUP_SCREEN;
	extern Image* IMAGE_LEVEL_SELECT_BASE;
	extern Image* IMAGE_LEVEL_SELECT_PAGE1;
	extern Image* IMAGE_LEVEL_SELECT_PAGE2;
	extern Image* IMAGE_LS_1_BTN_NORMAL;
	extern Image* IMAGE_LS_1_BTN_OVER;
	extern Image* IMAGE_LS_2_BTN_NORMAL;
	extern Image* IMAGE_LS_2_BTN_OVER;
	extern Image* IMAGE_LS_3_BTN_NORMAL;
	extern Image* IMAGE_LS_3_BTN_OVER;
	extern Image* IMAGE_LS_4_BTN_NORMAL;
	extern Image* IMAGE_LS_4_BTN_OVER;
	extern Image* IMAGE_LS_5_BTN_NORMAL;
	extern Image* IMAGE_LS_5_BTN_OVER;
	extern Image* IMAGE_LS_6_BTN_NORMAL;
	extern Image* IMAGE_LS_6_BTN_OVER;
	extern Image* IMAGE_MAIN_MENU;
	extern Image* IMAGE_MISSILE;
	extern Image* IMAGE_MM_BTN_NORMAL;
	extern Image* IMAGE_MM_BTN_OVER;
	extern Image* IMAGE_MM_SPACE;
	extern Image* IMAGE_NEBULA_1;
	extern Image* IMAGE_NEBULA_2;
	extern Image* IMAGE_PLANET_1;
	extern Image* IMAGE_PLANET_2;
	extern Image* IMAGE_PLANET_3;
	extern Image* IMAGE_PLANET_4;
	extern Image* IMAGE_PLANET_5;
	extern Image* IMAGE_PLANET_6;
	extern Image* IMAGE_PLAYER;
	extern Image* IMAGE_RFF;
	extern Image* IMAGE_ROTATING_EFFECTS;
	extern Image* IMAGE_SCORE_BOARD;
	extern Image* IMAGE_SLIDER_THUMB;
	extern Image* IMAGE_SLIDER_TRACK;
	extern Image* IMAGE_SPACE_BG;
	extern Image* IMAGE_SPACE_BG_BLUE;
	extern Image* IMAGE_SPACE_BG_GREEN;
	extern Image* IMAGE_SPACE_BG_RED;
	extern Image* IMAGE_STARS;
	extern Image* IMAGE_WAVE_DES;
	extern int SOUND_BALL_COLLISION;
	extern int SOUND_BOARDMOUSEDOWN;
	extern int SOUND_BONUSSFX;
	extern int SOUND_BONUS_LASERSFX;
	extern int SOUND_GAMEOVER;
	extern int SOUND_GAMEOVERSFX;
	extern int SOUND_LASERSFX;
	extern int SOUND_LEVELUPSFX;
	extern int SOUND_LSMOUSEDOWN;
	extern int SOUND_LSMOUSEOVER;
	extern int SOUND_LU_DING;
	extern int SOUND_MISSILESFX;
	extern int SOUND_MMOUSEOVER;
	extern int SOUND_ONEUPSFX;
	extern int SOUND_PLAYMOUSEDOWN;

	// Init Resources
	bool ExtractInitResources(ResourceManager *theMgr);
	extern Font* FONT_DEFAULT1;
	extern Font* FONT_DEFAULT2;
	extern Font* FONT_DEFAULT3;
	extern Font* FONT_DEFAULT;
	extern Font* FONT_NGAGE1;
	extern Font* FONT_NGAGE2;
	extern Font* FONT_NGAGE3;
	extern Image* IMAGE_CUSTOM_DRAGGING;
	extern Image* IMAGE_CUSTOM_HAND;
	extern Image* IMAGE_CUSTOM_POINTER;
	extern Image* IMAGE_CUSTOM_TEXT;
	extern Image* IMAGE_LOGO;
	extern Image* IMAGE_LOGO_TEXT;

	// TitleScreen Resources
	bool ExtractTitleScreenResources(ResourceManager *theMgr);
	extern Image* IMAGE_LOADER_BAR;
	extern Image* IMAGE_LOADER_BAR_BASE;
	extern Image* IMAGE_LOADER_LOADINGTXT;
	extern Image* IMAGE_LU_BTN_NORMAL;
	extern Image* IMAGE_LU_BTN_OVER;
	extern Image* IMAGE_TITLE_SCREEN;
	extern int SOUND_CONTINUE;

	enum ResourceId
	{
		FONT_DEFAULT_ID,
		FONT_DEFAULT1_ID,
		FONT_DEFAULT2_ID,
		FONT_DEFAULT3_ID,
		FONT_NGAGE1_ID,
		FONT_NGAGE2_ID,
		FONT_NGAGE3_ID,
		IMAGE_LOGO_ID,
		IMAGE_LOGO_TEXT_ID,
		IMAGE_CUSTOM_POINTER_ID,
		IMAGE_CUSTOM_HAND_ID,
		IMAGE_CUSTOM_DRAGGING_ID,
		IMAGE_CUSTOM_TEXT_ID,
		IMAGE_LOADER_BAR_ID,
		IMAGE_LOADER_LOADINGTXT_ID,
		IMAGE_TITLE_SCREEN_ID,
		IMAGE_LOADER_BAR_BASE_ID,
		IMAGE_LU_BTN_NORMAL_ID,
		IMAGE_LU_BTN_OVER_ID,
		SOUND_CONTINUE_ID,
		SOUND_MMOUSEOVER_ID,
		SOUND_LSMOUSEOVER_ID,
		SOUND_PLAYMOUSEDOWN_ID,
		SOUND_BOARDMOUSEDOWN_ID,
		SOUND_GAMEOVER_ID,
		SOUND_LSMOUSEDOWN_ID,
		SOUND_BONUSSFX_ID,
		SOUND_BONUS_LASERSFX_ID,
		SOUND_ONEUPSFX_ID,
		SOUND_LASERSFX_ID,
		SOUND_MISSILESFX_ID,
		SOUND_BALL_COLLISION_ID,
		SOUND_LEVELUPSFX_ID,
		SOUND_GAMEOVERSFX_ID,
		SOUND_LU_DING_ID,
		IMAGE_MAIN_MENU_ID,
		IMAGE_MM_SPACE_ID,
		IMAGE_INSTRUCTIONS_BASE_ID,
		IMAGE_INSTRUCTIONS_BRICKS_ID,
		IMAGE_INSTRUCTIONS_GENERAL_ID,
		IMAGE_INSTRUCTIONS_BONUS_ID,
		IMAGE_INSTRUCTIONS_BONUS_2_ID,
		IMAGE_INSTRUCTIONS_BTN_NORMAL_ID,
		IMAGE_INSTRUCTIONS_BTN_OVER_ID,
		IMAGE_LS_1_BTN_NORMAL_ID,
		IMAGE_LS_2_BTN_NORMAL_ID,
		IMAGE_LS_3_BTN_NORMAL_ID,
		IMAGE_LS_4_BTN_NORMAL_ID,
		IMAGE_LS_5_BTN_NORMAL_ID,
		IMAGE_LS_1_BTN_OVER_ID,
		IMAGE_LS_2_BTN_OVER_ID,
		IMAGE_LS_3_BTN_OVER_ID,
		IMAGE_LS_4_BTN_OVER_ID,
		IMAGE_LS_5_BTN_OVER_ID,
		IMAGE_LS_6_BTN_NORMAL_ID,
		IMAGE_LS_6_BTN_OVER_ID,
		IMAGE_LEVEL_SELECT_BASE_ID,
		IMAGE_LEVEL_SELECT_PAGE1_ID,
		IMAGE_LEVEL_SELECT_PAGE2_ID,
		IMAGE_CREDITS_FRAME_ID,
		IMAGE_CHECKBOX_ID,
		IMAGE_DIALOG_BOX_ID,
		IMAGE_DIALOG_BUTTON_ID,
		IMAGE_SLIDER_TRACK_ID,
		IMAGE_SLIDER_THUMB_ID,
		IMAGE_WAVE_DES_ID,
		IMAGE_MISSILE_ID,
		IMAGE_LASER_PAD_ID,
		IMAGE_RFF_ID,
		IMAGE_LASER_CIRCLEUNDER_ID,
		IMAGE_LASER_CIRCLEOVER_ID,
		IMAGE_LASER_MAIN_ID,
		IMAGE_SCORE_BOARD_ID,
		IMAGE_FIRE_BALL_ID,
		IMAGE_BOTTOM_SHIELD_ID,
		IMAGE_BONUS_GREENGEM_ID,
		IMAGE_BONUS_MISSILE_ID,
		IMAGE_BONUS_LIFE_ID,
		IMAGE_BONUS_LASER_ID,
		IMAGE_BONUS_BLUEGEM_ID,
		IMAGE_BONUS_REDGEM_ID,
		IMAGE_BONUS_FIRE_ID,
		IMAGE_BONUS_BOTTOM_BLOCK_ID,
		IMAGE_BONUS_BLACK_SCREEN_ID,
		IMAGE_BONUS_BLINKING_BALL_ID,
		IMAGE_BONUS_REVERSE_MOTION_ID,
		IMAGE_PLAYER_ID,
		IMAGE_BRICK_SILVER_ID,
		IMAGE_BRICK_BLACK_ID,
		IMAGE_BRICK_LASER_ID,
		IMAGE_BRICK_RED_ID,
		IMAGE_BRICK_GOLD_ID,
		IMAGE_BRICK_T_UNLOCKED_ID,
		IMAGE_BRICK_T_LOCKED_ID,
		IMAGE_BRICK_MISSILE_ID,
		IMAGE_DISC_ID,
		IMAGE_SPACE_BG_ID,
		IMAGE_SPACE_BG_GREEN_ID,
		IMAGE_SPACE_BG_RED_ID,
		IMAGE_SPACE_BG_BLUE_ID,
		IMAGE_NEBULA_1_ID,
		IMAGE_NEBULA_2_ID,
		IMAGE_STARS_ID,
		IMAGE_PLANET_1_ID,
		IMAGE_PLANET_2_ID,
		IMAGE_PLANET_3_ID,
		IMAGE_PLANET_4_ID,
		IMAGE_PLANET_5_ID,
		IMAGE_PLANET_6_ID,
		IMAGE_GALAXY_ID,
		IMAGE_ROTATING_EFFECTS_ID,
		IMAGE_EXPLOSION3_ID,
		IMAGE_EXPLOSION2_ID,
		IMAGE_FIRE_EXPLOSION_ID,
		IMAGE_LEVELUP_SCREEN_ID,
		IMAGE_HIGH_SCORE_ID,
		IMAGE_END_SCREEN_ID,
		IMAGE_MM_BTN_NORMAL_ID,
		IMAGE_MM_BTN_OVER_ID,
		RESOURCE_ID_MAX
	};

	Image* GetImageById(int theId);
	Font* GetFontById(int theId);
	int GetSoundById(int theId);

	Image*& GetImageRefById(int theId);
	Font*& GetFontRefById(int theId);
	int& GetSoundRefById(int theId);

	ResourceId GetIdByImage(Image *theImage);
	ResourceId GetIdByFont(Font *theFont);
	ResourceId GetIdBySound(int theSound);
	const char* GetStringIdById(int theId);
	ResourceId GetIdByStringId(const char *theStringId);

} // namespace FrameworkX


#endif
