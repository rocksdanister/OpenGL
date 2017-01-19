
#include <math.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

const char* vertexSource =
"#version 150\n"
"in vec2 position;"
"in vec3 color;"
"in vec2 texcoord;"
"out vec3 Color;"
"out vec2 Texcoord;"
"void main() {"
"	Color = color;"
"	Texcoord = texcoord;"
"	gl_Position = vec4( position, 0.0, 1.0 );"
"}";

const char* fragmentSource =
"#version 150\n"
"in vec3 Color;"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D tex;"
"uniform sampler2D tex2;"
"void main() {"
"vec4 pic1=texture(tex,Texcoord);"
"vec4 pic2=texture(tex2,Texcoord);"
"	outColor = mix(pic1,pic2,0.5);"
"}";

GLuint vertexShader;
GLuint fragmentShader;
GLuint shaderProgram;

void compileVertexShader() {
    vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &vertexSource, NULL );
    glCompileShader( vertexShader );


    GLint status;
    char buffer[512];
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &status );
    glGetShaderInfoLog( vertexShader, 512, NULL, buffer );

}

void compileFragmentShader() {

    fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &fragmentSource, NULL );
    glCompileShader( fragmentShader );


    GLint status;
    char buffer[512];
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &status );
    glGetShaderInfoLog(fragmentShader, 512, NULL, buffer );

}

void linkShaderProgram() {

    shaderProgram = glCreateProgram();
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glBindFragDataLocation( shaderProgram, 0, "outColor" );
    glLinkProgram( shaderProgram );
    glUseProgram( shaderProgram );
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
/*
    float vertices[] = {

        -0.5f,  0.5f,      1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // Top-left
        0.5f,  0.5f,        0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // Top-right
        0.5f, -0.5f,       0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f,     1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom-left
    };

*/
float vertices[] = {

    -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
     1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
     1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
    -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
};

	GLuint vao;
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );


    GLuint vbo;
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );


    GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};


    GLuint ebo;
    glGenBuffers( 1, &ebo );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );

    compileVertexShader();
    compileFragmentShader();
    linkShaderProgram();


    GLint posAttrib = glGetAttribLocation( shaderProgram, "position" );
    glEnableVertexAttribArray( posAttrib );
    glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0 );

    GLint colAttrib = glGetAttribLocation( shaderProgram, "color" );
    glEnableVertexAttribArray( colAttrib );
    glVertexAttribPointer( colAttrib, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)( 2*sizeof(float) ) );

    GLint texAttrib = glGetAttribLocation( shaderProgram, "texcoord" );
    glEnableVertexAttribArray( texAttrib );
    glVertexAttribPointer( texAttrib, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)( 5*sizeof(float) ) );


	GLuint text[2];
	glGenTextures( 2, text );

	int width, height;
	unsigned char* image;
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,text[0]);
  image = SOIL_load_image( "sample2.png", &width, &height, 0, SOIL_LOAD_RGB );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );
  glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );


glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D,text[1]);
image = SOIL_load_image( "sample.png", &width, &height, 0, SOIL_LOAD_RGB );
glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
SOIL_free_image_data( image );
glUniform1i(glGetUniformLocation(shaderProgram, "tex2"), 1);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );


    while(!glfwWindowShouldClose(window)){

		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );


        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
          glfwSwapBuffers(window);
          glfwPollEvents();
    }

  glDeleteTextures( 2, text );
  glDeleteProgram( shaderProgram );
	glDeleteShader( fragmentShader );
	glDeleteShader( vertexShader );
	glDeleteBuffers( 1, &vbo );
	glDeleteVertexArrays( 1, &vao );

    glfwTerminate();
}
