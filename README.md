# Lorenz Attractor

A real-time 3D visualization of the Lorenz attractor built with raylib.

## The equations

The Lorenz system is three differential equations:

```
dx/dt = σ(y - x)
dy/dt = x(ρ - z) - y
dz/dt = xy - βz
```

The program integrates these every frame using Euler's method with `dt = 1/fps`, plotting each resulting point as a line segment to trace the attractor shape over time.

Default parameter values:

| Parameter | Symbol | Default |
| --------- | ------ | ------- |
| sigma     | σ      | 10.0    |
| rho       | ρ      | 28.0    |
| beta      | β      | 8/3     |

## Build

```bash
make main
```

This produces `./lorenz.exe`.

## Run

```bash
./lorenz.exe
./lorenz.exe <sigma>
./lorenz.exe <sigma> <rho>
./lorenz.exe <sigma> <rho> <beta>
```

Examples:

```bash
./lorenz.exe 10 28 2.666
./lorenz.exe 14 28 2.666
./lorenz.exe 10 99 2.666
```

## Controls

| Input           | Action        |
| --------------- | ------------- |
| Scroll wheel    | Zoom in / out |
