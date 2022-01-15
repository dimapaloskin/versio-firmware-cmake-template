# versio-firmware-cmake-template

> Minimal cmake template for developing custom [versio platform](https://noiseengineering.us/pages/world-of-versio) firmware

## Get started
- [Prepare environment](https://github.com/electro-smith/DaisyWiki/wiki)
- Clone the repo
- Change `FIRMWARE_NAME` in the `CmakeLists.txt` file
- Change path to built firmware in the `flash.sh` file
- Build
```sh
cmake -B cmake-build-debug  -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/stm32h750xx.cmake

cmake --build cmake-build-debug
```
- Flash!


<p align="center">
  <img src="https://raw.githubusercontent.com/dimapaloskin/versio-firmware-cmake-template/master/media/versio-blank-panel.jpg">
</p>
