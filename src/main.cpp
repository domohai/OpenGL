#include <GL/glew.h> // must include first
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

static unsigned int CompileShader(unsigned int type, const string& source);
static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);
static void ParseShader(const string& filepath);

int main(void) {
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit()) return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	// First you need to create a valid OpenGL rendering context 
	// and call glewInit() to initialize the extension entry points
	// init glew
	if (glewInit() != GLEW_OK) {
		cout << "Failed to init GLEW" << endl;
	}

	// positions 
	float pos[] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	// generate buffer
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);
	// enable the buffer
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	/*
	// write shader program
	string vertexShader = 
		"#version 330 core"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"\n"
		"void main() {\n"
		"	gl_Position = position;\n"
		"}";

	string fragmentShader =
		"#version 330 core"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"void main() {\n"
		"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}";
	*/
	//unsigned int shader = CreateShader(vertexShader, fragmentShader);
	//glUseProgram(shader);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	//glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}

static unsigned int CompileShader(unsigned int type, const string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);
	// debug shader
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " << (type == GL_VERTEX_SHADER ?
			"vertex" : "fragment") << "shader!" << endl;
		cout << message << endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}

static void ParseShader(const string& filepath) {

	enum ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	ifstream in(filepath);
	string line;
	ShaderType type = NONE;

	while (getline(in, line)) {
		
	}
}