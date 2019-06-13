include Makefile_common.mk
LIB = librobot.a
OBJS = memoire_24.o ConversionMemoire.o Interrupts.o fonctions_led.o debug.o son.o Piezo.o capteurs.o moteur.o communication.o

yeet: clean lib

lib: $(LIB)

$(LIB): $(OBJS)
	avr-ar rcs $@ $^

clean: 
	rm -f *.o 
	rm -f *.a
	rm -f *.d

