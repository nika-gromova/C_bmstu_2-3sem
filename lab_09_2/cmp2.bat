@echo off
erase out.txt
app.exe in_%1.txt out.txt -s a -r bb
fc out.txt out_%1.txt
pause