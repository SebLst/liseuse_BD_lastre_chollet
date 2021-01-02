# Projet liseuse de BD 

## Membres du projet

CHOLLET Tom
LASTRE Sébastien

## Dependencies

See wxWidgets dependencies based on your OS: https://github.com/wxWidgets/wxWidgets/

On linux
```
sudo apt-get install build-essential libgtk-3-dev
```

## Build

After cloning the repo, don't forget to ```git submodule update``` to get the external dependencies.

```
mkdir build
cd build
cmake ..
make
./cbreader
```