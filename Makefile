CC = clang
CFLAGS = -Wall -O2

CFILES = src/*.c
CLIBDY = `pkg-config --libs --cflags raylib`
CLIBSTAT = ./lib/libraylib.a
BIN = ./bin/Tic-Tac-Toe

TEST =

# macOS specific
MACOS_FRAMEWORKS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
APP_NAME = Tic-Tac-Toe


all: Tic-Tac-Toe.app

bin:
				[ ! -d "./bin/" ] && mkdir bin

Tic-Tac-Toe_macOS: bin
				$(CC) $(MACOS_FRAMEWORKS) $(CLIBSTAT) $(CFILES) -o $(BIN)_macOS

Tic-Tac-Toe.app: bin
				$(CC) $(MACOS_FRAMEWORKS) $(CLIBSTAT) $(CFILES) -o $(BIN)_macOS -DMACOS_APP=TRUE
				mint run createapp -m json


# Platforms
# macOS
macos-app: Tic-Tac-Toe.app
macos-bin: Tic-Tac-Toe_macOS
macos-test: bin
				$(CC) $(MACOS_FRAMEWORKS) $(CLIBSTAT) src/draw.c test/test-$(TEST).c -o $(BIN)_test_macOS

clean:
				rm -r ./bin Tic-Tac-Toe.app
				/System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/LaunchServices.framework/Versions/A/Support/lsregister -f Tic-Tac-Toe.app
