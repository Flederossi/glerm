# glerm
> An ascii globe projection
---
`glerm` renders a rotating globe inside your terminal. It uses a simple form of diffuse lighting based on the [phong-reflection-model](https://en.wikipedia.org/wiki/Phong_reflection_model) as well as [UV-mapping](https://en.wikipedia.org/wiki/UV_mapping) to use the worldmap as texture.

<br>

![Alt Text](https://github.com/Flederossi/glerm/blob/main/assets/vid.gif)

## Compile & Run
> Compile only
```sh
make
```
> Compile and run
```sh
make run
```

## Configure
Some parameters of the globe can be configured directly in [main.c](https://github.com/Flederossi/glerm/blob/main/src/main.c).
