CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = chat_client

all: $(TARGET)

$(TARGET): chat_cliet.c
	$(CC) $(CFLAGS) -o $(TARGET) chat_client.c
	
clean:
	rm -f $(TARGET)