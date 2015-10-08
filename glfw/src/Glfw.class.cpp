#include "Glfw.class.hpp"
// #include <iostream>
#include <math.h>
// #include <list>
// #include <cstdlib>

int g_keycode = 0;

Glfw::Glfw(int x, int y) : _x(x), _y(y)
{
    this->_squareSize = (int) fmin(MAX_WIDTH / x, MAX_HEIGHT / y);

    this->_winWidth = this->_squareSize * x;
    this->_winHeight = this->_squareSize * y;

    this->_init();
}

Glfw::~Glfw(void) {}

static void     error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void     key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (action == GLFW_PRESS)
        g_keycode = key; // global use
    else
        g_keycode = 0;
}

void            Glfw::_init(void)
{
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(this->_winWidth, this->_winHeight, "Snake", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);

    this->_win = window;
}

void            Glfw::_destroy(void)
{
    glfwDestroyWindow(this->_win);
    glfwTerminate();
}

/* DRAW CALLS */
void            reset_viewport(GLFWwindow *window)
{
    float   ratio;
    int     width;
    int     height;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float)height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
}

void            Glfw::draw(Map *map)
{
    if (!glfwWindowShouldClose(this->_win))
    {
        reset_viewport(this->_win);

        glMatrixMode(GL_MODELVIEW);

        // Render
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();

        glfwSwapBuffers(this->_win);
        glfwPollEvents();
    }
}

// void            Glfw::_drawSnake(Snake *snake)
// {

// //head
//     sf::CircleShape head(this->_squareSize / 2);
//     head.setFillColor(sf::Color(BLACK));

//     head.setPosition(snake->_head->getX() * this->_squareSize + 1, snake->_head->getY() * this->_squareSize + 1);
//     this->_win->draw(head);
// //eyes
//     sf::CircleShape eyes((this->_squareSize / 2 - 1) / 4);
//     eyes.setFillColor(sf::Color(WHITE));

//     eyes.setPosition(snake->_head->getX() * this->_squareSize + this->_squareSize * 1 / 4, snake->_head->getY() * this->_squareSize + 1 + this->_squareSize * 1 / 4);
//     this->_win->draw(eyes);
//     eyes.setPosition(snake->_head->getX() * this->_squareSize + this->_squareSize * 3 / 4 - 1, snake->_head->getY() * this->_squareSize + 1 + this->_squareSize * 1 / 4);
//     this->_win->draw(eyes);

//     sf::CircleShape body(this->_squareSize / 2);
//     body.setFillColor(sf::Color(BODY_COLOR));

//     for (std::list<GameEntity *>::iterator it = snake->_body.begin(); it != snake->_body.end(); it++)
//     {
//         body.setPosition((*it)->getX() * this->_squareSize + 1, (*it)->getY() * this->_squareSize + 1);
//         this->_win->draw(body);
//     }
// }


// void            Glfw::_drawApple(std::list<GameEntity *>        apple)
// {
//     //draw 1 circle && 2 lozenge
//     sf::CircleShape shape(this->_squareSize / 2, 8);
//     sf::CircleShape leaf(this->_squareSize / 8, 4);
//     sf::CircleShape leaf2(this->_squareSize / 6, 4);
//     shape.setFillColor(sf::Color(RED));
//     leaf.setFillColor(sf::Color(GREEN));
//     leaf2.setFillColor(sf::Color(GREEN));

//     for (std::list<GameEntity *>::iterator it = apple.begin(); it != apple.end(); it++)
//     {
//         shape.setPosition((*it)->getX() * this->_squareSize + 1, (*it)->getY() * this->_squareSize + 1);
//         this->_win->draw(shape);
//         leaf.setPosition((*it)->getX() * this->_squareSize + 1 + this->_squareSize / 4, (*it)->getY() * this->_squareSize + 1);
//         this->_win->draw(leaf);
//         leaf2.setPosition((*it)->getX() * this->_squareSize + 1 + this->_squareSize / 2, (*it)->getY() * this->_squareSize + 1);
//         this->_win->draw(leaf2);
//     }
// }

// void            Glfw::_drawGrid()
// {
//     int margin = 0; //px
//     int size = this->_squareSize - 2 * margin;
//     sf::RectangleShape  rect(sf::Vector2f(size * 4, size * 4));

//     sf::Texture texture;
//     if (!texture.loadFromFile("sfml/texture/grass.png"))
//         rect.setFillColor(sf::Color(NICE_GREEN));
//     else
//     {
//         rect.setTexture(&texture);
//         rect.setTextureRect(sf::IntRect(10, 10, 100, 100));
//     }
//     for (int y = 0; y < this->_y / 4 + 1; y++) {
//         for (int x = 0; x < this->_x / 4 + 1; x++) {
//             rect.setPosition(margin + x * 4 * this->_squareSize, margin + y * 4 * this->_squareSize);
//             this->_win->draw(rect);
//         }
//     }
// }

/* INPUT EVENTS */
int             Glfw::getInput(void)
{
    return g_keycode;
}


extern "C" IGraphic *       init(int width, int height)
{
    return new Glfw(width, height);
}

extern "C" void             destroy(IGraphic * p)
{
    delete p;
}
