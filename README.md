# SDL Fractals
Fractal Image Generators in SDL

To use:

```cmd
./Fractals.exe /PARAMS={parameters.json} /IMAGE={image.png}
```

# Examples

## Mandelbrot Set
![Mandelbrot Set](/samples/mandelbrot.png)

### Parameters
|Parameter      | Value |
|---------------|:-----:|
|Generator      | **z**^**exp** + **C** |
|exp            | 2.0 |
|treshold       | 255 |
|orbit          | 2.0 |
|parameter files| [mandelbrot.json](src/parameters/mandelbrot.json), [mandelbrot2](src/parameters/mandelbrot2.json), [mandelbrot3](src/parameters/mandelbrot3.json) |
