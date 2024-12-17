#Ali Osman Öcalır - B221210404 – 1. Öğretim B Grubu

#Zeynep İrem Tekin - B191210047 - 1. Öğretim B Grubu

#Tunahan Şahin - G201210023 - 2. Öğretim B Grubu

#Dursun Özer - B231210301 - 1. Öğretim A Grubu

#Büşra Kaya – B201210045 – 1. Öğretim C Grubu


CC = gcc
CFLAGS = -Wall -g

SOURCES = main.c parser.c executor.c signals.c io_redirect.c pipe.c builtin.c pipeparser.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = shell

all: $(TARGET)
	clear
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	rm -f $(TARGET) $(OBJECTS)
