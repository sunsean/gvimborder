#!/bin/bash

# Set path to 32bit GCC
PATH="/c/Program Files (x86)/mingw-w64/i686-7.1.0-win32-dwarf-rt_v5-rev2/mingw32/bin:$PATH"

# Build dll
gcc \
  -shared -s -m32 \
  -o gvimborder.dll \
  gvimborder.c \
  -luser32 -lgdi32

# Copy dll to gvim
cp gvimborder.dll "/c/Program Files (x86)/Vim/vim73/"

# Test functionality
"/c/Program Files (x86)/Vim/vim73/gvim.exe"
