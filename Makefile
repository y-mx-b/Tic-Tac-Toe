CC = clang
CFLAGS = -Wall -O2

CFILES = src/*.c
CLIBDY = `pkg-config --libs --cflags raylib`
CLIBSTAT = ./lib/libraylib.a
BIN = ./bin/Tic-Tac-Toe

# macOS specific
MACOS_FRAMEWORKS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
APP_NAME = Tic-Tac-Toe


all: Tic-Tac-Toe.app

Tic-Tac-Toe-macOS:
				[ ! -d "./bin/" ] && mkdir bin
				$(CC) $(MACOS_FRAMEWORKS) $(CLIBSTAT) $(CFILES) -o $(BIN)-macOS

Tic-Tac-Toe.app: Tic-Tac-Toe-macOS
				mint run createapp -m json

clean:
				rm -r ./bin Tic-Tac-Toe.app
				/System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/LaunchServices.framework/Versions/A/Support/lsregister -f Tic-Tac-Toe.app
