#/bin/sh

## As you can tell, I'm being lazy. I have Sid on my laptop so felt like doing this.

sudo apt install pacapt
## sudo ln -s /usr/bin/pacapt /usr/pin/pacapt	## Awful fail, yeah im up late.
sudo ln -s /usr/bin/pacapt /usr/bin/pacman
./DEPS.sh
