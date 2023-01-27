# mmCoreAndDevices
The c++ code at the core of the Micro-Manager project.

### Building with meson

```sh
mamba create -n mmbuild meson pkg-config boost-cpp
mamba activate mmbuild

BOOST_ROOT=$CONDA_PREFIX meson setup build
meson compile -C build
```
