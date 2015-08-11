#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <Managers/Shader_Manager.h>

int main(){
	//initializing everything
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	//Tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS);  //depth testing interprets a smaller value as closer

	GLfloat points[] ={
		0.0f, 0.5f, 0.0f,
		0.5f,-0.5f, 0.0f,
		-0.5f,-0.5f,0.0f
	};
	
	//initializes Vertex Buffer Array
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//binds points into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	//initializing the Vertex Attribute Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Returns an unsigned integer to associate with this Vertex Array later
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//Shader stuff
	//associate Vertex Shader
	Managers::Shader_Manager shaderProgram;
	shaderProgram.CreateProgram("Initial Shader", "Shaders\\vertex.vs", "Shaders\\fragment.frag");

	//associate and compile Fragment Shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	while(!glfwWindowShouldClose(window)){
		//clear drawing surface
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		//draw the first three points in the currently bound VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//update other things
		glfwPollEvents();
		//Swap the buffers into the window
		glfwSwapBuffers(window);
	}




	glfwTerminate();
	return 0;
}