// Include TMK Core library
#include "timer.h"

#include QMK_KEYBOARD_H
#include "font_block.h"
#include "rndgen.h"

#include "game/init.h"
#include "game/drawing.h"
#include "game/game.h"

/*************************************************************************
  Initialization
**************************************************************************/
static uint8_t gaming_mode = 0;
static uint16_t main_timer = 0;

static Character player[NUM_PLAYER];
static Character enemies[MAX_NUM_ENEMY];
static uint8_t num_player = NUM_PLAYER; // 1
static uint8_t all_enemies = MAX_NUM_ENEMY; // 12
static uint8_t num_enemies = MAX_NUM_ENEMY; // 12

static Beam player_beams[MAX_PLAYER_BEAMS];
static uint8_t num_player_beams = 0;
static uint8_t max_player_beams = MAX_PLAYER_BEAMS; // 3
static Beam enemy_beams[MAX_ENEMY_BEAMS];
static uint8_t num_enemy_beams = 0;
static uint8_t max_enemy_beams = MAX_ENEMY_BEAMS; // 5
static uint16_t beam_e_clock = 0;

static Event game_event;
static Stage current_stage;
static const uint8_t stages[6] = {ONE_R_IDX, TWO_R_IDX, THREE_R_IDX, FOUR_R_IDX, FIVE_R_IDX, EXTRA_R_IDX};
static Rndgen rng;


/*************************************************************************
  A function to update the whole display
**************************************************************************/
void updateScreen(void) {
    // Draw events
    switch (game_event) {
        case GAME_START:
            drawEvent(GAME_R_IDX, START_R_IDX);
            break;
        case STAGE_CLEAR:
            drawEvent(STAGE_R_IDX, CLEAR_R_IDX);
            break;
        case GAME_CLEAR:
            drawEvent(GAME_R_IDX, CLEAR_R_IDX);
            break;
        case GAME_OVER:
            drawEvent(GAME_R_IDX, OVER_R_IDX);
            break;
        case NEXT_STAGE:
            drawStage(STAGE_R_IDX, stages[current_stage]);
            break;
        default:
            break;
    }

    // There are only non-event blocks below
    if (game_event != NONE) {
        return;
    }

    // Draw all beams
    for (int i = 0; i < max_player_beams; i++) {
        drawBeam(player_beams + i);
    }
    for (int i = 0; i < max_enemy_beams; i++) {
        drawBeam(enemy_beams + i);
    }

    // Draw a player
    drawCharacter(player);

    // Draw enemies
    for (int i = 0; i < all_enemies; i++) {
        // An enemy is alive
        if ((enemies + i)->isAlive) {
            (enemies + i)->rIdx = ((enemies + i)->isFiring
                                ? (enemies + i)->fire_rIdx
                                : (enemies + i)->org_rIdx);
            drawCharacter(enemies + i);
        // Not alive and its animation is not fully drawn
        } else if (!(enemies + i)->wasAnimated) {
            drawCharacter(enemies + i);
        }
    }
}


/*************************************************************************
  Functions for accessing the global variables from keymap.c
**************************************************************************/
void readMainTimer(void) {
    main_timer = timer_read();
}

uint16_t countMainTimer(void) {
    return timer_elapsed(main_timer);
}

void movePlayer(uint8_t isLeft) {
    if (game_event != NONE) {
        return;
    }

    if (isLeft) {
        if (player->pos.x >= 0) {
            player->pos.x--;
            calcCharWIdx(player);
            moveCharacter(player);
            oled_clear();
            updateScreen();
        }
    } else { // isRight
        if (player->pos.x < DISPLAY_WIDTH - 1) {
            player->pos.x++;
            calcCharWIdx(player);
            moveCharacter(player);
            oled_clear();
            updateScreen();
        }
    }
}

void firePlayerBeam(void) {
    if (game_event == NONE) {
        fireBeam(player, player_beams);
    }
}

void toggleGamingMode(void) {
    gaming_mode ^= 1;
}

uint8_t isGamingMode(void) {
    return gaming_mode;
}

void startGame(void) {
    game_event = GAME_START;
    current_stage = STAGE_ONE;
}


/*************************************************************************
  Functions for initialization
**************************************************************************/
void initCharacter(Character *character, int i, int j) {
    character->isAlive = 1;
    character->isFiring = 0;
    character->isAnimating = 0;
    character->wasAnimated = 0;
    character->isEjected = 0;
    character->timer = 0;

    if (character == player) {
        character->num = &num_player;
        character->pos.y = DISPLAY_HEIGHT - 1;
        character->pos.x = DISPLAY_WIDTH / 2;
        character->rIdx = PLAYER_R_IDX;
        character->org_rIdx = character->rIdx;
        character->fire_rIdx = PLAYER_R_IDX;
        character->dead_rIdx = DEAD_P_R_IDX;
        calcCharWIdx(character);
        setCharDir(character, DIR_STAY);
    } else { // Enemy
        character->num = &num_enemies;
        character->pos.y = i * 2;
        character->pos.x = j * 3;
        setCharRIdxForStage(character, current_stage, i);
        character->org_rIdx = character->rIdx;
        calcCharWIdx(character);
    }
}

