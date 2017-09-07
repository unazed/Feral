#/bin/sh

# i'm supposed to fanboy for centos and fedora

# If you don't have DNF installed. Install it. For the love of The Almighty Penguin Up Above.
# I have Fedora on my laptop, but don't recall if pacapt is actually in the repositories or not.
# Oh well, what are you doing building an OS where I insist on Arch... on something other than Arch?
sudo dnf -y install pacapt
sudo ln -s /usr/bin/pacapt /usr/bin/pacman
./DEPS.sh
