WAL = -Wall -Werror -Wextra
WNO = -Wno-implicit-int
DBG = # -g -O0  # debug option
FLG = $(WAL) $(WNO) $(DBG)

bin/detab: src/detab.c Makefile
	gcc $(FLG) $< -o $@

.PHONY: clean

clean:
	rm -f bin/*
