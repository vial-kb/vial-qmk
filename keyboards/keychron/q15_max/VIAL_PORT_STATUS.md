# Keychron Q15 Max Vial Port Status

## Summary
Initial port of Keychron Q15 Max from wireless_playground branch to Vial branch.

## What's Completed
✅ **Structure Created**:
- Default keymap (from VIA implementation)
- Vial keymap with proper directory structure
- vial.json with full 66-key layout
- Unique Vial UID: `{0xB5, 0xBE, 0xB0, 0x9E, 0xFF, 0xD8, 0x80, 0x9E}`
- Unlock combo: ESC + Enter (rows 1,2 cols 0,12)
- config.h with 8 layers support
- rules.mk with Vial/VialRGB enabled

✅ **Adaptations Made**:
- Removed wireless dependencies (not available in Vial branch)
- Created simplified q15_max_vial.c without wireless features
- Changed RGB driver from snled27351_spi to snled27351
- Added keyboard.json for Vial compatibility

## Current Issue
⚠️ **Compilation Error**: I2C peripheral configuration mismatch
- The STM32F401 MCU configuration expects I2C peripherals
- ChibiOS version differences between branches causing build issues

## Next Steps to Complete Port
1. **Option A: Full Peripheral Configuration**
   - Add proper halconf.h and mcuconf.h files
   - Configure I2C, SPI peripherals matching STM32F401 requirements
   - Port missing driver files from wireless_playground

2. **Option B: Simplified Build**
   - Disable I2C in features
   - Create minimal peripheral configuration
   - Focus on core keyboard functionality without advanced features

3. **Option C: Wait for Upstream Updates**
   - The Vial branch may need updates to support newer Keychron boards
   - STM32F401 with wireless features is newer than typical Vial boards

## Files Created/Modified
- `/keyboards/keychron/q15_max/` - Entire directory structure
- `/keyboards/keychron/q15_max/ansi_encoder/keymaps/vial/` - Complete Vial keymap
- `/keyboards/keychron/q15_max/q15_max_vial.c` - Simplified main file
- `/keyboards/keychron/q15_max/ansi_encoder/keyboard.json` - Board configuration

## Testing Status
- ❌ Compilation fails due to peripheral configuration
- ⚠️ Firmware not yet flashable
- ✅ Vial structure and configuration complete

## Notes
- Wireless features (Bluetooth, 2.4GHz) are not available in Vial branch
- RGB Matrix with 47 effects should work once compilation succeeds
- All 32 custom macros from delilah keymap are preserved
- Encoder support included in configuration