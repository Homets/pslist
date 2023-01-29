@echo off

cd ../src/
cl.exe pslist.c
cd ../
rd pslist.obj
