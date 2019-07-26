OBJS1	=	server_main.o server_net.o server_command.o win.o 
OBJS2	=	client_main.o client_net.o client_command.o win.o            wii_thread.o
TARGET1	=	server
TARGET2	=	client
CFLAGS	=	-c -DNDEBUG

.c.o:
	gcc $(CFLAGS) $<

all: $(TARGET1) $(TARGET2)

$(TARGET1):	$(OBJS1)
	gcc -o $(TARGET1) $(OBJS1) -lm -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf -Wl,-rpath,/usr/local/lib -lcwiimote -D_ENABLE_TILT -D_ENABLE_FORCE -L/usr/lib
$(TARGET2):	$(OBJS2)
	gcc -o $(TARGET2) $(OBJS2) -lm -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf -Wl,-rpath,/usr/local/lib -lcwiimote -D_ENABLE_TILT -D_ENABLE_FORCE -L/usr/lib

clean:
	rm *.o $(TARGET1) $(TARGET2)

server_main.o: server_main.c headers.h server.h others.h
server_net.o: server_net.c headers.h server.h others.h
server_command.o: server_command.c headers.h server.h others.h
client_main.o: client_main.c client.h others.h headers.h
client_net.o: client_net.c client.h others.h headers.h
client_command.o: client_command.c client.h others.h headers.h
win.o: win.c            client.h others.h headers.h
wii_thread.o: wii_thread.o client.h others.h headers.h
