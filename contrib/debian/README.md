
Debian
====================
This directory contains files used to package primestoned/primestone-qt
for Debian-based Linux systems. If you compile primestoned/primestone-qt yourself, there are some useful files here.

## primestone: URI support ##


primestone-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install primestone-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your primestoneqt binary to `/usr/bin`
and the `../../share/pixmaps/primestone128.png` to `/usr/share/pixmaps`

primestone-qt.protocol (KDE)

