# electribe-song-mode

Simple pattern chain tool for Korg Electribe 2 - so called "song mode".

## Dependencies

This projects uses CMake as a build system. It works with version 3.13, however older versions should be fine.

To build project dependencies you need `autoconf`, `automake` and `libtool`.
On macOS you can get them with `brew install autoconf automake libtool `.

## Build
```
bash build.sh
```

## Run
```
cd build
./electribe-song-mode
```

## Example sequence (JSON file)
```
{
    "bpm": 120,
    "patterns": [
        {
            "name": "PatternA",
            "id": 1,
            "length": 2,
            "repeat": 2
        },
        {
            "name": "PatternB",
            "id": 2,
            "length": 2,
            "repeat": 2
        }
    ]
}
```
