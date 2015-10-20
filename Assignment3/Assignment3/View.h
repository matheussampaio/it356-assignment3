#ifndef VIEW_H
#define VIEW_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <stack>

#include "Scenegraph.h"

#include <glm/glm.hpp>

#include <utils/Object.h>

using namespace std;

class View
{
    // we need this #define for convenience in some OpenGL 4 functions. As you can see it is just a typecast
	#define BUFFER_OFFSET(offset) ((void *)(offset))

    // a structure that encapsulates information about our GLSL shaders.
    typedef struct {
        GLenum  type; // is it a vertex shader, a fragment shader, a geometry shader, a tesselation shader or none of the above?
        string  filename; // the file that stores this shader
        GLuint  shader; // the ID for this shader after it has been compiled
    } ShaderInfo;

public:
    View();
    ~View();

    // the delegation functions called from the glut functions in main.cpp
    void resize(int w, int h);
    void initialize();
    void draw();
    void openFile(string filename);

    void mousepress(int x, int y);
    void mousemove(int x, int y);

    // helper functions to probe the supported (latest) version of OpenGL and GLSL.
    void getOpenGLVersion(int *major, int *minor);
    void getGLSLVersion(int *major, int *minor);

protected:
    // helper function to compile and link our GLSL shaders
    GLuint createShaders(ShaderInfo *shaders);

    // helper function to print error messages for shader compiling
    void printShaderInfoLog(GLuint shader);

private:
    int WINDOW_WIDTH, WINDOW_HEIGHT;

    GLint projectionLocation, modelviewLocation, objectColorLocation;

    Scenegraph sgraph;

    // the actual projection and modelview matrices
    stack<glm::mat4> proj, modelview;

    // the trackball transform
    glm::mat4 trackballTransform;

	// time for the animation
	double time;

    glm::vec2 prev_mouse;
	
	GLuint program;
};

#endif // VIEW_H