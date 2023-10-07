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

### Benchmarks

**mandelbrot**
```cmd
Time (mean ± σ):      8.775 s ±  0.057 s    [User: 8.537 s, System: 0.123 s]
Range (min … max):    8.680 s …  8.880 s    10 runs
```

**mandelbrot2**
```cmd
Time (mean ± σ):     651.1 ms ±   8.4 ms    [User: 604.5 ms, System: 36.2 ms]
Range (min … max):   639.8 ms … 662.9 ms    10 runs
```

**mandelbrot3**
```cmd
Time (mean ± σ):     681.8 ms ±  35.2 ms    [User: 619.5 ms, System: 38.9 ms]
Range (min … max):   647.1 ms … 744.7 ms    10 runs
```