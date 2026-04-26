# compile
sudo gcc -o /usr/bin/key_listener src/main.c

# set environment
mkdir -p /home/$USER/.config/key_listener
touch /home/$USER/.config/key_listener/shortcuts.txt

# set daemon
sudo cp install/*.service /etc/systemd/system/
sudo systemctl enable --now key-listener.service

