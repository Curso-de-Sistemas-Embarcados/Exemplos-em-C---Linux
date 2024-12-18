CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = programa1

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm -f $(TARGET)