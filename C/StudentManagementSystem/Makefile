CC = gcc
CFLAGS = -Wall -Iinclude
SRC = main.c utils/*.c constants/*.c
TARGET = main

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
