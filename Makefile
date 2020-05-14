LDLIBS=-lczmq -lzmq
EXES=client_push server_pull

all: $(EXES)

clean:
	$(RM) $(EXES)
