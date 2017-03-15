CFLAGS = -g -std=c99 -Wall -I ./include

.PHONY: clean doc

app-conway: app-conway.o cell.o load.o generate-image.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

cell: cell.o
	$(CC) $(CFLAGS) -o $@ $^

load: load.o
	$(CC) $(CFLAGS) -o $@ $^

generate-image: generate-image.o
	$(CC) $(CFLAGS) -o $@ $^

generate-animation:
	convert -delay 10 -loop 0 out/*.ppm out/animation.gif

add-files-svn:
	svn add --force src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q

clean:
	rm -f *.o app-conway
