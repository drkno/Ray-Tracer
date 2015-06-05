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

## Controls
| Key    	| Action                              	|
|--------	|-------------------------------------	|
| Up     	| Move eye forward                    	|
| Down   	| Move eye back                       	|
| a      	| Toggle Anti-aliasing                	|
| +/=    	| Increase number of threads          	|
| -/_    	| Decrease number of threads          	|
| r      	| Force redraw                        	|
| f      	| Toggle fog                          	|
| [/{    	| Move beginning of fog closer to eye 	|
| ]/}    	| Move beginning of fog away from eye 	|
| ;/:    	| Move end of fog closer to eye       	|
| ‘/”    	| Move end of fog away from eye       	|
| ,/&lt; 	| Increase fog strength               	|
| ./&gt; 	| Decrease fog strength               	|
| ?      	| Cycle fog colour                    	|
| q      	| Quit                                	|

## License
All code that was not externally sourced is licensed under the MIT license.