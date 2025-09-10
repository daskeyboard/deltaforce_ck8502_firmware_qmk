# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This repository contains the QMK firmware for the **Das Keyboard DeltaForce 65**, a 65% mechanical keyboard with RGB lighting, rotary encoder, and VIA/Vial support. The keyboard uses the WB32FQ95 processor and features:

- 65% layout (67 keys with rotary encoder)
- Per-key RGB lighting with IS31FL3733 drivers
- VIA/Vial compatibility for real-time keymap editing
- **SignalRGB support** for advanced RGB ecosystem integration
- Hot-swappable switches
- USB-C connectivity

## Repository Structure

```
CK8502_via_v1_07_20250411/
├── ck8502/                          # Current firmware version
│   ├── keymaps/
│   │   ├── default/                 # Standard ANSI keymap
│   │   ├── via/                    # VIA-compatible keymap
│   │   └── vial/                   # Vial-compatible keymap (open-source VIA)
│   ├── info.json                   # Keyboard configuration and layout
│   ├── keyboard.json               # VIA lighting configuration
│   ├── config.h                    # Hardware-specific settings
│   ├── rules.mk                    # Build configuration
│   └── ck8502.c                    # Keyboard-specific code
├── Daskeyboard_ck8502_65_via.js    # SignalRGB plugin file
└── daskeyboard_ck8502_via.bin      # Pre-compiled firmware binary

archive/v1_06/                      # Previous firmware version
```

## Development Workflow

### Building Firmware

This is a **QMK firmware** project. To build:

```bash
# Standard build command (replace keymap as needed)
make ck8502:default
make ck8502:via
make ck8502:vial

# Build with flash-ready output
make ck8502:via:flash
```

### File Naming Convention
- Compiled firmware outputs: `川东CK8502_via_v1_XX_YYYYMMDD.hex` and `.bin`
- Version format: `v1_XX` where XX is incremental version number
- Date format: `YYYYMMDD` (year/month/day)

### Testing
- Use QMK Toolbox for flashing firmware to keyboard
- Test with VIA application for real-time keymap changes (load `keyboard.json` for lighting controls)
- Test with SignalRGB application using `Daskeyboard_ck8502_65_via.js` plugin
- **Reset sequence**: Hold ESC key (K01 position) while plugging in USB cable

## Key Configuration Details

### Hardware Configuration
- **Processor**: WB32FQ95 with wb32-dfu bootloader
- **Matrix**: 5 rows × 16 columns (ROW2COL diode direction)
- **RGB**: 67 LEDs using dual IS31FL3733 drivers
- **Encoder**: Single rotary encoder on pins B14/B13
- **Storage**: SPI flash with wear leveling for settings persistence

### Keymap Architecture
- **Layer 0/WIN_BASE**: Windows base layout
- **Layer 1/WIN_FN**: Windows function layer (accessed via MO(2) key)
- **Layer 2/MAC_BASE**: macOS base layout with media keys
- **Layer 3/MAC_FN**: macOS function layer

### RGB Matrix Features
- 14 animation modes including All Off, Solid Color, Alphas Mods, Gradient, Breathing, Band effects, Cycle effects, Typing Heatmap, and Reactive modes
- Brightness: 160 max, 40 value steps
- Framebuffer effects for typing animations
- Sleep mode support (turns off when suspended)
- **SignalRGB integration**: Advanced ecosystem RGB control with protocol v1.0.6

## Important Implementation Notes

### VIA/Vial Differences
- **VIA keymap**: Uses `VIA_ENABLE = yes` for official VIA app compatibility
- **Vial keymap**: Uses both `VIA_ENABLE = yes` and `VIAL_ENABLE = yes` for open-source Vial app
- **Vial features**: Includes `vial.json` for layout definition and enhanced configuration options

### Custom Key Handling
- **Backspace behavior**: Shift+Backspace sends Delete
- **GUI toggle**: Long-press GU_TOGG (1.5s) toggles Windows key lock
- **EEPROM reset**: Long-press EE_CLR (1.5s) triggers factory reset with LED feedback
- **RGB toggle**: Custom behavior - cycles between all LEDs on/off states

### Memory Management
- Uses wear leveling with 8KB backing size for EEPROM longevity
- SPI flash storage on pins B3-B5, B4, CS on C12
- Force NKRO enabled by default

### SignalRGB Integration
- **Plugin file**: `Daskeyboard_ck8502_65_via.js` defines device communication protocol
- **Protocol version**: 1.0.6 with firmware compatibility checking
- **Features**: Canvas mode for effects, Forced color mode, hardware/SignalRGB shutdown modes
- **LED mapping**: 67 LEDs mapped to keyboard positions for precise lighting control
- **Communication**: USB HID interface with command-response protocol (commands 0x21-0x28)
- **Build option**: `SIGNALRGB_SUPPORT_ENABLE = yes` in rules.mk

## Development Best Practices

### When Modifying Keymaps
1. **Test both layouts**: Windows and macOS layers have different key assignments
2. **Encoder behavior**: Different functions per layer (volume vs RGB saturation)
3. **RGB indicators**: Caps Lock (LED 29) and GUI Lock (LED 58) show status

### When Adding Features
1. **Check EEPROM usage**: Settings are stored in wear-leveled flash
2. **RGB performance**: Max brightness is intentionally limited to 160/255
3. **Timing-critical code**: Be aware of 1.5-second long-press detection in housekeeping task

### File Organization
- Keep keymap-specific code in respective keymap directories
- Hardware configuration changes go in `config.h`
- Build options belong in `rules.mk` files
- Layout definitions and RGB matrix mappings are in `info.json`
- VIA lighting configurations are defined in `keyboard.json`
- SignalRGB plugin logic is in `Daskeyboard_ck8502_65_via.js`

## Troubleshooting

### Common Issues
- **Firmware won't flash**: Check bootloader mode (hold ESC during USB insertion)
- **RGB not working**: Verify I2C addresses (0x74, 0x77) and pin assignments
- **VIA not detecting**: Ensure VIA-specific JSON file is loaded in VIA application
- **VIA lighting not available**: Load `keyboard.json` in VIA for RGB controls
- **SignalRGB not detecting**: Verify `SIGNALRGB_SUPPORT_ENABLE = yes` in build and use correct plugin
- **Key matrix issues**: Check row/column pin definitions in `info.json`

### Build Errors
- **Missing dependencies**: Follow QMK setup guide for toolchain installation
- **Compilation failures**: Check for syntax errors in keymap.c files
- **Flash memory issues**: Verify SPI flash configuration in config.h
- **SignalRGB build errors**: Ensure SignalRGB support is properly enabled in rules.mk