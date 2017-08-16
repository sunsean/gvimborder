1. Copy the `gvimborder.dll` to the same folder as `gvim.exe`
2. Add the following to `_vimrc`

   ```vim
   autocmd VimEnter * call libcallnr("gvimborder.dll", "SetBorder", 0x080808)
   ```

<sub>Based on work from Derek McLoughlin and Yasuhiro Matsumoto.</sub>
