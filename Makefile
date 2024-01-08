CC = cc
#CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -ldl -lglfw -pthread -lm
TARGET = so_long

SRCS = test3.c \
	checkIfPassable.c \
	assignPositions.c \
	determineMapSize.c \
	renderTheGrid.c \
	renderElements.c \
	moves.c 
	
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) libmlx42.a $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
