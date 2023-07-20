#ifndef FONT_BLOCK_H
#define FONT_BLOCK_H

extern void set_rotation(uint8_t isVertical);
extern void write_font_block(const unsigned char* p, uint8_t rIdx, uint8_t wIdx);
extern void write_font_blocks(const unsigned char* p, uint8_t row, uint8_t col, uint8_t p_rIdx, uint8_t p_wIdx);
extern void clear_display(void);
extern void clear_block(uint8_t wIdx);

#endif // FONT_BLOCK_H
