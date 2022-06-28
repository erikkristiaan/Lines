# Lines 🎨

Lines is a generative art program which reproduces images by drawing random 2D lines to a blank canvas based on an input source image. Lines then compares each iteration, only keeping the lines which have a lower [Root-mean-square deviation](https://en.wikipedia.org/wiki/Root-mean-square_deviation).

<p align="center">
  <img src='https://user-images.githubusercontent.com/8892722/173779269-796cb672-44b0-4cb2-8332-070e9f598ac7.png' width=700>
</p>

## Installation

### Dependencies
- OpenCV
- Cmake
- GCC or Clang

### Compiling Lines

Compile Lines on linux with:

```
git clone https://github.com/erikkristiaan/Lines.git
cd Lines
mkdir build
cd build
cmake ../
cmake --build .
```

### Running Lines

You can then run Lines from the command-line using command:
```
./Lines [arguments]
```

## Flags

#### `--primitives, -p`
- Line size in pixels. For instance, `-p 50` will render 50px lines to the canvas. (Default: 30)

#### `--iterations, -i`
- Number of iterations to complete per frame. (Default: 20000000)

####  `--frames, -x`
- Number of times to run the program. Useful for making short animated gifs ffmpeg. (Default: 1)

#### `--antialiasing, -a`
- `true` - Lines are generated with anti-aliasing. Usually produces more pleasing images. (Default)
- `false`- Lines are generated without anti-aliasing.

#### `--palette, -c`
-  `1` - Generates a random value from 0 - 255 for each RGB channel.
-  `2` - Samples random values from all pixels on the canvas of the input image. Colors tend toward the mean.
-  `3` - Samples random values from the unique colors of the input image.  Sometimes produces images that are more color accurate. (Default)

####  `--filename, -f`
- Location of the input file. Use with  `-f ~/location/to/file.jpg`. (Default: ../examples/default.jpg)

## Inspiration for Lines & How it works

Lines is a program I wrote a while back to tackle the following programming challenge. I finally got around to converting the program from python to C++ for performance reasons while also adding some new features.

```
- Load an image (source image).
- Generate a list of all the colors from the source image.
- Create 2 blank images (image1 and image2).
- Draw a random primitive on image1 using a random color from the source image.
- Compare image1 to the source image.
- If image1 is closer to the source image than image2, copy image1 to image2. If not, copy image2 to image1 and continue iterating.
```

Lines however utilizes some tricks to vastly speed up performance while more or less creating the same results. For instance, Lines only does comparisons on CV matricies with RGB values and will only check RGB values along the pixels that have changed.

`./Lines -c 3 -a true -p 50 -i 10000000`
`./Lines -c 3 -a true -p 50 -i 10000000`

## Example Gallery

<!---`./Lines -c 3 -a true -p 50 -i 10000000` -->
<p align="center">
  <img src='https://user-images.githubusercontent.com/8892722/173780297-26b9b3c3-e4ff-44ef-ac96-aab3568c2f40.jpg'>
</p>

<!---`./Lines -p 50` -->
<p align="center">
  <img src='https://user-images.githubusercontent.com/8892722/176154522-9d3f02be-3875-4fce-84d0-5ba480b4e43d.jpg'>
</p>
