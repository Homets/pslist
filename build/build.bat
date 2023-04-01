@echo off

cl.exe ../src/pslist.c
move pslist.exe ..
del pslist.obj

if exist "../pslist.exe" (
echo "file compiled successfuly."
) else (
 echo "error in compilation."
)
