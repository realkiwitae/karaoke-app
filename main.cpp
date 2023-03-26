#include <GL/glut.h>

#include <iostream>
#include <string.h>

// Window dimensions
const int WIDTH = 640;
const int HEIGHT = 480;

// GLUT window ID
int windowID;

char inputText[256] = "";

// Display function
void display()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // // Draw the button
    // glColor3f(1.0f, 1.0f, 1.0f);
    // glBegin(GL_QUADS);
    // glVertex2f(-0.5f, -0.5f);
    // glVertex2f(-0.5f, 0.5f);
    // glVertex2f(0.5f, 0.5f);
    // glVertex2f(0.5f, -0.5f);
    // glEnd();

    // // Draw the text label
    // glMatrixMode(GL_PROJECTION);
    // glPushMatrix();
    // glLoadIdentity();
    // gluOrtho2D(0, WIDTH, 0, HEIGHT);
    // glMatrixMode(GL_MODELVIEW);
    // glPushMatrix();
    // glLoadIdentity();

    // // Set the text color and position
    // glColor3f(0.0f, 0.0f, 0.0f);
    // glRasterPos2f(WIDTH / 2 - 40, HEIGHT / 2 + 5);

    // // Draw the text
    // const char* label = "Click me!";
    // for (int i = 0; i < strlen(label); i++)
    // {
    //     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[i]);
    // }

    // Draw the input field
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Draw the input field border
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(WIDTH / 2 - 100, HEIGHT / 2 - 25);
    glVertex2f(WIDTH / 2 + 100, HEIGHT / 2 - 25);
    glVertex2f(WIDTH / 2 + 100, HEIGHT / 2 + 25);
    glVertex2f(WIDTH / 2 - 100, HEIGHT / 2 + 25);
    glEnd();

    // Draw the input text
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(WIDTH / 2 - 90, HEIGHT / 2 - 10);
    for (int i = 0; i < strlen(inputText); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, inputText[i]);
    }

    // Restore the modelview and projection matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    // Swap buffers
    glutSwapBuffers();
}
// Mouse function
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Convert mouse coordinates to normalized device coordinates
        float norm_x = (2.0f * x) / WIDTH - 1.0f;
        float norm_y = 1.0f - (2.0f * y) / HEIGHT;

        // Check if mouse is inside the square
        if (norm_x >= -0.5f && norm_x <= 0.5f && norm_y >= -0.5f && norm_y <= 0.5f)
        {
            std::cout << "Hello, World!" << std::endl;
        }
    }
}


void keyboard(unsigned char key, int x, int y)
{
    // Check if the key is a printable character
    if (key >= 32 && key <= 126 && strlen(inputText) < sizeof(inputText) - 1)
    {
        // Append the key to the input text
        inputText[strlen(inputText)] = key;
        inputText[strlen(inputText)] = '\0';
    }
    // Check if the key is the backspace character
    else if (key == 8 && strlen(inputText) > 0)
    {
        // Remove the last character from the input text
        inputText[strlen(inputText) - 1] = '\0';
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);

    // Set up the window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    windowID = glutCreateWindow("Hello, World!");

    // Register GLUT callbacks
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    // Start the main loop
    glutMainLoop();

    return 0;
}