#include "game.h"
#include "actuator.h"
#include "archive.h"
#include "render.h"
#include "stage.h"
#include "assets/sheetassets.h"
#include "core/assets/imageassets.h"
#include "inf/audio.h"
#include "inf/log.h"

ImageAssets* IMG;
SheetAssets* SHEET;
Stage* STAGE;
Render* RENDER;
Actuator* ACT;
ChibiLog* LOG;
Archive* ARC;
Audio* AUD;


Game::Game() {
    IMG=new ImageAssets;
    RENDER=new Render(128,128);
    STAGE=new Stage;
    ARC=new Archive;
    LOG=new ChibiLog;
    ACT=new Actuator;
    AUD=new Audio;
    SHEET=new SheetAssets;
}

void Game::save()
{

}

void Game::load()
{

}

void Game::sleep()
{

}

void Game::awake()
{

}

void Game::fresh(){
    if(running)return;
    STAGE->Fresh();
    RENDER->fresh();
    ACT->Fresh();
}
