SRC=main3E.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -g -o proj3E

.C.o: $<
	g++ -I. -g -c $<

clean:
	rm *.o proj3E
