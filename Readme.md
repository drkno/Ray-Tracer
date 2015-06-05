# Ray-Tracer
A ray tracer developed for a COSC363 assignment.

## Building
#### Prerequisites
- FreeGLUT
- C++11 Complient Compiler (Latest GCC, VS2012/VS2013)

#### Linux/OSX/BSD
```cd``` into this directory and type ```make```. Clang has a bug regarding ```#pragma once```, it can safely be ignored.

#### Windows
Open the Visual Studio 2013 solution file and press build.
<b>NOTE: Using Visual Studio below 2013 is untested, and below 2012 is known not to work due to lack of C++11 support.</b>

## Running
Ensure both Earth.raw and Moon.raw are in the same folder as the compiled executable. Run the executable, no extra
CLI arguments are required.

## License
All code that was not externally sourced is licensed under the MIT license.