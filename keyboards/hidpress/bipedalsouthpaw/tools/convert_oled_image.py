#!/usr/bin/env python3
"""
Convert an image to a C byte array for QMK OLED display.
Usage: python3 convert_oled_image.py <input_image> <array_name>

Output format is compatible with oled_write_raw_P() for 128x32 SSD1306 displays.
"""

import sys
from PIL import Image

def convert_image_to_oled_bytes(image_path, array_name):
    # Open and convert image
    img = Image.open(image_path)

    # Resize to 128x32, maintaining aspect ratio and cropping center
    target_width, target_height = 128, 32

    # Calculate aspect ratios
    img_ratio = img.width / img.height
    target_ratio = target_width / target_height

    if img_ratio > target_ratio:
        # Image is wider - fit height, crop width
        new_height = target_height
        new_width = int(img_ratio * target_height)
    else:
        # Image is taller - fit width, crop height
        new_width = target_width
        new_height = int(target_width / img_ratio)

    img = img.resize((new_width, new_height), Image.Resampling.LANCZOS)

    # Crop center to exact 128x32
    left = (new_width - target_width) // 2
    top = (new_height - target_height) // 2
    img = img.crop((left, top, left + target_width, top + target_height))

    # Convert to 1-bit (black and white)
    img = img.convert('1')

    # Generate byte array (column-major, LSB at top)
    # OLED format: 128 columns, 4 pages (8 pixels per page = 32 rows)
    bytes_array = []

    for page in range(4):  # 4 pages of 8 rows each
        for col in range(128):
            byte = 0
            for bit in range(8):
                row = page * 8 + bit
                pixel = img.getpixel((col, row))
                if pixel:  # White pixel = bit set
                    byte |= (1 << bit)
            bytes_array.append(byte)

    # Generate C code
    print(f"// Generated from: {image_path}")
    print(f"// Size: {len(bytes_array)} bytes (128x32 pixels)")
    print(f"static const char PROGMEM {array_name}[] = {{")

    for i in range(0, len(bytes_array), 16):
        line = bytes_array[i:i+16]
        hex_str = ", ".join(f"0x{b:02X}" for b in line)
        print(f"    {hex_str},")

    print("};")
    print(f"\n// Usage: oled_write_raw_P({array_name}, sizeof({array_name}));")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 convert_oled_image.py <input_image> <array_name>")
        sys.exit(1)

    convert_image_to_oled_bytes(sys.argv[1], sys.argv[2])
