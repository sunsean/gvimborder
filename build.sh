#!/bin/bash

PATH="/c/Program Files (x86)/mingw-w64/i686-7.1.0-win32-dwarf-rt_v5-rev2/mingw32/bin:$PATH"

gcc \
  -shared -s -m32 \
  -o gvimborder.dll \
  gvimborder.c \
  -luser32 -lgdi32

mv gvimborder.dll "/c/Program Files (x86)/Vim/vim73/"

"/c/Program Files (x86)/Vim/vim73/gvim.exe"
