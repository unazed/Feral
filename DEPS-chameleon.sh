#/bin/sh

#I've never installed this OS before. Do forgive me if this script doesn't work.

sudo zypper install pacapt
sudo ln -s /usr/bin/pacapt /usr/bin/pacman
./DEPS.sh
