# This Makefile assumes SDL2 was installed using "brew"

a.out: redflicker.c Makefile
	clang -std=c11 -I/Library/Frameworks/SDL2.framework/Headers/ redflicker.c /usr/local/lib/libSDL2.a \
-framework CoreAudio \
-framework AudioUnit \
-framework CoreFoundation \
-framework CoreGraphics \
-framework ForceFeedback \
-framework IOKit \
-framework AppKit \
-framework Carbon \
-liconv

clean:
	rm -f a.out
