CC = clang
CFLAGS = -Wall -O2
MACOS_FRAMEWORKS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
APP_NAME = Tic-Tac-Toe

macos:
	$(CC) $(MACOS_FRAMEWORKS) lib/libraylib.a src/main.c -o Tic-Tac-Toe
	./TIc-Tac-Toe
