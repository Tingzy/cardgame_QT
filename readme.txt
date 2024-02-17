This project was started on 24/1/2023.

Build:
qmake -o Makefile qtMain.pro
make

Run on X:
./qtMain

Run on Wayland: 
weston &
./qtMain -platform wayland
