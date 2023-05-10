#ifndef GAME_H
#define GAME_H

extern void readMainTimer(void);
extern uint16_t countMainTimer(void);
extern void movePlayer(uint8_t isLeft);
extern void firePlayerBeam(void);
extern void toggleGamingMode(void);
extern uint8_t isGamingMode(void);
extern void startGame(void);

extern void initGame(void);
extern void game_main(void);

#endif // GAME_H
