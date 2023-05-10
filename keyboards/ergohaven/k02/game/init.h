#ifndef INIT_H
#define INIT_H

/*************************************************************************
  Definition
**************************************************************************/
#define DISPLAY_WIDTH 5
#define DISPLAY_HEIGHT 16

#define ENEMY_HRZN 2
#define ENEMY_VERT 6
#define MAX_NUM_ENEMY (ENEMY_VERT * ENEMY_HRZN)
#define NUM_PLAYER 1

#define MAX_PLAYER_BEAMS 3
#define MAX_ENEMY_BEAMS 5

// Intervals as milliseconds
#define ENEMY_INTERVAL 300
#define BEAM_INTERVAL (60 * 3)
#define FIRE_INTERVAL (75 * 2)
#define HIT_INTERVAL 35
#define ANIME_INTERVAL 80
#define EVENT_INTERVAL 200


/*************************************************************************
  Specify which position this program reads from the OLED font
**************************************************************************/
// Characters
#define PLAYER_R_IDX 0x40
#define ENEMY1_R_IDX 0x42
#define ENEMY2_R_IDX 0x46
#define ENEMY3_R_IDX 0x4a
// Enemies(firing)
#define ENEMY1_F_R_IDX 0x44
#define ENEMY2_F_R_IDX 0x48
#define ENEMY3_F_R_IDX 0x4c
// Beams
#define BEAM_P_R_IDX 0x80
#define BEAM_P_L_R_IDX 0x84 // player's beam(on left-end)
#define BEAM_E1_R_IDX 0x88
#define BEAM_E2_R_IDX 0x8c
#define BEAM_E3_R_IDX 0x90
// Animations
#define DEAD_P_R_IDX 0x60
#define DEAD_E1_R_IDX 0x68
#define DEAD_E2_R_IDX 0x70
#define DEAD_E3_R_IDX 0x78
// Effects
#define BOMB_R_IDX 0xc0
// Events
#define GAME_R_IDX 0x01
#define START_R_IDX 0x06
#define OVER_R_IDX 0x0b
#define CLEAR_R_IDX 0x10
// Stages
#define STAGE_R_IDX 0x15
#define ONE_R_IDX 0x1a
#define TWO_R_IDX 0x1b
#define THREE_R_IDX 0x1c
#define FOUR_R_IDX 0x1d
#define FIVE_R_IDX 0x1e
#define EXTRA_R_IDX 0x1f

enum {
    ENEMY_ONE,
    ENEMY_TWO,
    ENEMY_THREE
};

enum {
    DIR_STAY,  // 0
    DIR_RIGHT, // 1
    DIR_LEFT,  // 2
    DIR_DOWN,  // 3
    DIR_UP     // 4
};

typedef struct {
    int x,y;
} Vec2;

typedef struct {
    Vec2 pos;            // position
    int dir;             // direction
    Vec2 vDir;           // direction-vector
    uint8_t rIdx;        // read-index on OLED font (Helix type)
    uint8_t wIdx;        // write-index on OLED display
    uint8_t isAlive;     // whether alive or NOT
    uint8_t isFiring;    // whether attacking or not
    uint8_t *num;        // pointer to the number of alive instances
    uint16_t timer;      // timer variable to draw an animation
    uint8_t org_rIdx;    // original read-index
    uint8_t fire_rIdx;   // firing read-index
    uint8_t dead_rIdx;   // dead-animation read-index
    uint8_t isAnimating; // whether it's being animated or NOT
    uint8_t wasAnimated; // whether its animating was finished or NOT
    uint8_t isEjected;   // whether it's ejected or NOT
} Character;

typedef struct {
    Vec2 pos;            // position
    uint8_t rIdx;        // read-index on OLED font (Helix type)
    uint8_t wIdx;        // write-index on OLED display
    uint8_t isFired;     // whether it's fired or NOT
    uint8_t fromPlayer;  // whether it's fired from a player or NOT
    uint8_t *num;        // pointer to the number of instances
    uint8_t *max;        // pointer to the max of instances
    uint16_t timer;      // timer variable to draw an animation
    uint8_t org_rIdx;    // original read-index
} Beam;

typedef enum {
    NONE,
    SOMETHING,
    GAME_START,
    GAME_OVER,
    STAGE_CLEAR,
    NEXT_STAGE,
    GAME_CLEAR
} Event;

typedef enum {
    STAGE_ONE,
    STAGE_TWO,
    STAGE_THREE,
    STAGE_FOUR,
    STAGE_FIVE,
    STAGE_EXTRA
} Stage;

#endif // INIT_H
