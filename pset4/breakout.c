//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// Define blocks + paddle height and width in pixels.
#define BLOCK_HEIGHT 10
#define BLOCK_WIDTH 38

// Define oval width and height.
#define OVAL_WIDTH 20
#define OVAL_HEIGHT 20

// Define paddle's initial coords.
#define PAD_INIT_HEIGHT 560
#define PAD_INIT_WIDTH 175

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    //Velocity of the ball.
    /*
    * I don't support the idea for giving random velocity to the ball, instead I will give it constant speed.
    */
    double xVelocity = drand48();
    double yVelocity = 1;
    
    waitForClick();
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {    
        // Catch mouse movements for the paddle.
        GEvent mouseEvent = getNextEvent(MOUSE_EVENT);
        if(mouseEvent != NULL){
            if(getEventType(mouseEvent) == MOUSE_MOVED){
                double x = getX(mouseEvent) - getWidth(paddle) / 2;
                double y = getY(paddle);
                if(x > 0 && x < getWidth(window )- getWidth(paddle)){
                    setLocation(paddle, x, y);
                }
            }
        }
        
        // Ball movements.
        move(ball, xVelocity, yVelocity);
        // Left window border.
        if(getX(ball) + getWidth(ball) >= getWidth(window)){
            xVelocity = -xVelocity;
        }
        // Right window border.
        else if(getX(ball) <= 0){
            xVelocity = -xVelocity;
        }
        // Upper window border.
        else if(getY(ball) <= 0){
            yVelocity = -yVelocity;
        }
        // Down border, special case, when it occurs we decrement lives and reinitialize the ball.
        else if(getY(ball) + getHeight(ball) > getHeight(window)){
            removeGWindow(window, ball);
            lives--;
            ball = initBall(window);
            waitForClick();
        }
        
        // Detect collisions.
        GObject colObject = detectCollision(window, ball);
        if(colObject != NULL){
            if(colObject == paddle){
                yVelocity = -yVelocity;
            }
            else if(strcmp(getType(colObject), "GRect") == 0){
                yVelocity = -yVelocity;
                removeGWindow(window, colObject);
                points++;
                bricks--;
                updateScoreboard(window, label, points);
            }
        }
        
        
        pause(5);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int upperSpacer = 40;
    int rows, cols;
    int spacer = 2;
    
    for(rows = 0;rows < ROWS; rows++){
        
        string color;
        switch(rows){
            case 0:
                color = "BLUE";
                break;
            case 1:
                color = "GREEN";
                break;
            case 2:
                color = "YELLOW";
                break;
            case 3:
                color = "ORANGE";
                break;
            case 4:
                color = "RED";
                break;
            default:
                color = NULL;
                break;
        }
        for(cols = 0;cols < COLS; cols++){
            int yPosition = cols * (BLOCK_WIDTH + spacer);
            int xPosition = upperSpacer + (rows * (BLOCK_HEIGHT + spacer));
            GRect brick = newGRect(yPosition, xPosition, BLOCK_WIDTH, BLOCK_HEIGHT);
            
            setFilled(brick, true);
            setColor(brick, color);
            add(window, brick);
    }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    int x, y;
    x = (getWidth(window) / 2) - (OVAL_WIDTH / 2);
    y = (getHeight(window) / 2) - (OVAL_HEIGHT / 2);
    GOval ball = newGOval(x, y, OVAL_WIDTH, OVAL_HEIGHT);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(PAD_INIT_WIDTH, PAD_INIT_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel scoreboard = newGLabel("0");
    setFont(scoreboard, "SansSerif-36");
    int x, y;
    x = (getWidth(window) - getWidth(scoreboard)) / 2;
    y = ((getHeight(window) - getHeight(scoreboard)) / 2) - 30; // Just to pull it a bit up from the ball.
    setColor(scoreboard, "GREEN");
    setLocation(scoreboard, x, y);
    add(window, scoreboard);
    
    return scoreboard;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
