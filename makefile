#
# Makefile para auxiliar a compilacao do jogo da inundacao
# Compilador: gcc
# Data......: 07/09/2016
# SO........: Arch Linux 4.7.2-1
# para executar esse arquivo basta apenas digitar 'make' no terminal
#

COMPILER=gcc
SOURCES=main.c window.c renderer.c core.c
EXECUTABLE=flood
LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf
build:
	$(COMPILER) $(SOURCES) -o $(EXECUTABLE) $(LIBS)