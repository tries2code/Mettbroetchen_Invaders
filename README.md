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


//Ab hier Linux-Version///////////////////////////////////////////////////////////////////////////////////////////////////////////
11.01.2023
DOCKER:


Hier eine funktionierende Dockerfile auf archlinux-basis, aber etwas groß(Imgage-Size 1.09GB)

    FROM archlinux:latest

    # Kopiert Daten des aktuellen Ordners in den angegebenen Image-Ordner
    COPY . /usr/src/myapp
    # Setzt den aktuellen Pfad
    WORKDIR /usr/src/myapp

    #Installation von Abhänigkeiten. Erster RUN-Befehl ist für die Schrift...
    RUN yes | pacman -Sy gnome-terminal
    RUN yes | pacman -Sy  gcc
    RUN yes | pacman -Sy  fltk

    # Code kompilieren
    RUN g++ -g  Backrounds.cpp Barriers.cpp Hostiles.cpp Spaceship.cpp SubWindows.cpp main.cpp -o main -lfltk -lfltk_images -lpthread
    # Programm ausführen
    CMD ["./main"]

    #?
    LABEL Name=mettbroetcheninvaderss Version=0.0.1


Hier eine funktionierende Dockerfile auf alpine-basis, wehsentlich kleiner(Imgage-Size 454MB). Allerdings sieht man hier den Laser nicht.
    
    FROM alpine:latest

    # Kopiert Daten des aktuellen Ordners in den angegebenen Image-Ordner
    COPY . /usr/src/myapp

    #Installation von Abhänigkeiten. Erster RUN-Befehl ist für die Schrift...
    RUN apk --update --upgrade --no-cache add fontconfig ttf-freefont font-noto terminus-font \ 
         && fc-cache -f \ 
         && fc-list | sort 
    RUN yes | apk add g++
    RUN yes | apk add fltk-dev

    # Setzt den aktuellen Pfad
    WORKDIR /usr/src/myapp

    # Code kompilieren
    RUN g++ -g  Backrounds.cpp Barriers.cpp Hostiles.cpp Spaceship.cpp SubWindows.cpp main.cpp -o main -lfltk -lfltk_images -lpthread
    # Programm ausführen
    CMD ["./main"]

    #?
    LABEL Name=mettbroetcheninvaderss Version=0.0.1


Container erstellen und öffnen(-p ist in diesem Fall nicht nötig):

    docker run -it \
        -e RAM=8 \
        -e cpu=max \
        -p 5000:5000 \
        -v /tmp/.X11-unix:/tmp/.X11-unix \
        -e "DISPLAY=${DISPLAY:-:0.0}" \
        --name mbi-app \
        --restart=on-failure:5 \
        mbi




15.01.2023
Multi-Stage-Build(Imgage-Size 845MB).: Mehrere Images werden in einer Dockerfile nacheiander, und aufeinander aufbauend,gebaut.
Sinn und Zweck ist, im finalen Image ausschließlich die Layer zu integrieren, welche auch dort rein gehören.
In diesem Fall wird gcc beim finallen Image weggelassen, da es nur in "builder" zum kompilieren benötigt wird.
Im Gegensatz dazu wird gnome-terminal nur für die Ausführung des Programms benötigt und wird dementsprechend nicht
in "builder" geladen.


####Multi-Stage-Build mit Arch#########################################################################
FROM archlinux:latest as builder

# Setzt den aktuellen Pfad
WORKDIR /usr/src/myapp
# Kopiert Daten des aktuellen Ordners in den angegebenen Image-Ordner
COPY . /usr/src/myapp

#Installation von Abhänigkeiten. 
RUN yes | pacman -Sy  gcc \
 && yes | pacman -Sy  fltk

# Code kompilieren
RUN g++ -g  Backrounds.cpp Barriers.cpp Hostiles.cpp Spaceship.cpp SubWindows.cpp main.cpp -o main -lfltk -lfltk_images -lpthread


####Production-Build (ohne Bezeichnung)#######################################################

FROM archlinux:latest

WORKDIR /usr/src/myapp
#Erster RUN-Befehl ist für die Schrift...
RUN yes | pacman -Sy gnome-terminal \
 && yes | pacman -Sy  fltk

# Kopiert binary und Bilder-Ordner aus "builder" in den angegebenen Image-Ordner
COPY --from=builder /usr/src/myapp/main /usr/src/myapp/main 
COPY --from=builder /usr/src/myapp/MBs /usr/src/myapp/MBs 
COPY --from=builder /usr/src/myapp/Highscores.txt /usr/src/myapp/Highscores.txt

#Binary ausführen
CMD ["./main"]  

#?
LABEL Name=mettbroetcheninvaderss Version=0.0.1







16.01.2023
Multistage Build mit Alpine:

 ####Multi-Stage-Build mit Alpine#########################################################################

FROM alpine:latest as builder

# Setzt den aktuellen Pfad
WORKDIR /usr/src/myapp
# Kopiert Daten des aktuellen Ordners in den angegebenen Image-Ordner
COPY . /usr/src/myapp

#Installation von Abhänigkeiten. Erster RUN-Befehl ist für die Schrift...
RUN yes | apk add g++ && \
    yes | apk add fltk-dev

# Code kompilieren
RUN g++ -g  Backrounds.cpp Barriers.cpp Hostiles.cpp Spaceship.cpp SubWindows.cpp main.cpp -o main -lfltk -lfltk_images -lpthread
  

####Production-Build (ohne Bezeichnung)#######################################################
FROM alpine:latest

# Setzt den aktuellen Pfad
WORKDIR /usr/src/myapp
# Kopiert binary, Bilder-Ordner, und Highscores.txt aus "builder" in den angegebenen Image-Ordner
COPY --from=builder /usr/src/myapp/main /usr/src/myapp/main 
COPY --from=builder /usr/src/myapp/MBs /usr/src/myapp/MBs 
COPY --from=builder /usr/src/myapp/Highscores.txt /usr/src/myapp/Highscores.txt

#Installation von Abhänigkeiten. Erster RUN-Befehl ist für die Schrift...
RUN apk --update --upgrade --no-cache add fontconfig ttf-freefont font-noto terminus-font \ 
 && fc-cache -f \ 
 && fc-list | sort \
 && yes | apk add fltk-dev


#Programm ausführen
CMD ["./main"]
#?
LABEL Name=mettbroetcheninvaderss Version=0.0.1