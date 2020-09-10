APPNAME := main
C := g++ -std=c++11 -Wall
INC := -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers -I include
FW := -framework SDL2 -framework SDL2_ttf -framework SDL2_mixer -F/Library/Frameworks

main: main.o app.o textManager.o ball.o bar.o
	$C -o $(APPNAME) main.o app.o textManager.o ball.o bar.o $(FW)

main.o: main.cpp
	$C -c $< -I include $(INC)

app.o: app.cpp app.h globals.h
	$C -c $< -I include $(INC)

textManager.o: textManager.cpp textManager.h
	$C -c $< $(INC)

ball.o: ball.cpp ball.h globals.h bar.h
	$C -c $< $(INC)

bar.o: bar.cpp bar.h globals.h
	$C -c $< $(INC)

vpath %.cpp src
vpath %.h include
