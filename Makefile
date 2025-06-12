# Makefile for P-H Flash Thermodynamics Library

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
DEBUGFLAGS = -g -DDEBUG -O0
INCDIR = include
SRCDIR = src
OBJDIR = obj
LIBNAME = libph_flash.a

# Source files
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Default target
all: $(LIBNAME)

# Create object directory
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Create static library
$(LIBNAME): $(OBJS)
	ar rcs $@ $^
	@echo "Library $(LIBNAME) created successfully"

# Debug build
debug: CFLAGS += $(DEBUGFLAGS)
debug: $(LIBNAME)

# Clean build files
clean:
	rm -rf $(OBJDIR) $(LIBNAME)
	@echo "Build files cleaned"

# Install headers (optional)
install-headers:
	@mkdir -p /usr/local/include/ph_flash
	cp $(INCDIR)/*.h /usr/local/include/ph_flash/
	@echo "Headers installed to /usr/local/include/ph_flash/"

# Example compilation command for user programs
help:
	@echo "P-H Flash Thermodynamics Library Build System"
	@echo ""
	@echo "Targets:"
	@echo "  all     - Build the library (default)"
	@echo "  debug   - Build with debug information"
	@echo "  clean   - Remove build files"
	@echo "  help    - Show this help message"
	@echo ""
	@echo "Usage example:"
	@echo "  gcc -o my_app my_app.c -I./include -L. -lph_flash -lm"

.PHONY: all debug clean install-headers help