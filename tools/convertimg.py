import struct
import sys
import re
import os

if len(sys.argv) != 3:
    print("Usage: python convert_rgb565.py <input_file> <output_file>")
    sys.exit(1)

input_file = sys.argv[1]
output_file = sys.argv[2]

# Extract width and height from the input file name
match = re.search(r'_(\d+)x(\d+)\.png$', input_file)
if not match:
    print("Error: Input file name must be in the format <name>_<width>x<height>.png")
    sys.exit(1)

width = int(match.group(1))
height = int(match.group(2))

# Use ImageMagick to convert PNG to raw RGB format
rgb_temp_file = "temp.rgb"
convert_command = f"magick {input_file} -depth 8 -resize {width}x{height}! rgb:{rgb_temp_file}"
result = os.system(convert_command)
if result != 0:
    print("Error: ImageMagick convert command failed.")
    sys.exit(1)

# Read the raw RGB data from the temp file
try:
    with open(rgb_temp_file, "rb") as f:
        rgb_data = f.read()
except Exception as e:
    print(f"Error: Could not read the temporary RGB file. {e}")
    sys.exit(1)

# Convert the RGB888 data to RGB565
rgb565_data = bytearray()
for i in range(0, len(rgb_data) - 2, 3):
    r = rgb_data[i] >> 3
    g = rgb_data[i + 1] >> 2
    b = rgb_data[i + 2] >> 3

    # Pack RGB565 (5 bits red, 6 bits green, 5 bits blue)
    rgb565 = (r << 11) | (g << 5) | b
    rgb565_data.extend(struct.pack("<H", rgb565))

# Write the RGB565 data to the output file
with open(output_file, "wb") as f:
    f.write(rgb565_data)

# Clean up temporary file
os.remove(rgb_temp_file)

print(f"Converted image saved as {output_file}")
