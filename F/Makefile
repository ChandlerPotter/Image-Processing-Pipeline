SRC=main3F.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C logging.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -g -o proj3F

.C.o: $<
	g++  -I. -g  -c $<

clean:
	rm *.o proj3F
