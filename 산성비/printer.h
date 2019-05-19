#pragma once

#include "rainDropMng.h"
#include "gamePlay.h"

void scoreUpdate(RAINDROP_LIST raindropList, int idx, STATUS *stat);
void speedUpdate(STATUS *stat);
void statPrint(REMAIN remain);
void scorePrint(STATUS stat);
void speedPrint(STATUS stat);
void printAll(REMAIN remain, STATUS stat);