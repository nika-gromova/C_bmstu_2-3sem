@echo off
.\..\dyn2\app.exe in_%1.txt .\..\tests\out.txt
fc out.txt out_%1.txt
pause