# STM32 NUCLEO-N657X0-Q Santa and Snow

STM32 NUCLEO-N657X0-Q Santa and snow for 8080 interface driver for the
3.5 inch Arduino 8BIT Module MAR3501 Display  (see my other repro for details about driver pin-out
etc.)

Another just for fun xmas project. A look a like xsnow application. XPM files have been taking from the original xsnow project and modified to RGB565.

This is not a full working stm32 project. The files here are part of a STM32CUBEIDE project for STM32N657X0HXQ. Create a project for this and then replace Src and Inc in the Core directory with the Src and Inc directories here. Also include the sources and headers from the xmas folder. All sources and headers are in the code folder. 

Use -Ofast for optimization to get all functions inlined, so it will run (almost) flicker free.