---
description: workflow for implementing OLED UI designs on the Bipedal Southpaw keyboard
---

# OLED UI Implementation Workflow

This workflow describes how to implement OLED UI designs for the Bipedal Southpaw keyboard (RP2040, 128x32 OLED).

## Display Specifications
- **Resolution:** 128 × 32 pixels
- **Color depth:** 1-bit (black and white)
- **Driver:** SSD1306
- **Memory:** RP2040 has 2MB flash (plenty for graphics)

## Step 1: Receive Design Assets

The user will provide:
- **Static screens:** PNG/JPG images (ideally 128x32, 1-bit)
- **State descriptions:** What each screen represents (e.g., "Layer 0, Mouse mode")
- **Animation frames:** If animated, multiple frames with timing info
- **Transition logic:** When/how to switch between states

## Step 2: Convert Images to Byte Arrays

For each image:
1. Resize to 128x32 if needed
2. Convert to 1-bit (black and white, no grayscale)
3. Generate C byte array in column-major format (QMK OLED format)

// turbo
Use this Python script to convert:
```bash
python3 /path/to/convert_oled_image.py input.png output_array_name
```

Or manually convert using online tools like:
- https://javl.github.io/image2cpp/ (select "Arduino" format, vertical byte orientation)

## Step 3: Implement in Code

### For static screens:
```c
static const char PROGMEM screen_name[] = {
    // 512 bytes for 128x32 display
};

void render_screen_name(void) {
    oled_write_raw_P(screen_name, sizeof(screen_name));
}
```

### For state-based rendering:
```c
bool oled_task_user(void) {
    switch (current_state) {
        case STATE_A:
            oled_write_raw_P(screen_a, sizeof(screen_a));
            break;
        case STATE_B:
            oled_write_raw_P(screen_b, sizeof(screen_b));
            break;
    }
    return false;
}
```

### For animations:
```c
static uint32_t anim_timer = 0;
static uint8_t current_frame = 0;
const char* frames[] = {frame_0, frame_1, frame_2};

bool oled_task_user(void) {
    if (timer_elapsed32(anim_timer) > FRAME_DURATION) {
        current_frame = (current_frame + 1) % NUM_FRAMES;
        anim_timer = timer_read32();
    }
    oled_write_raw_P(frames[current_frame], 512);
    return false;
}
```

## Step 4: Test and Iterate

// turbo
1. Build firmware:
```bash
cd /Users/matthewthomas/dev/vial-qmk && make hidpress/bipedalsouthpaw:vial
```

2. Flash and verify on device
3. Adjust timing, transitions, or graphics as needed

## File Locations
- **Graphics header:** `keyboards/hidpress/bipedalsouthpaw/oled_graphics.h`
- **OLED logic:** `keyboards/hidpress/bipedalsouthpaw/bipedalsouthpaw.c`
- **Conversion scripts:** `keyboards/hidpress/bipedalsouthpaw/tools/`

## Example Request Format

When providing designs, include:
```
**Screen name:** layer_0_mouse_mode
**State:** Layer 0, Mouse mode active
**Image:** [attached 128x32 PNG]
**Notes:** Should show mouse cursor icon and "L0" text
```

For animations:
```
**Animation name:** mode_transition
**Frames:** [frame1.png, frame2.png, frame3.png]
**Frame duration:** 50ms
**Trigger:** When mode changes via TMB_MODE
```
