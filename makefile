OBJS	= Source.o
SOURCE	= Source.cpp
HEADER	= 
OUT	= distance.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Source.o: Source.cpp
	$(CC) $(FLAGS) Source.cpp 


clean:
	rm -f $(OBJS) $(OUT)