#include "Scenegraph.h"
#include "TransformNode.h"
#include <stack>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

using namespace std;

Node * car;

Scenegraph::Scenegraph()
{
    root = NULL;
}

void Scenegraph::makeScenegraph(Node *r)
{
    if (root != NULL)
    {
        delete root;
        root = NULL;
    }

    this->root = r;
	
	if (this->root != NULL)
		this->root->setScenegraph(this);


	//car = root->getNode("car");
}

Scenegraph::~Scenegraph()
{
    if (root != NULL)
    {
        delete root;
        root = NULL;
    }
}

void Scenegraph::initShaderProgram(GLint shaderProgram)
{
   modelviewLocation = glGetUniformLocation(shaderProgram, "modelview");
   objectColorLocation = glGetUniformLocation(shaderProgram, "vColor");
}

void Scenegraph::draw(stack<glm::mat4>& modelView)
{
    if (root != NULL)
        root->draw(modelView);
}

void Scenegraph::animate(float time)
{
	/*TransformNode& tNode = dynamic_cast<TransformNode&>(*car);

	glm::mat4 transform = glm::mat4(1.0)
		* glm::rotate(glm::mat4(1.0), time * 100, glm::vec3(1, 0, 0));

	tNode.setAnimationTransform(transform);*/
}

