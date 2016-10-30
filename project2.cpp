/*==================================================================================================
 PROGRAMMER:			Thomas Kroll, Nathan Kroll
 COURSE:				CSC 525/625
 MODIFIED BY:			Thomas Kroll:kroll001, Nathan Kroll:Kroll1483
 LAST MODIFIED DATE:	10/10/2016
 DESCRIPTION:			This program displays multiple objects on a 900x676 window.  The first thing
                        displayed is a pixel map, which is used as the background of this scene.
                        The pixel map is read from the file "pixel_map.txt" to be displayed.
                        Next the program displays a green Bitmap of tiny bushes (or broccoli)
                        randomly across the bottom of the screen.
                        Next is the (slightly creepy) stick figures, which are
                        composed of line segments, circles and partial circles.  The figures'
                        shields are made of a pattern filled polygon rendered on top of a solid
                        polygon. Lastly, the text "The Battle of Broccoli Fields" is written across
                        the top of the window.
 NOTE:					N/A
 FILES:					project1.cpp, pixel_map.txt (projProject.sln, ...)
 IDE/COMPILER:			MicroSoft Visual Studio 2013
 INSTRUCTION FOR COMPILATION AND EXECUTION:
	1.		Double click on myCPPproj.sln	to OPEN the project
	2.		Press Ctrl+F7					to COMPILE
	3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
	4.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glut.h>				// include GLUT library

class Window {
public:
	Window(int width, int height);
	void setFont(void* newFont);
	void* getFont();
	void setColor(float red, float green, float blue);
	float red();
	float green();
	float blue();
	void setWindowId(int id);
	int getWindowId();
	int getTextX();
	int getTextY();
	bool hasText();
	void resetTextPos();
	void textNextLine();
	void addChar(char key);
	void removeLastChar();
    std::vector<char> getText();
	void setUp(const char title[]);
private:
	int id;
	int width;
	int height;
	int textX, textY;
	int leftWorldX;
	int rightWorldX;
	int topWorldY;
	int lowerWorldY;
    const int line_height = 25;
	float color[3];
	void* font;
	std::vector<char> displayedText;
};

//Window(width of window, height of window)
Window::Window(int width, int height) {
	this->width = width;
	this->height = height;
	this->leftWorldX = (width / 2) * -1;
	this->rightWorldX = (width / 2);
	this->topWorldY = (height / 2);
	this->lowerWorldY = (height / 2) * -1;
	this->textX = this->leftWorldX + 10;
	this->textY = this->topWorldY - 15;
	this->font = GLUT_BITMAP_8_BY_13;
}

void Window::setUp(const char title[]) {
	glutInitWindowSize(width, height);				// specify a window size
	glutInitWindowPosition(leftWorldX, topWorldY);			// specify a window position
	glutCreateWindow(title);
	glClearColor(1, 1, 1, 0);			// specify a background color: white 
	gluOrtho2D(leftWorldX, rightWorldX, lowerWorldY, topWorldY);
}

void Window::setFont(void* newFont){this->font = newFont;}
void* Window::getFont() {return font;}
void Window::setColor(float red, float green, float blue){
    this->color[0] = red;
    this->color[1] = green;
    this->color[2] = blue;
}
float Window::red(){ return this->color[0]; }
float Window::green(){ return this->color[1]; }
float Window::blue(){ return this->color[2]; }
int Window::getWindowId(){ return this->id;}
int Window::getTextX(){ return this->textX; }
int Window::getTextY(){ return this->textY; }
void Window::resetTextPos(){
    this->textX = this->leftWorldX + 10;
    this->textY = this->topWorldY - 15;
}
void Window::textNextLine(){
    this->textX = this->leftWorldX + 10;
    this->textY = this->textY - this->line_height;
}
bool Window::hasText(){ return !this->displayedText.empty(); }
void Window::setWindowId(int id) { this->id = id; }
std::vector<char> Window::getText() { return displayedText; }
void Window::addChar(char key) { displayedText.push_back(key); }
void Window::removeLastChar() { displayedText.pop_back(); }


//***********************************************************************************
//GLOBALS
// Window dimentions
const int windowX = 680;
const int windowY = 800;
const unsigned int ENTER = 13;
const unsigned int BACKSPACE = 8;
Window editorWindow(windowX, windowY); 
//***********************************************************************************


//***********************************************************************************
//Global Function Definitions
//***********************************************************************************

void display_text(){
    glColor3f(editorWindow.red(), editorWindow.green(), editorWindow.blue());
    glRasterPos2i(editorWindow.getTextX(), editorWindow.getTextY());
    std::vector<char> text = editorWindow.getText();
    int chars = 0;
    for(int i = 0; i < text.size(); i++){
        if (text.at(i) == ENTER){
            chars = 0;
            editorWindow.textNextLine();
            glRasterPos2i(editorWindow.getTextX(), editorWindow.getTextY());
            continue;
        }
        if (chars == 60){
            chars = 0;
            editorWindow.textNextLine();
            glRasterPos2i(editorWindow.getTextX(), editorWindow.getTextY());
        }
        glutBitmapCharacter(editorWindow.getFont(), text.at(i));
        chars++;
    }
    editorWindow.resetTextPos();
}


//***********************************************************************************
void myInit()
{glClearColor(1, 1, 1, 0);			// specify a background clor: white 
 int x = windowX / 2;
 int y = windowY / 2;
 gluOrtho2D(-x, x, -y, y);  // specify a viewing area
}

//***********************************************************************************
void myDisplayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT);	// draw the background
    if (editorWindow.hasText())
        display_text();
    glFlush(); // flush out the buffer contents
}

void handleKey(unsigned char key, int mouseX, int mouseY){
    if (key == BACKSPACE)
        editorWindow.removeLastChar();
    else
        editorWindow.addChar(key);
    myDisplayCallback();
}

#ifdef _WIN32
#else
#endif


int main()
{
    //====================================================================//
    // These lines are only here so I (Thomas) can work on this at home
    // since the only c++ compiler available to me is g++
    // (Visual Studio and Linux don't play well together)
    int argc = 1;
    char *argv[1] = {(char*)"Something"};
    glutInit(&argc, argv);
    //====================================================================//

	editorWindow.setUp("Editor Window");
	glutKeyboardFunc(handleKey);
    glutDisplayFunc(myDisplayCallback);		// register a callback


    glutMainLoop();							// get into an infinite loop
}
