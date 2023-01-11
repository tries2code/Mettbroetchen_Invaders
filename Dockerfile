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