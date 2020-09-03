silm:
	gcc src/main.c src/depack.c src/asm.c src/utils.c src/platform.c -o silm-depack
clean:
	rm silm-depack