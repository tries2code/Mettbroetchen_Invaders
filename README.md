# Mettbroetchen_Invaders

This is a basic Space Invaders Clone, using FLTK.



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


-Fine tuning on ship movement and shooting


-Fine tuning barrier damage




Postscript:

This is my third game using the FLTK library, and the very first without using the Stroustrup enviorment 
from his Book programming Principles and Practice using C++. This project is meant for practicing coding and
learning about how to use FLTK beyond the functionality of Dr Stroustrup's FLTK-Enviorment.
The FLTK functions within this code might have been used wrong since i'm far from fully understanding how
everything works.For now the code works (mostly) as intended and therefor i'll give it a rest, for now.
I might revistit it in the future for improvements once i have a better understanding about how things 
like handle() or damage() work. I had a hard time working with the latter, so i took it out again and went with
a rather primitve way (regarding the Barriers).
Next to the FLTK stuff, my code logic itself is provbably flawed as well. Some parts could probably shorter
and/or smarter, and also with less technical debt. Luckyly, this game is too basic to care for the latter.
