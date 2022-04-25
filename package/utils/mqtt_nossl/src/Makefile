
all:mqtt_nossl


OBJS = mqtt_nossl.o

mqtt_nossl:$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lpthread -lmosquitto

clean:
	rm -f mqtt_nossl *.o
    
    
    