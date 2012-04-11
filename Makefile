all:
	gcc `xosd-config --cflags --libs` caps-osd.c -o caps-osd
