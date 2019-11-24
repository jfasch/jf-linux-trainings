# Jörg Faschingbauer's Linux Trainings: Supporting Code

## Trainings, Supporting Material

The [``trainings``](trainings/) subdirectory contains support material
created per training.

## Building and Installing

The project's C/C++ is built with
[Meson](https://mesonbuild.com/). Meson uses
[Ninja](https://ninja-build.org/) by default, so make sure you have
both installed. Then,

1. Change to the project's root directory (`~/jf-linux-trainings`)
1. Generate Ninja files from there, into the build directory (`/tmp/builddir`)
1. Change to the build directory, and build.
1. Optionally, install into the *prefix* directory (`/tmp/installdir`)


```
$ cd ~/jf-linux-trainings
$ meson /tmp/builddir
$ cd /tmp/builddir
$ ninja
$ ninja install # optional
```
   
