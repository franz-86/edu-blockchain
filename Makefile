# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# OpenSSL paths (automatically obtained from Homebrew on my mac)
OPENSSL_PREFIX = $(shell brew --prefix openssl)
INCLUDES = -I$(OPENSSL_PREFIX)/include
LIBS = -L$(OPENSSL_PREFIX)/lib -lcrypto

# Target and source files
TARGET = edublockchain
SRCS = src/main.cpp src/block.cpp src/blockchain.cpp src/transaction.cpp src/utils/sha256.cpp src/utils/time.cpp 

# Default rule
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET) $(LIBS)

# Clean rule
clean:
	rm -f $(TARGET)
