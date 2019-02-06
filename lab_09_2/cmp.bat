@echo off
erase out.txt
app.exe in_%1.txt out.txt -s a -r b
fc out.txt out_%1.txt
pause