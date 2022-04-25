all:Serial
 
OBJS = Serial.o
 
Serial:$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lpthread
 
clean:
	rm -f Serial *.o