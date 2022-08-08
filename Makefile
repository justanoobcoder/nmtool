.PHONY: all clean

CC = g++
CFLAGS = -Wall
LDFLAGS = 
OBJFILES = main.o utils.o
TARGET = nmtool

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)
