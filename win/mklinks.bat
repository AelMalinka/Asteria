@echo off

rmdir Entropy\include\Entropy
rmdir Hecate\include\Entropy\Hecate
mklink /d Entropy\include\Entropy ..\..\..\..\Entropy\src
mklink /d Hecate\include\Entropy\Hecate ..\..\..\..\..\Hecate\src