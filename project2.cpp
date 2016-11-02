/*==================================================================================================
 PROGRAMMER:			Thomas Kroll, Nathan Kroll
 TRACE:                 kroll001, Kroll1483
 COURSE:				CSC 525/625
 MODIFIED BY:			Thomas Kroll:kroll001, Nathan Kroll:Kroll1483
 LAST MODIFIED DATE:	11/02/2016
 TASKS COMPLETED BY:    Thomas Kroll, kroll001: 50%
                            -User can type text into the text editor window (line length 60 chars)
                            -When the line is full, the text automatically wraps to the next line
                            -User can type ENTER to go to the next line
                            -User can type BACKSPACE to remove the last character
                            -User can select starting position of text
                        
                        Nathan Kroll, Kroll1483: 50%
                            -User can minimize the help window
                            -Help window displays detailed instructions
                            -User can select the Font of the text in the editor window
                            -User can select the color of the text in the editor window
                            -User can save the text in the editor window to a txt file
                            -User can terminate the program through the menu
 DESCRIPTION:           This program opens two windows on launch.  One is a help window that
                        describes how to operate the second window, which is the text editor
                        window.  In the text editor, left clicking before typing will choose
                        the starting location for the text.  Right clicking will open a menu
                        that lets you choose the font type, and the text color.  The menu
                        also gives you the option to save to a text file or exit the program.
                        This program auto-wraps a line of text at 60 characters.  Also while
                        typing, you may hit enter at any time to move to the next line, or hit
                        backspace at any time to remove the last character (and then the next
                        to last character and so on).

 NOTE:					N/A
 FILES:					project2.cpp, (projProject.sln, ...)
 IDE/COMPILER:			MicroSoft Visual Studio 2013
 INSTRUCTION FOR COMPILATION AND EXECUTION:
    MICROSOFT VISUAL STUDIO:
        1.		Double click on myCPPproj.sln	to OPEN the project
        2.		Press Ctrl+F7					to COMPILE
        3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
        4.		Press Ctrl+F5					to EXECUTE
    LINUX/G++ COMMAND LINE:
        1.      Open a terminal in the project directory
        2.      Execute command to COMPILE: g++ -std=c++11 project2.cpp -o PROJECT -lGL -lGLU -lglut
        3.      Execute command to EXECUTE: ./PROJECT
==================================================================================================*/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glut.h>				// include GLUT library


//***********************************************************************************
//GLOBALS

const unsigned int ENTER = 13;
const unsigned int BACKSPACE = 8;

//For Menus
const int SAVE = 0;
const int COLOR = 1;
const int FONT = 2;
const int MINIMIZE = 3;
const int EXIT = 4;
const int RED = 5;
const int GREEN = 6;
const int BLUE = 7;
const int TIMES_NEW_ROMAN = 8;
const int HELVETICA = 9;
const int BITMAP = 10;
//***********************************************************************************

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
	int getLineWidth();
	bool hasText();
	void resetTextPos();
	void textNextLine();
	void setTextStart(int x, int y);
	void addChar(char key);
	void removeLastChar();
    std::vector<char> getText();
	void setUp(const char title[], int startX, int startY);
	void save();
private:
	int id;
	int width;
	int height;
	int textX, textY, defaultX, defaultY;
	int leftWorldX;
	int rightWorldX;
	int topWorldY;
	int lowerWorldY;
    const int line_height = 25;
	const int line_width = 60;
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
	this->textY = this->topWorldY - this->line_height;
	this->defaultX = this->textX;
	this->defaultY = this->textY;
	this->font = GLUT_BITMAP_8_BY_13;
}

void Window::setUp(const char title[], int startX, int startY) {
	glutInitWindowSize(width, height);				// specify a window size
	glutInitWindowPosition(startX, startY);  // specify a window position
	glutCreateWindow(title);
	glClearColor(1, 1, 1, 0);			// specify a background color: white 
	gluOrtho2D(leftWorldX, rightWorldX, lowerWorldY, topWorldY);
	glRasterPos2i(leftWorldX, rightWorldX);
}

