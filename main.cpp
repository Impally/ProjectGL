#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

const char* vertex_shader=
"#version 450\n"
"in vec3 vp;"
"void main(){"
"gl_Position = vec4(vp, 1.0);"
"}";

const char* fragment_shader=
"#version 450\n"
"out vec4 frag_colour;"
"void main(){"
"frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
"}";

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
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

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