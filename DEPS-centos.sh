#/bin/sh

# i think i'm supposed to fanboy for centos and fedora

# If you don't have DNF installed. Install it. For the love of The Almighty Penguin Up Above.
# I have Fedora on my laptop, but don't recall if pacapt is actually in the repositories or not.
# Oh well, what are you doing building an OS where I insist on Arch... on something other than Arch?
sudo dnf -y install pacapt
sudo ln -s /usr/bin/pacapt /usr/bin/pacman
./DEPS.sh

# I'm also too lazy to bother with Bourne shell-ing properly with switches and arguments and all that. Fix it yourself if you're on YUM.
