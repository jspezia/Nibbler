#include "Glfw.class.hpp"
#include <math.h>
#include <list>

int g_keycode = 0;

Glfw::Glfw(int x, int y) : _x(x), _y(y)
{
    this->_squareSize = (int) fmin(MAX_WIDTH / x, MAX_HEIGHT / y);

    this->_winWidth = this->_squareSize * x;
    this->_winHeight = this->_squareSize * y;
}

Glfw::~Glfw(void)
{
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

void            Glfw::init(void)
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

void            Glfw::close(void)
{
    if (this->_win)
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
    reset_viewport(this->_win);
    g_keycode = 0;

    glMatrixMode(GL_MODELVIEW);

    // Render
    this->_drawGrid();
    this->_drawBonus(map->getBonus());
    this->_drawApple(map->getApple());
    this->_drawObstacles(map->getObstacles());
    this->_drawSnake(map->getSnake());
    this->_drawScore(map->getScore());

    glfwSwapBuffers(this->_win);
    glfwPollEvents();
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

void            Glfw::_drawObstacles(std::list<GameEntity *> obst)
{
    int   x;
    int   y;

    glColor3ub(BROWN);
    for (std::list<GameEntity *>::iterator it = obst.begin(); it != obst.end(); it++)
    {
        x = (*it)->getX() * this->_squareSize;
        y = (*it)->getY() * this->_squareSize;
        glRecti(x, y, x + this->_squareSize, y + this->_squareSize);
    }
}

void            Glfw::_drawBonus(GameEntity * bonus)
{
    int   x;
    int   y;
    int   padding = 2;

    glColor3ub(CYAN);
    x = bonus->getX() * this->_squareSize;
    y = bonus->getY() * this->_squareSize;
    glRecti(x + padding, y + padding, x + this->_squareSize - padding, y + this->_squareSize - padding);
}

void            Glfw::_drawApple(std::list<GameEntity *> apple)
{
    int   x;
    int   y;
    int   padding = 2;

    glColor3ub(RED);
    for (std::list<GameEntity *>::iterator it = apple.begin(); it != apple.end(); it++)
    {
        x = (*it)->getX() * this->_squareSize;
        y = (*it)->getY() * this->_squareSize;
        glRecti(x + padding, y + padding, x + this->_squareSize - padding, y + this->_squareSize - padding);
    }
}


void            draw_text(float x, float y, std::string str, void *font)
{
    int     len;
    int     i;

    glRasterPos2f(x, y);
    len = str.length();
    i = 0;
    while (i < len)
    {
        glutBitmapCharacter(font, str[i]);
        i++;
    }
}

void            Glfw::_drawScore(int score)
{
    std::string     score_str;

    score_str = "SCORE: " + std::to_string(score);
    glColor3ub(WHITE);
    draw_text(15, 20, score_str, TEXT_FONT);
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
    // printf("getInput %d\n", g_keycode);
    switch (g_keycode) {
        case GLFW_KEY_UP:       return KeyUp;       break;
        case GLFW_KEY_DOWN:     return KeyDown;     break;
        case GLFW_KEY_RIGHT:    return KeyRight;    break;
        case GLFW_KEY_LEFT:     return KeyLeft;     break;
        case GLFW_KEY_ESCAPE:   return KeyEscape;   break;
        case GLFW_KEY_SPACE:    return KeySpace;    break;
        case GLFW_KEY_1:        return KeyNum1;     break;
        case GLFW_KEY_2:        return KeyNum2;     break;
        case GLFW_KEY_3:        return KeyNum3;     break;
        default:                return 0;
    }
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
