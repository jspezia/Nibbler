#ifndef SFML_CLASS_HPP
# define SFML_CLASS_HPP

# include <glfw3.h>
# include <GLUT/glut.h>
# include "IGraphic.class.hpp"

# define MAX_WIDTH      800
# define MAX_HEIGHT     600

# define TEXT_FONT      GLUT_BITMAP_9_BY_15

/*
**      COLOR
**                          |R|, |G|, |B|
*/
# define RED                255,   0,   0
# define BLUE                 0,   0, 255
# define PINK               217,  36, 105
# define PURPLE             157, 124, 255
# define CYAN               117, 176, 195
# define YELLOW             227, 219, 115
# define ORANGE             228, 126,   0
# define GREEN              177, 227,  54
# define NICE_GREEN           0, 102,  51
# define BODY_COLOR         255, 204,   0
# define BODY_COLOR2        255, 255,   0
# define BROWN              115, 111,  79
# define DARK_GREY           44,  44,  39
# define LIGHT_GREY         142, 143, 137
# define BLACK                0,   0,   0
# define WHITE              255, 255, 255

# include "Snake.class.hpp"
# include "Map.class.hpp"
# include "GameEntity.class.hpp"
# include "KeyValue.hpp"

class Glfw : public IGraphic {

    public:
        Glfw(int width, int height);
        ~Glfw(void);

        void    init(void);
        void    draw(Map *map);
        int     getInput(void);
        void    close(void);

    private:
        Glfw(void);

        void        _drawGrid(void);
        void        _drawSnake(Snake *snake);
        void        _drawBonus(GameEntity *bonus);
        void        _drawApple(std::list<GameEntity *> apple);
        void        _drawObstacles(std::list<GameEntity *> obst);
        void        _drawScore(int score);

        int                 _x;
        int                 _y;

        int                 _squareSize;
        int                 _winWidth;
        int                 _winHeight;

        GLFWwindow *        _win;
};

#endif
