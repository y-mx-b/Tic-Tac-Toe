# Tic-Tac-Toe

A simple tic-tac-toe game made with [raylib](http://www.raylib.com/).

## Build

Build with `make`.

```make
make macos-app  # create .app bundle (using createapp)
make macos-bin  # create binary-only
make clean      # delete binaries/apps
```

Note: target `macos-app` requires [`createapp`](https://github.com/y-mx-b/createapp).

## TODO

### Bugs

- [ ] Fix visual bugs in app bundle (textures not rendered)

### Niceties

- [ ] Start menu
- [ ] Custom drawn O/X's
- [ ] New game menu
- [ ] Sound effects + music
