This project was started on 24/1/2023.

Build:
qmake -o Makefile qtMain.pro
make

Run on X:
./qtMain

Run on Wayland: 
weston &
./qtMain -platform wayland

Current state:
No logic for a poker game yet. when dealing cards, it only deal A spade because there is no logic to random the card yet.
Graphics works OK. 
Game asset: background images not completed (using placeholder now), only card images for spade available.

