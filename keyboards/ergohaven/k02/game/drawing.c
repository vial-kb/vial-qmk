// Include TMK Core library
#include "timer.h"

#include QMK_KEYBOARD_H
#include "font_block.h"

#include "game/drawing.h"
#include "game/invader.c"

/*************************************************************************
  Initialization
**************************************************************************/
static const Vec2 dir_vec[] = {
    { 0, 0}, // DIR_STAY
    { 1, 0}, // DIR_RIGHT
    {-1, 0}, // DIR_LEFT
    { 0, 1}, // DIR_DOWN
    { 0, -1} // DIR_UP
};


/*************************************************************************
  Functions related to the Character-type instances
**************************************************************************/
void calcCharWIdx(Character *character) {
    character->wIdx = character->pos.y * DISPLAY_WIDTH + character->pos.x;
}

void setCharRIdx(Character *character, int enemy_type) {
    switch (enemy_type) {
        case ENEMY_ONE: // 0
            character->rIdx = ENEMY1_R_IDX;
            character->fire_rIdx = ENEMY1_F_R_IDX;
            character->dead_rIdx = DEAD_E1_R_IDX;
            break;
        case ENEMY_TWO: // 1
            character->rIdx = ENEMY2_R_IDX;
            character->fire_rIdx = ENEMY2_F_R_IDX;
            character->dead_rIdx = DEAD_E2_R_IDX;
            break;
        case ENEMY_THREE: // 2
            character->rIdx = ENEMY3_R_IDX;
            character->fire_rIdx = ENEMY3_F_R_IDX;
            character->dead_rIdx = DEAD_E3_R_IDX;
            break;
        default:
            break;
    }
}

void setCharRIdxForStage(Character *character, Stage stage, int line) {
    switch (stage) {
        case STAGE_ONE:
            setCharRIdx(character, ENEMY_ONE);
            break;
        case STAGE_TWO:
            if (line < 1) { // line 0 (rear)
                setCharRIdx(character, ENEMY_TWO);
            } else { // line 1-2 (front)
                setCharRIdx(character, ENEMY_ONE);
            }
            break;
        case STAGE_THREE:
            if (line < 2) { // line 0-1 (rear)
                setCharRIdx(character, ENEMY_TWO);
            } else { // line 2-3 (front)
                setCharRIdx(character, ENEMY_ONE);
            }
            break;
        case STAGE_FOUR:
            if (line < 1) { // line 0 (rear)
                setCharRIdx(character, ENEMY_THREE);
            } else if (line < 2) { // line 1 (middle)
                setCharRIdx(character, ENEMY_TWO);
            } else { // line 2-3 (front)
                setCharRIdx(character, ENEMY_ONE);
            }
            break;
        case STAGE_FIVE:
            if (line < 1) { // line 0 (rear)
                setCharRIdx(character, ENEMY_THREE);
            } else if (line < 3) { // line 1-2 (middle)
                setCharRIdx(character, ENEMY_TWO);
            } else { // line 3-4 (front)
                setCharRIdx(character, ENEMY_ONE);
            }
            break;
        case STAGE_EXTRA:
            if (line < 2) { // line 0-1 (rear)
                setCharRIdx(character, ENEMY_THREE);
            } else if (line < 4) { // line 2-3 (middle)
                setCharRIdx(character, ENEMY_TWO);
            } else { // line 4 (front)
                setCharRIdx(character, ENEMY_ONE);
            }
            break;
        default:
            break;
    }
}

void setCharDir(Character *character, int direction) {
    character->dir = direction;
    character->vDir = dir_vec[direction];
}

void moveCharacter(Character *character) {
    character->pos.x += character->vDir.x;
    character->pos.y += character->vDir.y;
}

void ejectCharacter(Character *character, uint16_t *pTimer) {
    if (!character->isAlive && !character->isAnimating) {
        character->pos.x = -3;
        character->pos.y = -3;
        character->isEjected = 1;
        *(character->num) -= 1; // Subtract 1 from the number of the alive characters
        *pTimer = *(character->num) == 0 // Check whether all characters are destroyed
                ? timer_read() // If so, reset main_timer
                : *pTimer;
    }
}

void drawCharacter(const Character *character) {
    if (character->pos.x < 0) { // If the character is on left-end
        write_font_blocks(invader_font, 1, 1, character->rIdx + 1, character->wIdx + 1);
    } else if (DISPLAY_WIDTH - 1 <= character->pos.x) { // If the character is on right-end
        write_font_blocks(invader_font, 1, 1, character->rIdx, character->wIdx);
    } else {
        write_font_blocks(invader_font, 1, 2, character->rIdx, character->wIdx);
    }
}

void clearCharacter(const Character *character) {
    if (character->pos.x < 0) {
        clear_block(character->wIdx + 1);
    } else if (DISPLAY_WIDTH - 1 <= character->pos.x) {
        clear_block(character->wIdx);
    } else {
        clear_block(character->wIdx);
        clear_block(character->wIdx + 1);
    }
}


/*************************************************************************
  Functions related to the Beam-type instances
**************************************************************************/
void calcBeamWIdx(Beam *beam) {
    beam->wIdx = beam->pos.y * DISPLAY_WIDTH + beam->pos.x;
}

