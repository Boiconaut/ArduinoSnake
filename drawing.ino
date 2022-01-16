void UpdateBound(){
  display.drawRect(BOUND_MARGIN, BOUND_MARGIN, BOUND_WIDTH, BOUND_HEIGHT, 1);
  display.setTextSize(0);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(SCORE_X, SCORE_Y);
  display.print("Score: ");
  display.print(score);
}

void DrawSnake(){
  Position *p = snake;

  for(; p < snake + length * step; p += step){
    display.fillRect(p->x, p->y, A, A, 1);
  }
}

void DrawApple(){
  display.fillRect(apple->x, apple->y, A, A, 1);
}
