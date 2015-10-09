#include "Glfw.class.hpp"
#include <math.h>
#include <list>

int g_keycode = 0;

Glfw::Glfw(int x, int y) : _x(x), _y(y)
{
    this->_squareSize = (int) fmin(MAX_WIDTH / x, MAX_HEIGHT / y);

    this->_winWidth = this->_squareSize * x;
    this->_winHeight = this->_squareSize * y;

    this->_init();
}

Glfw::~Glfw(void)
{
    this->_destroy();
}

static void     error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void     key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (action == GLFW_PRESS)
        g_keycode = key;
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
    printf("GLFW _destroy call\n");
    glfwDestroyWindow(this->_win);
    glfwTerminate();
}

void            reset_viewport(GLFWwindow *window)
{
    int     width;
    int     height;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
}

void            Glfw::draw(Map *map)
{
    if (!glfwWindowShouldClose(this->_win))
    {
        reset_viewport(this->_win);

        glMatrixMode(GL_MODELVIEW);

        // Render
        this->_drawGrid();
        this->_drawApple(map->getApple());
        this->_drawSnake(map->getSnake());

        glfwSwapBuffers(this->_win);
        glfwPollEvents();
    }
}

void            Glfw::_drawSnake(Snake *snake)
{
    int x;
    int y;

    x = snake->_head->getX() * this->_squareSize;
    y = snake->_head->getY() * this->_squareSize;

    // head
    glColor3ub(GREEN);
    glRecti(x, y, x + this->_squareSize, y + this->_squareSize);

    // body
    glColor3ub(NICE_GREEN);
    for (std::list<GameEntity *>::iterator it = snake->_body.begin(); it != snake->_body.end(); it++)
    {
        x = (*it)->getX() * this->_squareSize;
        y = (*it)->getY() * this->_squareSize;
        glRecti(x, y, x + this->_squareSize, y + this->_squareSize);
    }
}

void            Glfw::_drawApple(std::list<GameEntity *> apple)
{
    int   x;
    int   y;
    int   padding = 3;

    glColor3ub(RED);
    for (std::list<GameEntity *>::iterator it = apple.begin(); it != apple.end(); it++)
    {
        x = (*it)->getX() * this->_squareSize;
        y = (*it)->getY() * this->_squareSize;
        glRecti(x + padding, y + padding, x + this->_squareSize - padding, y + this->_squareSize - padding);
    }
}

void            Glfw::_drawGrid()
{
    int margin = 5;

    glColor3ub(BROWN);
    glRecti(0, 0, this->_winWidth, this->_winHeight);

    glColor3ub(DARK_GREY);
    glRecti(margin, margin, this->_winWidth - margin, this->_winHeight - margin);
}

/* INPUT EVENTS */
int             Glfw::getInput(void)
{
    if (g_keycode == GLFW_KEY_UP)
        return KeyUp;
    if (g_keycode == GLFW_KEY_DOWN)
        return KeyDown;
    if (g_keycode == GLFW_KEY_RIGHT)
        return KeyRight;
    if (g_keycode == GLFW_KEY_LEFT)
        return KeyLeft;
    if (g_keycode == GLFW_KEY_SPACE)
        return KeySpace;
    if (g_keycode == GLFW_KEY_1)
        return KeyNum1;
    if (g_keycode == GLFW_KEY_2)
        return KeyNum2;
    if (g_keycode == GLFW_KEY_3)
        return KeyNum3;

    return 0;
}


extern "C" IGraphic *       init(int width, int height)
{
    return new Glfw(width, height);
}

extern "C" void             destroy(IGraphic * p)
{
    delete p;
}
