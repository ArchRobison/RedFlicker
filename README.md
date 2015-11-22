# RedFlicker

This program should display an all-blue screen, but on buggy systems displays a
red flicker at the top of the screen.  

Bug is known to appear on a 2015 MacBook Air running MacOS 10.11.1.

# To Build and Run

1. Install SDL2.  The Makefile presumes it was installed using "brew".  You might have
   to change paths in the Makefile if you install SDL2 another way.
2. Run "make"
3. Run "./a.out"
