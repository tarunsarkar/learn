#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# <Put a Description Here>
#
# Use: make [TARGET] [PLATFORM-OVERRIDES]
#
# Build Targets:
#      <Put a description of the supported targets here>
#
# Platform Overrides:
#      <Put a description of the supported Overrides here
#
#------------------------------------------------------------------------------
include sources.mk

# Platform Overrides
PLATFORM = HOST
TARGET = c1m2.out

ifeq ($(PLATFORM),HOST)
    # Compiler Flags and Defines
    CC = gcc
    LD =
    LDFLAGS =
    CFLAGS = $(INCLUDES) -D$(PLATFORM)
    CPPFLAGs =
    # Architectures Specific Flags
    LINKER_FILE =
    CPU =
    ARCH =
    SPECS =
else
    CC = arm-none-eabi-gcc
    LD =
    LDFLAGS =
    CFLAGS = $(INCLUDES) -D$(PLATFORM)
    CPPFLAGs =
    # Architectures Specific Flags
    LINKER_FILE =
    CPU =
    ARCH =
    SPECS =
endif

OBJS = $(SOURCES:.c=.o)
.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@

