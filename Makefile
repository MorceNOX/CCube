CC = gcc
CFLAGS = -O2
LIBS = -lao -lm
SRCDIR = src
INCDIR = include
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)
TARGET = ccube
PREFIX ?= /usr/local
DATADIR ?= $(PREFIX)/share/ccube
BINDIR ?= $(PREFIX)/bin

.PHONY: all clean run install uninstall

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

install: $(TARGET)
	# Create installation directories
	mkdir -p $(DESTDIR)$(BINDIR)
	mkdir -p $(DESTDIR)$(DATADIR)
	# Install the binary
	cp $(TARGET) $(DESTDIR)$(BINDIR)/
	# Install data files (if they exist)
	# Note: We'll install data files to DATADIR
	# You may want to add your default data files here
	# For now, we'll just ensure the directory exists

uninstall:
	# Remove the binary
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)
	# Remove data directory if it's empty or remove specific files
	# Note: We don't remove the entire data directory to avoid removing user data
	# But we can remove files that were installed by this package
	# Remove any default data files that were installed
	# If you have default data files, add them here
	# For now, we just clean up the binary

# Install libao development libraries (Ubuntu/Debian)
install-libao-debian:
	sudo apt-get update
	sudo apt-get install -y libao-dev

# Install libao development libraries (CentOS/RHEL/Fedora)
install-libao-redhat:
	sudo yum install -y libao-devel

# Install libao development libraries (macOS with Homebrew)
install-libao-macos:
	brew install libao

# Check if libao is available
check-libao:
	@echo "Checking for libao development libraries..."
	@if pkg-config --exists libao; then \
		echo "libao development libraries found"; \
	else \
		echo "libao development libraries NOT found"; \
		echo "Please install them using one of these commands:"; \
		echo "  make install-libao-debian   (Ubuntu/Debian)"; \
		echo "  make install-libao-redhat   (CentOS/RHEL/Fedora)"; \
		echo "  make install-libao-macos    (macOS with Homebrew)"; \
	fi

# Show compilation flags
show-flags:
	@echo "CC: $(CC)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "LIBS: $(LIBS)"
	@echo "PREFIX: $(PREFIX)"
	@echo "DATADIR: $(DATADIR)"
	@echo "BINDIR: $(BINDIR)"