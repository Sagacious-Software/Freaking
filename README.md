# Freaking

Simple 2D graphics drawing library!

## Build

Build the library and the demos by running this in the root of the repository:

```bash
meson builddir --buildtype release
cd builddir
meson compile
```

(Optionally do `--buildtype debug` instead if you would like to keep debugging information and turn optimizations off, e.g., if you want to do development.)

## Try the demos

Try the demos by running this in the build directory:

```bash
meson test
```

## Install

And when you are ready to install do this in the build directory:

```bash
meson install
```

## TODO

### General

- fonts, at least bitmaps for now
- rect and vector path fill and stroke
- make transforms used

### Implementation

- software rendering implementation
- opengl implementation
