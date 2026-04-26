# Key Listener

A lightweight, system-level daemon written in C that listens to keyboard events directly from `/dev/input` and triggers custom shell scripts or commands based on mapped key codes. This is particularly useful for enabling custom keyboard shortcuts on Linux systems, running quietly as a background service.

## Features

- Non-intrusive background execution via `systemd`.
- Trigger scripts or commands from raw Linux event streams (e.g., `/dev/input/event4`).
- Simple configuration file for mapping key codes to respective scripts.
- Includes a utility to check your keyboard's key codes.

## Project Structure

- `src/`: Contains the C source code for the key listener and utility tools.
- `config/`: Contains the configuration file `shortcuts.txt` for mapping key presses to scripts.
- `install/`: Contains systemd service definitions and an installation script.

## Configuration

Keyboard shortcuts are mapped in the `~/.config/key_listener/shortcuts.txt` file. 

The format for each shortcut is:
```text
<keycode>:<absolute_path_to_script>
```

**Example:**
```text
99:/home/lazaro/.scripts/printscreen.sh
110:/home/lazaro/.scripts/lockscreen.sh
```

**Note:** The daemon parses the configuration file path relative to a specific user's system directory (e.g., `~/.config/key_listener/shortcuts.txt`). Because the daemon is run as `root` via `systemd`, environment variables like `$USER` will resolve to `root`. Therefore, **you must manually configure the `USER` variable inside `src/main.c`** with your actual username (e.g. `char* USER = "lazaro";`) before compiling to ensure it successfully resolves to your home directory.

Additionally, the input event file is hardcoded to `/dev/input/event4` in `src/key_listener.c`. You may need to change this depending on your active keyboard input device.

## Finding Key Codes

If you don't know the key code for the key you want to map, you can use the included `check_keys.c` utility. 

You can manually compile and run it to observe key codes directly from your `/dev/input` stream:
```bash
gcc -o check_keys src/check_keys.c
sudo ./check_keys
```
*Note: Make sure to verify that the target event stream in `check_keys.c` matches your system's keyboard stream before running.*

## Installation

An installation script is provided which will automatically compile the main program and set it up as a `systemd` service to run upon startup.

To install:
1. Make sure you have `gcc` installed.
2. Ensure `install.sh` has execute permissions.
3. Run the installation script:

```bash
cd /home/lazaro/key_listener
sh install/install.sh
```

This will:
1. Compile the key listener and place the binary at `/usr/bin/key_listener`.
2. Copy the `key-listener.service` file to `/etc/systemd/system/`.
3. Enable and start the systemd service.

## Managing the Service

Once installed, the process runs as a root systemd service. You can manage it using standard `systemctl` commands:

- **Check status:** `sudo systemctl status key-listener.service`
- **Stop the service:** `sudo systemctl stop key-listener.service`
- **Restart the service:** `sudo systemctl restart key-listener.service` (Useful after updating `shortcuts.txt` or recompiling).
