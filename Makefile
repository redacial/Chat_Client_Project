CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = chat_client

all: $(TARGET)

$(TARGET): chat_client.c
	$(CC) $(CFLAGS) -o $(TARGET) chat_client.c
	
clean:
	rm -f $(TARGET)