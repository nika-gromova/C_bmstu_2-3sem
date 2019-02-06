@echo off
erase res.txt
.\..\app.exe o in_%1.txt res.txt
fc res.txt out_%1.txt
pause