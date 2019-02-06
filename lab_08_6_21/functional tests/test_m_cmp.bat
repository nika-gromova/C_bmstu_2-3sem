@echo off
erase res.txt
.\..\app.exe m in_%1_1.txt in_%1_2.txt res.txt
fc res.txt out_%1.txt
pause