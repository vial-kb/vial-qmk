#ifndef DRAWING_H
#define DRAWING_H

#include "game/init.h"

extern void calcCharWIdx(Character *character);
extern void setCharRIdxForStage(Character *character, Stage stage, int line);
extern void setCharDir(Character *character, int direction);
extern void moveCharacter(Character *character);
extern void ejectCharacter(Character *character, uint16_t *timer);
extern void drawCharacter(const Character *character);

extern void calcBeamWIdx(Beam *beam);
extern void setBeamRIdx(const Character *character, Beam *beam);
extern void fireBeam(Character *character, Beam *beam);
extern void moveBeam(Beam *beam);
extern void drawBeam(const Beam *beam);

extern void updateCharAnim(Character *character, uint8_t num_frame);
extern void updateBeamAnim(Beam *beam);
extern void drawDeadPlayerAnim(Character *character, Event *game_event);

extern void drawEvent(uint8_t upper_rIdx, uint8_t lower_rIdx);
extern void drawStage(uint8_t upper_rIdx, uint8_t lower_rIdx);

#endif // DRAWING_H
