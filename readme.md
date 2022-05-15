# Polygons

Polygons is a generative art program which prints random 2D primitives to a blank canvas based on an input source image.

## Installation 🤔

### Dependencies
- OpenCV
- Cmake
- GCC or Clang

### Compilation

Compile Polygons on linux with:

```
cd Polygons
mkdir build
cd build
cmake ../
cmake --build .
```

### Running Polygons

You can then run Polygons from the command-line using command:
```
./Polygons [arguments]
```


## Flags 🚩

#### `--primitives, -p`
- Bounding box size in pixels. For instance, `-p 50` will render 50px lines to the canvas. (Default: 30)

#### `--iterations, -i`
- Number of iterations to complete per frame. (Default: 20000000)

####  `--frames, -x`
- Number of times to run the program. Useful for making short animated gifs. (Default: 1)

#### `--antialiasing, -a`
- `true` - Lines are generated with anti-aliasing. Usually produces more pleasing images. (Default)
- `false`- Lines are generated without anti-aliasing.

#### `--palette, -c`
-  `1` - Generates a random value from 0 - 255 for each RGB channel.
-  `2` - Samples random values from all pixels on the canvas of the input image. Colors tend toward the mean.
-  `3` - Samples random values from the unique colors of the input image.  Sometimes produces images that are more color accurate. (Default)
####  `--filename, -f`
- Location of the input file. Use with  `-f ~/location/to/file.jpg`. (Default: ../examples/default.jpg)

## Inspiration for Polygons 🙂

Polygons is a program I wrote a while back to tackle the following programming challenge. I finally got around to converting the program from python to C++ for performance reasons while also adding some new features.

```
- Load an image (source image)
- Generate a list of all the colors in the source image
- Create 2 blank images (image1 and image2)
- draw a random polygon or circle on image1 using a random color from source image
- compare image1 to the source image
- if it's closer in color to the source image than image2, copy image1 to image2; if not, copy image2 to image1 and continue drawing more random shapes and comparing
```

## Example Gallery 🖼️

`./Polygons -c 3 -f ../examples/example3.jpg -a true -p 40 -i 10000000 -x 10`

![asdf](https://thumbs.gfycat.com/RingedCommonApisdorsatalaboriosa-mobile.mp4)