void Window::save() {
	std::ofstream fout;
	std::string filename = "typed.txt";
#ifdef _WIN32
	filename = "C:\\TEMP\\typed.txt";
#endif
	fout.open(filename);
	if (fout.is_open()) {
		int chars = 0;
		for (int i = 0; i < displayedText.size(); i++) {
			if (chars == line_width) {
				chars = 0;
				i--;
				fout << '\n';
			}
			else {
				if (displayedText.at(i) == ENTER)
					chars = 0;
				else {
					chars++;
				}
				fout << displayedText.at(i);
			}
		}
		fout.close();
	}
	else {
		std::cout << "Failed to open C:\\TEMP\\typed.txt" << std::endl;
	}
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
int Window::getLineWidth() { return this->line_width; }
void Window::resetTextPos(){
    this->textX = this->defaultX;
	this->textY = this->defaultY;
}
void Window::textNextLine(){
    this->textX = this->defaultX;
    this->textY = this->textY - this->line_height;
}
void Window::setTextStart(int x, int y){
    this->defaultX = x - this->rightWorldX;
    this->defaultY = this->topWorldY - y;
    this->resetTextPos();
}
bool Window::hasText(){ return !this->displayedText.empty(); }
void Window::setWindowId(int id) { this->id = id; }
std::vector<char> Window::getText() { return displayedText; }
void Window::addChar(char key) { displayedText.push_back(key); }
void Window::removeLastChar() { displayedText.pop_back(); }

// Window dimentions
const int editWindowX = 680;
const int editWindowY = 800;
const int infoWindowX = 500;
const int infoWindowY = 400;
Window editorWindow(editWindowX, editWindowY);
Window infoWindow(infoWindowX, infoWindowY);

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
        if (chars == editorWindow.getLineWidth()){
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
void editorDisplayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT);	// draw the background
    if (editorWindow.hasText())
        display_text();
    glFlush(); // flush out the buffer contents
}

void editorMenuCallback(int entryId) {
	switch (entryId) {
	case SAVE:
		editorWindow.save();
		break;
	case EXIT:
		exit(0);
	}
}
void colorMenuCallback(int entryId) {
	switch (entryId) {
	case RED:
		editorWindow.setColor(1, 0, 0);
		break;
	case GREEN:
		editorWindow.setColor(0, 1, 0);
		break;
	case BLUE:
		editorWindow.setColor(0, 0, 1);
		break;
	default:
		editorWindow.setColor(0, 0, 0);
	}
	editorDisplayCallback();
}

void fontMenuCallback(int entryId) {
	switch (entryId) {
	case TIMES_NEW_ROMAN:
		editorWindow.setFont(GLUT_BITMAP_TIMES_ROMAN_24);
		break;
	case HELVETICA:
		editorWindow.setFont(GLUT_BITMAP_HELVETICA_18);
		break;
	case BITMAP:
		editorWindow.setFont(GLUT_BITMAP_8_BY_13);
		break;
	}
	editorDisplayCallback();
}

void createEditorMenus() {
	int colorMenuId = glutCreateMenu(colorMenuCallback);
	glutAddMenuEntry("Red", RED);
	glutAddMenuEntry("Green", GREEN);
	glutAddMenuEntry("Blue", BLUE);
	int fontMenuId = glutCreateMenu(fontMenuCallback);
	glutAddMenuEntry("Times New Roman", TIMES_NEW_ROMAN);
	glutAddMenuEntry("HELVETICA", HELVETICA);
	glutAddMenuEntry("Bitmap 8 by 13", BITMAP);
	glutCreateMenu(editorMenuCallback);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAddSubMenu("Colors", colorMenuId);
	glutAddSubMenu("Fonts", fontMenuId);
	glutAddMenuEntry("Save Display Text", SAVE);
	glutAddMenuEntry("Exit", EXIT);
}

void infoDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background
	glFlush(); // flush out the buffer contents
}

void infoMenuCallback(int entryId) {
	switch (entryId) {
	case MINIMIZE:
		glutIconifyWindow();
	}
}

void handleKey(unsigned char key, int mouseX, int mouseY){
    if (key == BACKSPACE && editorWindow.hasText())
        editorWindow.removeLastChar();
    else if (key != BACKSPACE)
        editorWindow.addChar(key);
    editorDisplayCallback();
}

void setTextPos(int button, int state, int cursX, int cursY){
    if (button == GLUT_LEFT_BUTTON && !editorWindow.hasText()){
        editorWindow.setTextStart(cursX, cursY);
    }
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
	infoWindow.setUp("Info Window", 1000, 100);
	glutDisplayFunc(infoDisplayCallback);
	glutCreateMenu(infoMenuCallback);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAddMenuEntry("Minimize", MINIMIZE);
	editorWindow.setUp("Editor Window", 100, 100);
    glutDisplayFunc(editorDisplayCallback);		// register a callback
	createEditorMenus();
	glutKeyboardFunc(handleKey);
	glutMouseFunc(setTextPos);
	


    glutMainLoop();							// get into an infinite loop
}
