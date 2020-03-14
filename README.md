

# Background

Wiray is a very simple renderer based on [nori](https://wjakob.github.io/nori/),  used to learning PBRT.

# Compile

Wiray compiles and runs successfully on Windows, and has not been tested on other platforms. You can generate vs2019 sln through cmake-gui, or cmake command line. You also can play with the executable in release file.

# Feature



|                          Function                           | state   |
| :---------------------------------------------------------: | ------- |
|                       direct lighting                       | done    |
|                        Path tracing                         | done    |
|                  multi important  sampling                  | done    |
|                       photon mapping                        | done    |
|                     homogeneous medium                      | done    |
|                     volume path tracing                     | done    |
|                         Disney brdf                         | done    |
|                            bdpt                             | doing   |
|                             mlt                             | doing   |
|                    subsurface scattering                    | doing   |
| ppm/sppm/mmlt/vcm...(advance light transporting algorithms) | planing |

Also lots of important but trivial feature light GUI and multi-threading is done by nori.


# image produced by WiRay

**Path tracing with Disney brdf:**

![](Scenes/box.png)

**naive Photon mapping with simple caustic:**

![](Scenes/pm.png)


**homogeneous Volume rendering:**

![](Scenes/vol.png)