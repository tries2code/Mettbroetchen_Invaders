# Mettbroetchen_Invaders
A Space Invaders Clone for practice

Linker Input debug:


fltkzlibd.lib
fltkpngd.lib
fltkd.lib
wsock32.lib
comctl32.lib
fltkimagesd.lib


Linker Input release:


fltkzlib.lib
fltkpng.lib
fltk.lib
wsock32.lib
comctl32.lib
fltkimages.lib

To Do:

-Increase frame-rate somehow so barriers can be added. They are commented out atm(see MB_Invaders Constructor).
Once done, the code for damaging barriers by lasers and hostiles will be added.
Edit: Barriers can now be added without causing problems, since the main window womt comtimously redraw itself. But therfor lasers got even worse.


-Fix Lasers so they dont look like moving caterpillars. Lasers got worse. I wish they could be moved as smooth as the spaceship, but that doesnt work, idk why...

-Fine tuning on ship movement and shooting
