DEPS = common.h planificador.h generator_api.h

lector: lector.o planificador.o common.o libgenerator.a
	gcc -o $@ $^ -lpthread -lm

%.o: %.c $(DEPS)
	gcc -c $<

.PHONY: clean
clean:
	rm -rf lector *.o