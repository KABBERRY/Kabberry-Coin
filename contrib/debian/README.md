
Debian
====================
This directory contains files used to package kabberryd/kabberry-qt
for Debian-based Linux systems. If you compile kabberryd/kabberry-qt yourself, there are some useful files here.

## kabberry: URI support ##


kabberry-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install kabberry-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your kabberry-qt binary to `/usr/bin`
and the `../../share/pixmaps/kabberry128.png` to `/usr/share/pixmaps`

kabberry-qt.protocol (KDE)

