
APPS 		= ./apps
BIN 		= ./bin
FLAGS 	= -Wall -std=gnu99 -lm

all: $(BIN)/main

$(BIN)/%: $(APPS)/%.c
	gcc $(FLAGS) $< -o $@

run:
	$(BIN)/main

clean:
	rm $(BIN)/*
