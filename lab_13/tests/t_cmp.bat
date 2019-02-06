@echo off
(.\..\app.exe in_%1.txt) < command_%1.txt
fc out.txt out_%1.txt
pause