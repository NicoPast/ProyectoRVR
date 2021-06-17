#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
//
		{ ARIAL10, "./resources/fonts/ARIAL.ttf", 10 }, //
		{ ARIAL12, "./resources/fonts/ARIAL.ttf", 12 }, //
		{ ARIAL16, "./resources/fonts/ARIAL.ttf", 16 }, //
		{ ARIAL24, "./resources/fonts/ARIAL.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_ {
//
		{ Fighter, "./resources/images/fighter.png" }, //
		{ WhiteRect,"./resources/images/whiterect.png" }, //
};

vector<Resources::TextMsgInfo> Resources::messages_ {
//
		{ PressEnter, "Press Enter to Start", { COLOR(0xaaffbbff) }, ARIAL24 }, //
		{ WaitingForPlayer, "Waiting for other player", { COLOR(0xaaccbbff) }, ARIAL24 }, //
		{ GameOver, "Game Over", { COLOR(0xffffbbff) }, ARIAL24 }, //
		{ YouWin, "You WIN!!!", { COLOR(0xffffbbff) }, ARIAL24 }, //
		{ YouLost, "You LOST...", { COLOR(0xffffbbff) }, ARIAL24 }, //
		{ Draw, "Draw!", { COLOR(0xffffbbff) }, ARIAL24 } //


};

vector<Resources::MusicInfo> Resources::musics_ {
//
		{ Beat, "./resources/sound/beat.wav" }, //
		{ Cheer, "./resources/sound/cheer.wav" }, //
		{ Boooo, "./resources/sound/boooo.wav" }, //
		{ ImperialMarch, "./resources/sound/imperial_march.wav"} //
};

vector<Resources::SoundInfo> Resources::sounds_ {
//
		{ Wall_Hit, "./resources/sound/wall_hit.wav" }, //
		{ Paddle_Hit, "./resources/sound/paddle_hit.wav" }, //
		{ RetroGameOverSound, "./resources/sound/game-over.mp3" }, //
		{ BonusBellSound, "./resources/sound/bonus-bell.mp3" }, //
		{ Explosion, "./resources/sound/explosion.wav"} //
};

