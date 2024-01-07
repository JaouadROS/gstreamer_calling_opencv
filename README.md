
# gstreamer_calling_opencv

This repository contains an example of how to call OpenCV functions within a GStreamer plugin. It demonstrates the integration of GStreamer with OpenCV for image processing tasks. The project is configured with CMake, making it easy to build and install on various platforms.

## Prerequisites

Before you begin, ensure you have the following installed:
- GStreamer: Make sure GStreamer and its development libraries are installed.
- OpenCV: You will need OpenCV and its development libraries.
- CMake: Required for building the project.
- A C++ compiler: GCC, Clang, or any C++ compiler compatible with your version of GStreamer and OpenCV.

## Compilation and Installation

1. **Clone the Repository:**
   
   First, clone this repository to your local machine using:
   ```bash
   git clone https://github.com/JaouadROS/gstreamer_calling_opencv 
   cd gstreamer_calling_opencv
   ```

2. **Build with CMake:**

   In the project directory, create a build directory and navigate into it:
   ```bash
   mkdir build
   cd build
   ```

   Configure the project with CMake:
   ```bash
   cmake ..
   ```

   Compile the project:
   ```bash
   make
   ```

3. **Install the Plugin:**

   After compiling, you can install the plugin. This might require administrative privileges:
   ```bash
   sudo make install
   ```

   This command installs the GStreamer plugin into `/usr/lib/gstreamer-1.0`.

## Running the Application

Once installed, the GStreamer plugin can be used by GStreamer applications. In this project, `gstImageProcessor` is an example executable that demonstrates how to load and use the plugin.

To run the `gstImageProcessor`, simply execute:
```bash
./gstImageProcessor
```

This executable will load the GStreamer plugin `cvimageprocessing` from `/usr/lib/gstreamer-1.0` and demonstrate its functionality, which involves using `cv::equalizeHist` for image processing within a GStreamer pipeline.

## Author
The code in this repository is inspired by the `gstcvequalizehist` plugin and re written by [JaouadROS](https://github.com/JaouadROS).
