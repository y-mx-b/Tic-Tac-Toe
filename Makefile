CC = clang
CFLAGS = -Wall -O2
MACOS_FRAMEWORKS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
APP_NAME = Tic-Tac-Toe

macos-bin:
				[ ! -d "./bin/" ] && mkdir bin
				$(CC) $(MACOS_FRAMEWORKS) lib/libraylib.a src/main.c -o ./bin/Tic-Tac-Toe

macos-app: macos-bin
				mint run createapp -m json

clean:
				rm -r ./bin Tic-Tac-Toe.app
