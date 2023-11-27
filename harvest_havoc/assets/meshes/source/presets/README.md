# Blender Export Preset Installation Guide

This directory contains the custom export preset for Blender, specifically designed for use with the HarvestHavoc project. Follow the instructions below to install the preset in your Blender setup.

## Installation Steps

1. **Locate the Preset File**:
   - Inside this directory, you will find a folder structure starting with `Blender Foundation`. This contains the `Velecs_Export_Preset.py` file, which is the Blender export preset.

2. **Identify Your Blender Configuration Directory**:
   - Blender presets are stored in the Blender configuration directory on your system. The path to this directory typically includes your user's `AppData` folder on Windows.
   - The path usually looks like this: `%APPDATA%\Blender Foundation\Blender\[BlenderVersion]\scripts\presets\`
   - Here, `[BlenderVersion]` should be replaced with the version of Blender you are using (e.g., `3.6`).

3. **Copy the Preset**:
   - Copy the entire `Blender Foundation` directory from this location.
   - Paste it into your `AppData` folder, typically accessed by typing `%APPDATA%` in the file explorer's address bar on Windows.
   - If prompted, merge the folders with existing ones in `AppData`.

4. **Verify Installation**:
   - Open Blender, and go to the export options where you usually find OBJ export settings.
   - Your new preset, `Velecs_Export_Preset`, should now be available as an option.

## Notes

- The preset is tailored for the Velecs Engine's specific requirements, ensuring consistent export settings for all meshes.
- If you update Blender to a new major version, you may need to re-install the preset for that version.
- For any issues or if you have custom requirements, refer to the project's documentation or contact the project maintainers.
