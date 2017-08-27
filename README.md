# Shader Preset Support
This is a Kodi binary addon for libretro meta shader support (.cgp files). It passes things like the preset configuration and options, shader source, LUTs/texture paths to Kodi.

## Building

Building this add-on requires Kodi's internal CMake-based build system for binary add-ons. If you are cross-compiling or just packaging the add-on, it is recommended that you use the Makefile provided with Kodi.

The Makefile will download, build and install the add-on and its dependencies. There is no need to manually clone the add-on if Kodi's source is available.

### Building on Linux

First, make sure Kodi's add-on build system is installed somewhere. You can perform a system install (to `/usr/local`) or a local install (I prefer `$HOME/kodi`). Specify this when you build Kodi:

```shell
./bootstrap
./configure --prefix=$HOME/kodi
make
make install
```

Clone the repo and make sure to download the submodules too with:
```shell
git clone https://github.com/VelocityRa/game.shader.presets.git --recursive
```
If you just want the submodules do:
```shell
git submodule update --init --recursive
```

Now, run the Makefile with the path to the build system:

```shell
cd tools/depends/target/binary-addons
make PREFIX=$HOME/kodi ADDONS="game.shader.presets"
```

You can specify multiple add-ons, and wildcards are accepted too. For example, `ADDONS="pvr.*"` will build all pvr add-ons.

On Linux this performs a cross-compile install, so to package the add-on you'll need to copy the library and add-on files manually:

```shell
mkdir game.shader.presets
cp -r $HOME/kodi/share/kodi/addons/game.shader.presets/ .
cp -r $HOME/kodi/lib/kodi/addons/game.shader.presets/ .
```

To rebuild the add-on or compile a different one, clean the build directory:

```shell
make clean
```

### Building on OSX

Building on OSX is similar to Linux, but all the paths are determined for you. This command will download, build and install the add-on to the `addons/` directory in your Kodi repo:

```shell
cd tools/depends/target/binary-addons
make ADDONS="game.shader.presets"
```

### Building on Windows

First, download and install [CMake](http://www.cmake.org/download/).

To compile on windows, open a command prompt at `tools\buildsteps\win32` and run the script:

```
make-addons.bat install game.shader.presets
```

## Developing

When developing, compiling from a git repo is more convenient than repeatedly pushing changes to a remote one for Kodi's Makefile.

### Developing on Linux

The add-on requires several dependencies to build properly. Like Kodi's build system, you can perform a system install or a local one (demonstrated here).

First, clone p8-platform and build per standard CMake:

```shell
git clone https://github.com/Pulse-Eight/platform.git
cd platform
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_INSTALL_PREFIX=$HOME/kodi \
      ..
make
make install
```

The kodi-platform library was split from p8-platform. Do the same as above for this library:

```
git clone https://github.com/xbmc/kodi-platform.git
cd kodi-platform
...
```

With these dependencies in place, the add-on can be built:

```shell
git clone https://github.com/VelocityRa/game.shader.presets.git
cd game.shader.presets
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_PREFIX_PATH=$HOME/kodi \
      -DCMAKE_INSTALL_PREFIX=$HOME/workspace/kodi/addons \
      -DPACKAGE_ZIP=1 \
      ..
make
make install
```

where `$HOME/workspace/kodi` symlinks to the directory you cloned Kodi into.

### Developing on Windows

This instructions here came from this helpful [forum post](http://forum.kodi.tv/showthread.php?tid=173361&pid=2097898#pid2097898).

First, open `tools\windows\prepare-binary-addons-dev.bat` and change `-DCMAKE_BUILD_TYPE=Debug ^` to `-DCMAKE_BUILD_TYPE=Release ^`.

Open a command prompt at `tools\windows` and run the script:

```shell
prepare-binary-addons-dev.bat game.shader.presets
```

Open `cmake\addons\build\kodi-addons.sln` and build the solution. This downloads the add-on from the version specified in its text file (see above) and creates a Visual Studio project for it. If the build fails, try running it twice.

This should package and copy the add-on to the `addons/` directory. If not, you can try opening the solution `cmake\addons\build\<addon-id>-prefix\src\<addon-id>-build\<addon-id>.sln` and building the INSTALL project or, worse case, copy by hand.
