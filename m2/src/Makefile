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
BASENAME = c1m2
TARGET = $(BASENAME).out

DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

COMM_CFLAGS = -Wall \
     -Werror \
     -g \
     -O0 \
     -std=c99


ifeq ($(PLATFORM),HOST)
    SOURCES = $(HOST_SOURCES)
    INCLUDES = $(HOST_INCLUDES)
    # Compiler Flags and Defines
    CC = gcc
    LD =
    LDFLAGS = -Wl,-Map=$(BASENAME).map
    CFLAGS = $(COMM_CFLAGS)
    CPPFLAGS = $(INCLUDES) -D$(PLATFORM) $(DEPFLAGS)
    LINKER_FILE =
else
    SOURCES = $(MSP432_SOURCES)
    INCLUDES = $(MSP432_INCLUDES)
    CPU = -mcpu=cortex-m4
    ARCH = -mthumb \
        -march=armv7e-m \
        -mfloat-abi=soft \
        -mfpu=vfpv4-d16

    SPECS = --specs=nosys.specs
    CC = arm-none-eabi-gcc
    LD =
    LDFLAGS = -Wl,-Map=$(BASENAME).map
    CFLAGS = $(COMM_CFLAGS) $(CPU) $(ARCH) $(SPECS)
    CPPFLAGS = $(INCLUDES) -D$(PLATFORM) $(DEPFLAGS) -nostartfiles
    # Architectures Specific Flags
    LINKER_FILE = -T msp432p401r.lds
endif

PREPS = $(SOURCES:.c=.i)
OBJS = $(SOURCES:.c=.o)
ASMS = $(SOURCES:.c=.asm)

%.i: %.c
	$(CC) -E $< $(CPPFLAGS) -o $@

%.o: %.i
	$(CC) -c $< $(CPPFLAGS) $(CFLAGS) -o $@

%.asm: %.i
	$(CC) -S $< $(CPPFLAGS) $(CFLAGS) -o $@

.PHONY: prep-all
prep-all: $(PREPS)

.PHONY: compile-all
compile-all: $(OBJS)
%.o: %.c
%.o: %.c $(DEPDIR)/%.d
	$(CC) -c $< $(CPPFLAGS) $(CFLAGS) -o $@
	$(POSTCOMPILE)


.PHONY: asm-all
asm-all: $(ASMS)

.PHONY: build
build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LINKER_FILE) $(LDFLAGS) -o $@

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

.PHONY: clean
clean:
	rm -f $(PREPS) $(OBJS) $(ASMS) $(BASENAME).out $(BASENAME).map

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SOURCES))))