#define OLED_RESET -1
#define WIDTH 128
#define HEIGHT 64
#define BOUND_WIDTH 124
#define BOUND_HEIGHT 50
#define BOUND_MARGIN 2
#define BOUND_MARGIN_DOWN 10
#define BOUND_LEFT 2
#define BOUND_RIGHT 125
#define BOUND_UP 2
#define BOUND_DOWN 54
#define MAX_WIDTH 31
#define MAX_HEIGHT 13
#define SCORE_X 4
#define SCORE_Y 56

#define A 4
#define START_X 32
#define START_Y 32
#define START_LENGTH 3

#define BUTTON_MASK B00001100
#define UP 0
#define DOWN 4
#define RIGHT 1
#define LEFT 3

Adafruit_SH1106G display(128, 64, &Wire, OLED_RESET);

unsigned long timer = 0;
int length;
int score;
byte direction;
int step;
byte speed;

struct Position{
  int x;
  int y;
};

Position *snake;
Position *apple;
Position snake_buffer[MAX_WIDTH * MAX_HEIGHT];
