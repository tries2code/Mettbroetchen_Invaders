 ####Multi-Stage-Build mit Alpine#########################################################################

FROM alpine:latest as builder

# Setzt den aktuellen Pfad
WORKDIR /usr/src/myapp
# Kopiert Daten des aktuellen Ordners in den angegebenen Image-Ordner
COPY . /usr/src/myapp

#Installation von Abhänigkeiten. Erster RUN-Befehl ist für die Schrift...
RUN yes | apk add g++ \
 && yes | apk add fltk-dev

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