void setBeamRIdx(const Character *character, Beam *beam) {
    // Exit if the number of beams reaches its max
    if (*(beam->max) <= *(beam->num)) {
        return;
    }

    for (int i = 0; i < *(beam->max); i++) {
        // Search for the beam that has yet to be fired
        if ((beam + i)->isFired) {
            continue;
        }
        // These cases are divided by the Character type
        switch (character->org_rIdx) {
            case PLAYER_R_IDX:
                (beam + i)->rIdx = BEAM_P_R_IDX;
                break;
            case ENEMY1_R_IDX:
                (beam + i)->rIdx = BEAM_E1_R_IDX;
                break;
            case ENEMY2_R_IDX:
                (beam + i)->rIdx = BEAM_E2_R_IDX;
                break;
            case ENEMY3_R_IDX:
                (beam + i)->rIdx = BEAM_E3_R_IDX;
                break;
            default:
                break;
        }
        (beam + i)->org_rIdx = (beam + i)->rIdx;
        return; // Exit once the unfired beam is found
    }
}

void fireBeam(Character *character, Beam *beam) {
    // Exit if the number of beams reaches its max
    if (*(beam->max) <= *(beam->num)) {
        return;
    }

    // The animation of the beam starts above the player or below the enemy
    int pos_y = (beam->fromPlayer == 1
                ? character->pos.y - 2   // Player
                : character->pos.y + 1); // Enemy

    for (int i = 0; i < *(beam->max); i++) {
        // Search for the beam that has yet to be fired
        if (!(beam + i)->isFired) {
            (beam + i)->isFired = 1;
            (beam + i)->pos.x = character->pos.x;
            (beam + i)->pos.y = pos_y;
            (beam + i)->timer = timer_read();
            *(beam->num) += 1;
            character->isFiring = 1;
            calcBeamWIdx(beam + i);
            return; // Exit once the unfired beam is found
        }
    }
}

void moveBeam(Beam *beam){
    if ((beam->isFired) && (beam->fromPlayer) && (-1 <= beam->pos.y)) {
        beam->pos.y--; // Move player's beam upwards
    } else if ((beam->isFired) && (!beam->fromPlayer) && (beam->pos.y <= DISPLAY_HEIGHT)) {
        beam->pos.y++; // Move enemy's beam downwards
    } else {
        // Remove a beam
        beam->isFired = 0;
        beam->pos.x = -3;
        beam->pos.y = -3;
        beam->timer = 0;
        if (1 <= *(beam->num)) {
            *(beam->num) -= 1;
        }
    }
}

void drawBeam(const Beam *beam) {
    if (beam->isFired) {
        if (beam->fromPlayer && beam->pos.x < 0) {
            write_font_blocks(invader_font, 2, 1, beam->rIdx + 4, beam->wIdx + 1);
        } else {
            write_font_blocks(invader_font, 2, 1, beam->rIdx, beam->wIdx);
        }
    }
}

void clearBeam(const Beam *beam) {
    // Beam's on left-end
    if (beam->pos.x < 0) {
        clear_block(beam->wIdx + 1);
    // Player's beam
    } else if (beam->fromPlayer && -1 <= beam->pos.y) {
        clear_block(beam->wIdx);
        clear_block(beam->wIdx + DISPLAY_WIDTH);
    // Enemy's beam
    } else if (!beam->fromPlayer && beam->pos.y < DISPLAY_HEIGHT) {
        clear_block(beam->wIdx);
        clear_block(beam->wIdx + DISPLAY_WIDTH);
    }
}


/*************************************************************************
  Functions for animations
**************************************************************************/
void updateCharAnim(Character *character, uint8_t num_frame) {
    // Start the loop
    if (!character->isAnimating) {
        if (!character->isAlive && !character->wasAnimated) {
            character->isAnimating = 1;
            character->timer = timer_read();
            character->rIdx = character->dead_rIdx;
        }
    // If the loop reaches specified frame, stop it and reset some variables.
    } else if (character->rIdx >= character->dead_rIdx + (num_frame - 1) * 2) {
        // Stop the animation here
        character->isAnimating = 0;
        character->wasAnimated = 1;
        character->timer = 0;
        character->rIdx = character->org_rIdx;
    // Move read-index every 1 frame
    } else if (timer_elapsed(character->timer) % ANIME_INTERVAL == 0) {
        character->rIdx += 2; // 1 character has 2 blocks
    }
}

void updateBeamAnim(Beam *beam) {
    if (!beam->isFired) {
        return;
    }

    // Stop a loop when it reaches the end
    if (beam->rIdx >= beam->org_rIdx + 3) {
        moveBeam(beam);
        calcBeamWIdx(beam);
        beam->timer = timer_read();
        beam->rIdx = beam->org_rIdx;
        clearBeam(beam);
        drawBeam(beam);
    // Draw animated beams
    } else {
        beam->rIdx++; // Go on to the next frame
        clearBeam(beam);
        drawBeam(beam);
    }
}

void drawDeadPlayerAnim(Character *character, Event *game_event) {
    updateCharAnim(character, 4);
    if (timer_elapsed(character->timer) % ANIME_INTERVAL == 0) {
        if (character->wasAnimated) {
            *game_event = GAME_OVER;
        } else {
            oled_clear();
            drawCharacter(character);
        }
    }
}


/*************************************************************************
  Functions for drawing the whole display
**************************************************************************/
void drawEvent(uint8_t upper_rIdx, uint8_t lower_rIdx) {
    // Draw events using OLED fonts of 2 rows & 5 cols
    write_font_blocks(invader_font, 2, 5, upper_rIdx, /* upper_wIdx = */ 25);
    write_font_blocks(invader_font, 2, 5, lower_rIdx, /* lower_wIdx = */ 35);
}

void drawStage(uint8_t upper_rIdx, uint8_t lower_rIdx) {
    // Draw "Stage" using OLED fonts of 2 rows & 5 cols
    write_font_blocks(invader_font, 2, 5, upper_rIdx, /* upper_wIdx = */ 25);
    // Draw stage-number using OLED fonts of 2 rows & 1 cols
    write_font_blocks(invader_font, 2, 1, lower_rIdx, /* lower_wIdx = */ 37);
}