void initBeam(Beam *beam) {
    beam->isFired = 0;
    beam->timer = 0;
    beam->pos.y = -3;
    beam->pos.x = -3;

    if (beam->fromPlayer) {
        beam->num = &num_player_beams;
        beam->max = &max_player_beams;
        beam->rIdx = BEAM_P_R_IDX;
    } else { // Enemy's beam
        beam->num = &num_enemy_beams;
        beam->max = &max_enemy_beams;
        // We'll update this rIdx within setBeamRIdx() when an enemy fires a beam
        beam->rIdx = BEAM_E1_R_IDX;
    }
    beam->org_rIdx = beam->rIdx;
    calcBeamWIdx(beam);
}

void initGame(void) {
    // Initialization for a player
    num_player = NUM_PLAYER; // This stores the number of player (Of course it's 1)
    initCharacter(player, 0, 0);

    // Initialization for all enemies
    uint8_t enemy_vert = ENEMY_VERT - 3; // 3
    switch (current_stage) {
        case STAGE_THREE:
        case STAGE_FOUR:
            enemy_vert = ENEMY_VERT - 2; // 4
            break;
        case STAGE_FIVE:
            enemy_vert = ENEMY_VERT - 1; // 5
            break;
        case STAGE_EXTRA:
            enemy_vert = ENEMY_VERT; // 6
            break;
        default:
            break;
    }
    all_enemies = enemy_vert * ENEMY_HRZN; // This stores the number of all enemies
    num_enemies = all_enemies; // This stores the number of currently ALIVE enemies
    for (int i = 0; i < enemy_vert; i++) {
        for (int j = 0; j < ENEMY_HRZN; j++) {
            int p = i * ENEMY_HRZN + j; // Calculate a position of an enemy
            initCharacter(enemies + p, i, j);

            // Check whether an enemy's pos is right-end
            (p % ENEMY_HRZN != ENEMY_HRZN - 1) \
                ? setCharDir(enemies + p, DIR_RIGHT) // NOT right-end
                : setCharDir(enemies + p, DIR_STAY); // right-end
        }
    }

    // Initialization for player's beams
    num_player_beams = 0; // This stores the number of currently fired player's beams
    max_player_beams = MAX_PLAYER_BEAMS;
    for (int i = 0; i < max_player_beams; i++) {
        (player_beams + i)->fromPlayer = 1;
        initBeam(player_beams + i);
    }

    // Initialization for enemies' beams
    num_enemy_beams = 0; // This stores the number of currently fired enemies' beams
    beam_e_clock = 0; // Reset the clock for enemy's beam
    switch (current_stage) {
        case STAGE_ONE:
            max_enemy_beams = MAX_ENEMY_BEAMS - 3; // 2
            break;
        case STAGE_TWO:
        case STAGE_THREE:
            max_enemy_beams = MAX_ENEMY_BEAMS - 2; // 3
            break;
        case STAGE_FOUR:
            max_enemy_beams = MAX_ENEMY_BEAMS - 1; // 4
            break;
        case STAGE_FIVE:
        case STAGE_EXTRA:
            max_enemy_beams = MAX_ENEMY_BEAMS; // 5
            break;
        default:
            break;
    }
    for (int i = 0; i < max_enemy_beams; i++) {
        (enemy_beams + i)->fromPlayer = 0;
        initBeam(enemy_beams + i);
    }

    // Initialization for randomization
    uint16_t t = timer_read();
    init_rng(&rng, t, (t >> 8), 0, 1, 0);
}


