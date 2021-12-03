# A simple Makefile
# Manolo Martin G01268345
# CS 262, Lab Section 204
# Project 2
CC = gcc

TARGET = orderList_mmart2_204

CFLAGS=-g -Wall -std=c89 -pedantic-errors

LIBS=-lm

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	 rm $(TARGET)
