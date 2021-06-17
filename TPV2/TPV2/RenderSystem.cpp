#include "RenderSystem.h"

#include "ecs.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "SDL_macros.h"
#include "SDLGame.h"

#include "Image.h"
#include "Transform.h"
#include "Texture.h"

RenderSystem::RenderSystem() :
		System(ecs::_sys_Render) {
}

void RenderSystem::update() {
	for (auto &e : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
		drawImage(e); // auto cast from unique_ptr to Entity*
	}

	for (auto &e : mngr_->getGroupEntities(ecs::_grp_Bullets))
		drawImage(e); // auto cast from unique_ptr to Entity*

	drawCtrlMessages();
	drawScore();
	drawNames();
}

void RenderSystem::drawImage(Entity *e) {
	Transform *tr = e->getComponent<Transform>(ecs::Transform);
	Texture *tex = e->getComponent<Image>(ecs::Image)->tex_;

	SDL_Rect dest =
	RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
			tr->height_);
	tex->render(dest, tr->rotation_);
}

void RenderSystem::drawCtrlMessages() {
	auto game = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);
	
	auto gameState = game->getState();
	
	auto gameScoreF0 = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->getScore(0);
	auto gameScoreF1 = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->getScore(1);

	if (!mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->isReady()) {
		auto msgTex = game_->getTextureMngr()->getTexture(
			Resources::WaitingForPlayer);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}else if (gameState != GameCtrlSystem::RUNNING) {
		auto msgTex = game_->getTextureMngr()->getTexture(
				Resources::PressEnter);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}

	Texture* msgTex = nullptr;

	if (gameState == GameCtrlSystem::GAMEOVER) {
		if (gameScoreF0 == 3) {
			if (gameScoreF1 == 3) 
				msgTex = game_->getTextureMngr()->getTexture(Resources::Draw);
			
			else if(mngr_->getClientId() == 0)
				msgTex = game_->getTextureMngr()->getTexture(Resources::YouWin);

			else 
				msgTex = game_->getTextureMngr()->getTexture(Resources::YouLost);
		}
		else if(mngr_->getClientId() == 0)
			msgTex = game_->getTextureMngr()->getTexture(Resources::YouLost);
		else
			msgTex = game_->getTextureMngr()->getTexture(Resources::YouWin);

		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - msgTex->getHeight()) / 2);
	}

}

void RenderSystem::drawScore() {
	auto gameCtrl = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	Texture scoreTex(game_->getRenderer(),
			to_string(gameCtrl->getScore(0)) + " - "
					+ to_string(gameCtrl->getScore(1)),
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0x111122ff) });
	scoreTex.render(game_->getWindowWidth() / 2 - scoreTex.getWidth() / 2, 10);
}

void RenderSystem::drawNames()
{
	auto gameCtrl = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	if (gameCtrl->isReady()) {		
		if (mngr_->getClientId() == 0) {
			Texture namef0(game_->getRenderer(),
				mngr_->getName(),
				game_->getFontMngr()->getFont(Resources::ARIAL24),
				{ COLOR(0xFFFFFFFF) });

			Texture namef1(game_->getRenderer(),
				mngr_->getRivalName(),
				game_->getFontMngr()->getFont(Resources::ARIAL24),
				{ COLOR(0x010101FF) });
			namef0.render(game_->getWindowWidth() / 4 - namef0.getWidth() / 2, 10);
			namef1.render(game_->getWindowWidth() * 3 / 4 - namef1.getWidth() / 2, 10);
		}
		else {
			Texture namef0(game_->getRenderer(),
				mngr_->getRivalName(),
				game_->getFontMngr()->getFont(Resources::ARIAL24),
				{ COLOR(0x010101FF) });

			Texture namef1(game_->getRenderer(),
				mngr_->getName(),
				game_->getFontMngr()->getFont(Resources::ARIAL24),
				{ COLOR(0xFFFFFFFF) });
			namef0.render(game_->getWindowWidth() / 4 - namef0.getWidth() / 2, 10);
			namef1.render(game_->getWindowWidth() * 3 / 4 - namef1.getWidth() / 2, 10);
		}
	}
	else {
		Texture name(game_->getRenderer(),
			mngr_->getName(),
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0XFFFFFFFF) });
		if (mngr_->getClientId() == 0) {
			name.render(game_->getWindowWidth() / 4 - name.getWidth() / 2, 10);
		}
		else {
			name.render(game_->getWindowWidth() * 3 / 4 - name.getWidth() / 2, 10);
		}
	}
}
