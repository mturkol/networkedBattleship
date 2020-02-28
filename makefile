CC= g++
NAME = networkedBattleship.exe

all: CursesGUI.o WMap.o WBox.o WList.o WindowClass.o ShipClass.o MarkerClass.o ControlClass.o ServerClass.o ClientClass.o AIClass.o
	$(CC) -g project4.cpp  CursesGUI.o WMap.o WBox.o WList.o WindowClass.o ShipClass.o MarkerClass.o ControlClass.o ServerClass.o ClientClass.o AIClass.o -lncurses -o $(NAME)

ControlClass.o: ControlClass.cpp ControlClass.h GUIGLOBALCONSTANTS.h ShipClass.h CursesGUI.h MarkerClass.h ServerClass.h ClientClass.h
	$(CC) -g ControlClass.cpp -c
ServerClass.o: ServerClass.cpp ServerClass.h ServerSocket.h
	$(CC) -g ServerClass.cpp -c
ClientClass.o: ClientClass.cpp ClientClass.h ClientSocket.h
	$(CC) -g ClientClass.cpp -c
MarkerClass.o: MarkerClass.cpp MarkerClass.h ShipClass.h GUIGLOBALCONSTANTS.h
	$(CC) -g MarkerClass.cpp -c
CursesGUI.o: CursesGUI.cpp CursesGUI.h GUIGLOBALCONSTANTS.h WMap.h WBox.h WList.h ShipClass.h
	$(CC) -g CursesGUI.cpp -c
WMap.o: WMap.cpp WMap.h WindowClass.h ShipClass.h GUIGLOBALCONSTANTS.h
	$(CC) -g WMap.cpp -c
WBox.o: WBox.cpp WBox.h WindowClass.h
	$(CC) -g WBox.cpp -c
WList.o: WList.cpp WList.h WindowClass.h
	$(CC) -g WList.cpp -c
WindowClass.o: WindowClass.cpp WindowClass.h
	$(CC) -g WindowClass.cpp -c
ShipClass.o: ShipClass.cpp ShipClass.h GUIGLOBALCONSTANTS.h
	$(CC) -g ShipClass.cpp -c
AIClass.o: AIClass.cpp AIClass.h GUIGLOBALCONSTANTS.h
	$(CC) -g AIClass.cpp -c
clean:
	rm -rf networkedBattleship.exe *.o
