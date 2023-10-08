# SDL Fractals
Fractal Image Generators in SDL

To use:

```cmd
./Fractals.exe /PARAMS={parameters.json} /IMAGE={image.png} /PALETTE={palette.json}

/IMAGE and /PALETTE are optional
```

# Examples

## Mandelbrot Set
![Mandelbrot Set](/samples/mandelbrot.png)

### Parameters
|Parameter      | Value |
|---------------|:-----:|
|Generator      | **z**^**exp** + **C** |
|exp            | 2   |
|threshold      | 255 |
|orbit          | 2.0 |
|parameter files| [mandelbrot](src/parameters/mandelbrot.json), [mandelbrot2](src/parameters/mandelbrot2.json), [mandelbrot3](src/parameters/mandelbrot3.json) |

### Benchmarks

**mandelbrot**
```cmd
Time (mean ± σ):     740.5 ms ±   6.3 ms    [User: 694.0 ms, System: 35.1 ms]
Range (min … max):   729.2 ms … 751.2 ms    10 runs
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

## Newton
![Newton](/samples/newton1.png)

### Parameters
|Parameter      | Value |
|---------------|:-----:|
|Generator      | **z** - (**z**^3 - 1)/(3**z**^2) |
|tolerance      | 1e-6 |
|threshold      | 255 |
|parameter files| [newton1](src/parameters/newton1.json) |

```cmd
Time (mean ± σ):     868.1 ms ±   8.0 ms    [User: 822.9 ms, System: 35.2 ms]
Range (min … max):   855.1 ms … 882.9 ms    10 runs
```

## Julia Sets

### Common Parameters
|Parameter      | Value |
|---------------|:-----:|
|Generator      | **z**^**exp** + **C** |
|threshold      | 255 |
|orbit          | 2.0 |

### Specific Parameters and Benchmarks

![Julia 1](/samples/julia1.png)
|Parameter | Value       |
|----------|:-----------:|
|C         | -0.4 + 0.6i |
|parameter file| [julia1](src/parameters/julia1.json) |

```cmd
Time (mean ± σ):     821.6 ms ±   8.3 ms    [User: 770.7 ms, System: 38.7 ms]
Range (min … max):   812.3 ms … 836.7 ms    10 runs
```

![Julia 2](/samples/julia2.png)
|Parameter | Value         |
|----------|:-------------:|
|C         | -0.8 + 0.156i |
|parameter file| [julia2](src/parameters/julia2.json) |

```cmd
Time (mean ± σ):     936.7 ms ±  10.5 ms    [User: 881.0 ms, System: 39.5 ms]
Range (min … max):   925.1 ms … 959.9 ms    10 runs
```

![Julia 3](/samples/julia3.png)
|Parameter | Value         |
|----------|:-------------:|
|C         | 0.285 + 0.01i |
|parameter file| [julia3](src/parameters/julia3.json) |

```cmd
Time (mean ± σ):     732.1 ms ±  12.2 ms    [User: 678.0 ms, System: 38.8 ms]
Range (min … max):   718.5 ms … 755.8 ms    10 run
```

![Julia 4](/samples/julia4.png)
|Parameter | Value         |
|----------|:-------------:|
|C         | -0.7269 + 0.1889i |
|parameter file| [julia4](src/parameters/julia4.json) |

```cmd
Time (mean ± σ):      1.224 s ±  0.019 s    [User: 1.166 s, System: 0.041 s]
Range (min … max):    1.201 s …  1.263 s    10 runs
```

## Mandelbrot4
![Mandelbrot 4](/samples/mandelbrot4.png)

### Parameters
|Parameter      | Value |
|---------------|:-----:|
|Generator      | **z**^**exp** + **C** |
|exp            | 4   |
|threshold      | 255 |
|orbit          | 2.0 |
|parameter files| [mandelbrot4](src/parameters/mandelbrot4.json) |

```cmd
Time (mean ± σ):      3.937 s ±  0.055 s    [User: 3.831 s, System: 0.056 s]
Range (min … max):    3.898 s …  4.063 s    10 runs
```

## Burning Ship
![Burning Ship](/samples/burningship.png)

### Parameters
|Parameter      | Value |
|---------------|:-----:|
|Generator      | (Re(**Zn**) + iIm(**Zn**))^2 + **C** |
|inverted x     | true |
|inverted y     | true |
|inside color   | 0    |
|threshold      | 100  |
|orbit          | 4.0 |
|parameter files| [burningship](src/parameters/burningship.json) |

```cmd
Time (mean ± σ):     559.9 ms ±   4.1 ms    [User: 518.1 ms, System: 33.7 ms]
Range (min … max):   552.8 ms … 567.2 ms    10 runs
```

## Tricorn
![Tricorn](/samples/tricorn.png)

### Parameters
|Parameter      | Value |
|---------------|:-----:|
|Generator      | (**z_x**^2 + **z_y**^2) - i(2 * **z_x** * **z_y**) + **C** |
|inside color   | 0    |
|threshold      | 255  |
|orbit          | 4.0  |
|parameter files| [tricorn](src/parameters/tricorn.json) |

```cmd
Time (mean ± σ):     575.8 ms ±  21.6 ms    [User: 528.1 ms, System: 36.5 ms]
Range (min … max):   536.0 ms … 602.0 ms    10 runs
```
