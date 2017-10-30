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

ifeq ($(PLATFORM),HOST)
    SOURCES = $(HOST_SOURCES)
    INCLUDES = $(HOST_INCLUDES)
    # Compiler Flags and Defines
    CC = gcc
    LD =
    LDFLAGS = -Wl,-Map=$(BASENAME).map
    CFLAGS = -Wall -Werror -g -O0 -std=c99
    CPPFLAGS = $(INCLUDES) -D$(PLATFORM) $(DEPFLAGS)
    # Architectures Specific Flags
    LINKER_FILE =
    CPU =
    ARCH =
    SPECS =
else
    SOURCES = $(MSP432_SOURCES)
    INCLUDES = $(MSP432_INCLUDES)
    CC = arm-none-eabi-gcc
    LD =
    LDFLAGS = -T msp432p401r.lds -Wl,-Map=$(BASENAME).map
    CFLAGS = -Wall -Werror -g -O0 -std=c99 -mcpu=cortex-m4 -mthumb -march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nosys.specs
    CPPFLAGS = $(INCLUDES) -D$(PLATFORM) $(DEPFLAGS)
    # Architectures Specific Flags
    LINKER_FILE =
    CPU =
    ARCH =
    SPECS =
endif

PREPS = $(SOURCES:.c=.i)
OBJS = $(SOURCES:.c=.o)
ASMS = $(SOURCES:.c=.asm)

%.i: %.c
	$(CC) -E $< $(CPPFLAGS) -o $@

%.o: %.i
	$(CC) -c $< $(CPPFLAGS) -o $@

%.asm: %.i
	$(CC) -S $< $(CPPFLAGS) -o $@

.PHONY: prep-all
prep-all: $(PREPS)

.PHONY: compile-all
compile-all: $(OBJS)
%.o: %.c
%.o: %.c $(DEPDIR)/%.d
	$(CC) -c $< $(CPPFLAGS) -o $@
	$(POSTCOMPILE)


.PHONY: asm-all
asm-all: $(ASMS)

.PHONY: build
build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

.PHONY: clean
clean:
	rm -f $(PREPS) $(OBJS) $(ASMS) $(BASENAME).out $(BASENAME).map

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SOURCES))))