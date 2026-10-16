# Device Info Shared Library (`lib_device_info`)

`lib_device_info` is a native C++ dynamic shared library (`cc_library_shared`) built for the Android Open Source Project (AOSP). It exposes utility APIs to query core Android system properties (release version, API level, model, and brand) and issue system notifications using native shell commands.

> **Target Consumer:** This library is a direct dependency required by the [`hello_aosp`](https://github.com/germanloera/hello_aosp) companion binary module.

---

## Features & Functionality

The library defines functions under the `info` namespace declared in `include/lib_device_info.h` and implemented in `src/lib_device_info.cpp`:

| Function                   | Description                                            | Underlying Mechanism                                               |
| :------------------------- | :----------------------------------------------------- | :----------------------------------------------------------------- |
| `GetProperty(string prop)` | Retrieves system properties with fallback `"-1"`       | Calls `android::base::GetProperty` (`<android-base/properties.h>`) |
| `PrintVersion()`           | Outputs the Android release version to standard output | Reads system property `ro.build.version.release`                   |
| `PrintAPI()`               | Outputs the SDK API level                              | Reads system property `ro.build.version.sdk`                       |
| `PrintModel()`             | Outputs device model name                              | Reads system property `ro.product.model`                           |
| `PrintBrand()`             | Outputs manufacturer/product brand                     | Reads system property `ro.product.brand`                           |
| `Notify()`                 | Posts a system tray notification                       | Invokes `cmd notification post` via standard `system()` execution  |

---

## Project Structure

```text
lib_device_info/
├── Android.bp                  # Soong build configuration
├── include/
│   └── lib_device_info.h       # Exported public header
├── src/
│   └── lib_device_info.cpp     # Library implementation
└── README.md
```

### Build Definition Highlights (`Android.bp`)

- **Target Type:** `cc_library_shared` — builds into `lib_device_info.so`.
- **Exported Headers:** `export_include_dirs: ["include"]` allows consumers (such as `hello_aosp`) to include `<lib_device_info.h>` directly when adding `lib_device_info` to their `shared_libs`.
- **Dependencies:** Relies on `libbase` and `liblog`.

---

## Installation & Placement

Clone this repository into the `system/extras/` path from your AOSP root:

```bash
# Navigate to the AOSP root
cd /path/to/aosp/root

# Clone the repository
git clone <repository-url> system/extras/lib_device_info
```

Expected destination: `system/extras/lib_device_info/`

---

## Build Instructions

### 1. Standalone / Targeted Build

To compile only `lib_device_info`:

```bash
# Initialize build environment
source build/envsetup.sh

# Select your lunch target (e.g. Goldfish emulator or generic device)
lunch sdk_phone_x86_64-userdebug

# Build the shared library target
m lib_device_info
```

Alternatively, navigate into the directory and build locally:

```bash
cd system/extras/lib_device_info
mm
```

The compiled library will output to `$ANDROID_PRODUCT_OUT/system/lib/` or `$ANDROID_PRODUCT_OUT/system/lib64/` depending on your architecture.

---

### 2. Including in the System Image (`system.img`)

To bundle `lib_device_info.so` into the system image automatically, add it to `PRODUCT_PACKAGES` inside your product definition makefile (such as `build/make/target/product/handheld_system.mk`):

```make
PRODUCT_PACKAGES += \
    lib_device_info
```

Then trigger an AOSP build:

```bash
m
```

---

## Usage in Consumer Modules (`hello_aosp`)

To consume this library in other native binaries or shared libraries (e.g., `hello_aosp`), configure their `Android.bp`:

```bp
cc_binary {
    name: "hello_aosp",
    srcs: ["main.cpp"],
    shared_libs: [
        "libbase",
        "liblog",
        "lib_device_info", // <--- Include the library here
    ],
}
```

Include the public header in your consumer source files:

```cpp
#include <lib_device_info.h>

int main() {
    info::PrintVersion();
    info::PrintAPI();
    info::PrintModel();
    info::PrintBrand();
    info::Notify();
    return 0;
}
```
