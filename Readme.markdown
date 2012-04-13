caps osd
========

Idea
--------

I'm a VIM user, and there's one thing that is very annoying: 
accidentally pressing CapsLock which quite changes VIM's 
behaviour.
So I wanted an OSD that shows me, when CapsLock was pressed.
This is the result: a little program using the 
[xosd library](http://libxosd.sourceforge.net/) that just
shows the message "Capslock is ON" in bold green letters.

I also use the 
[awesome window manager](http://awesome.naquadah.org/), which
is where I bound the CapsLock key to execute this program
(see below).

Requirements
--------

The xosd library

Usage
--------

Just start the program. Nothing will happen at first, but
with the SIGUSR1 signal the OSD can be toggled.

awesome wm keybinding
--------

I put this in my rc.lua2:

    caps_pid = awful.util.spawn("/home/sh/bin/caps-osd")
	
and in the key binding section

    awful.key({}, "Caps_Lock",
    NULL,
    function() 
        awful.util.spawn("kill -USR1 " .. caps_pid)
    end),
	

License
--------
GPL
