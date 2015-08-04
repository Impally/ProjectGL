all:
	g++ -o demo.exe main.cpp glew32.dll glfw3dll.a -I include -lOpenGL32 -L ./ -lglew32 -lglfw3 -lm