/*************************************************************************
  Main function
**************************************************************************/
void game_main(void) {
    // Game-starting block
    if (game_event == GAME_START && countMainTimer() > 1500) {
        game_event = NEXT_STAGE;
        readMainTimer();
    }

    // Stage-setting block
    if (game_event == STAGE_CLEAR && countMainTimer() > 2000) {
        current_stage++;
        game_event = NEXT_STAGE;
        readMainTimer();
    }

    // Stage-displaying block
    if (game_event == NEXT_STAGE && countMainTimer() > 1500) {
        game_event = NONE;
        readMainTimer();
        initGame(); // Go on to next stage
    }

    // Clear-judging block
    if (game_event == NONE && num_enemies == 0 && countMainTimer() > 300) {
        game_event = (current_stage == STAGE_EXTRA ? GAME_CLEAR : STAGE_CLEAR);
        readMainTimer();
    }

    // If some event happens
    if (game_event != NONE) {
        // Player's dead animation block
        if (!player->isAlive && game_event != GAME_OVER) {
            drawDeadPlayerAnim(player, &game_event);
        // Events-displaying block
        } else {
            if (countMainTimer() % EVENT_INTERVAL == 0) {
                oled_clear();
                updateScreen();
            }
        }
        // You'll be out of main loop here if some event happens
        return;
    }

    // Hit-detection block
    if (countMainTimer() % HIT_INTERVAL == 0) {
        // Player's hit detection
        for (int i = 0; i < max_enemy_beams; i++) {
            if (!(enemy_beams + i)->isFired) {
                continue;
            }

            // If beams hit a player, the game is over.
            if ((enemy_beams + i)->pos.x == player->pos.x
                && (enemy_beams + i)->pos.y + 1 == player->pos.y) {
                game_event = SOMETHING; // Turn the event flag on
                player->isAlive = 0;
            }
        }

        // Enemy's hit detection
        for (int i = 0; i < all_enemies; i++) {
            if (!(enemies + i)->isAlive) {
                continue;
            }

            // If enemies hit a player, the game is over.
            if (((enemies + i)->pos.x >= player->pos.x - 1
                && (enemies + i)->pos.y == player->pos.y)
                && ((enemies + i)->pos.x <= player->pos.x + 1
                && (enemies + i)->pos.y == player->pos.y)) {
                game_event = SOMETHING; // Turn the event flag on
                player->isAlive = 0;
            }
            for (int j = 0; j < max_player_beams; j++) {
                if (!(player_beams + j)->isFired) {
                    continue;
                }

                // If beams hit an enemy, it's destroyed
                if ((enemies + i)->pos.x == (player_beams + j)->pos.x
                    && (enemies + i)->pos.y == (player_beams + j)->pos.y) {
                    // Sweep dead enemies out of the display and leave them there
                    (enemies + i)->isAlive = 0;
                    setCharDir((enemies + i), DIR_STAY);

                    // Move the player's beam out of the display
                    (player_beams + j)->isFired = 0;
                    moveBeam(player_beams + j);
                    calcBeamWIdx(player_beams + j);

                    break; // Go on to the next enemy's hit detection
                }
            }
        }
    }

    // Enemy-moving block
    if (countMainTimer() % ENEMY_INTERVAL == 0) {
        // Move all enemies per ENEMY_INTERVAL
        for (int i = 0; i < all_enemies; i++) {
            // The position of the enemy after it moves in their current direction
            int next_pos = (enemies + i)->pos.x + (enemies + i)->vDir.x;

            // If enemies are already STAY, force them to move DOWN.
            if ((enemies + i)->dir == DIR_STAY
                    && (enemies + i)->isAlive) {
                setCharDir((enemies + i), DIR_DOWN);
            // If enemies are already DOWN and reach 2 blocks before the right end,
            // force them to turn back.
            } else if ((enemies + i)->dir == DIR_DOWN
                    && ((enemies + i)->pos.x == DISPLAY_WIDTH - 2)) {
                setCharDir((enemies + i), DIR_LEFT);
            // If enemies are already DOWN and reach the left end,
            // force them to turn back.
            } else if ((enemies + i)->dir == DIR_DOWN
                    && ((enemies + i)->pos.x == 0)) {
                setCharDir((enemies + i), DIR_RIGHT);
            // Keep an enemy moving toward current direction.
            } else if (0 <= next_pos && next_pos <= DISPLAY_WIDTH - 2) {
                setCharDir((enemies + i), (enemies + i)->dir);
            // Enemies are all STAY when they reaches the end.
            } else {
                setCharDir((enemies + i), DIR_STAY);
            }
            calcCharWIdx(enemies + i);
            moveCharacter(enemies + i);
        }
        oled_clear();
        updateScreen();
    }

    // Enemy-firing block (that is called 2 times as frequently as firing clock)
    if (countMainTimer() % (FIRE_INTERVAL / 2) == 0) {
        // Generate a random number with Xorshift
        int rnd_i = calc_rng(&rng, timer_read()) % all_enemies;
        // Enemies always shoot a beam from the nearest point to a player
        for (int i = rnd_i; i < all_enemies; i += ENEMY_HRZN) {
            if ((enemies + i)->isAlive) {
                rnd_i = i;
            }
        }
        // Reset firing animation
        if ((enemies + rnd_i)->isFiring == 1) {
            (enemies + rnd_i)->isFiring = 0;
        }
        // The randomly chosen enemy fires every 350+ milliseconds
        if (countMainTimer() % FIRE_INTERVAL == 0) {
            if ((enemies + rnd_i)->isAlive && timer_elapsed(beam_e_clock) >= 350) {
                setBeamRIdx(enemies + rnd_i, enemy_beams);
                fireBeam(enemies + rnd_i, enemy_beams);
                beam_e_clock = timer_read();
            }
        }
    }

    // Enemy-animating block
    for (int i = 0; i < all_enemies; i++) {
        if ((enemies + i)->isAlive || (enemies + i)->isEjected) {
            continue;
        }

        updateCharAnim(enemies + i, 4);
        if ((enemies + i)->wasAnimated) {
            ejectCharacter(enemies + i, &main_timer);
        } else {
            drawCharacter(enemies + i);
        }
    }

    // Beam-drawing block
    if (countMainTimer() % (BEAM_INTERVAL / 3) == 0) {
        // Player's beam drawing block
        for (int i = 0; i < max_player_beams; i++) {
            updateBeamAnim(player_beams + i);
        }

        // Enemy's beam drawing block
        for (int i = 0; i < max_enemy_beams; i++) {
            updateBeamAnim(enemy_beams + i);
        }
        oled_clear();
        updateScreen();
    }
}
