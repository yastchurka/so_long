CC = cc
#CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -ldl -lglfw -pthread -lm
TARGET = my_program

SRCS = test2.c \
	renderElements.c \
	renderTheGrid.c \
	checkIfPassable.c \
	determineMapSize.c \
	
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) libmlx42.a $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
