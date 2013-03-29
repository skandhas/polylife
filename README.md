polylife
========

Conway's Game of Life on STL models

[http://life.h2so5.net/](http://life.h2so5.net/)

![image](http://life.h2so5.net/polylife.png)

## Build

### OSX 10.7 or later

1) Install [GLFW](http://www.glfw.org/). Add the library/header path as necessary.

2) Checkout Polylife and [glm](http://glm.g-truc.net/) as submodule.

```bash
$ git clone git://github.com/h2so5/polylife.git
$ cd polylife

# checkout glm
$ git submodule init
$ git submodule update
```
3) Then, open __xcode/Polylife.xcodeproj__ and build it.
