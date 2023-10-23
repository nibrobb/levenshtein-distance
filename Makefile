all: levenshtein

levenshtein: main.c
	$(CC) -O2 -o $@ $^

clean:
	rm -f levenshtein
