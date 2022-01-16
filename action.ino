void checkButtons(){
  byte direction_past = direction;
  byte direction_new = (PIND & BUTTON_MASK) >> 2;
  if(direction_new != ~direction_past) direction = direction_new;
}

void NewGame(){
  score = 0;
  direction = 1;
  length = START_LENGTH;
  snake = calloc(length, step);
  Position *p = snake;
  int i = 0;
  
  for(; p < snake + length * step; p += step){
    p->x = START_X - A * i;
    p->y = START_Y;
    i++;
  }
  
  UpdateApple();
  DrawSnake();
  DrawApple();
}

void Move(){
  int offset_x = 0;
  int offset_y = 0;
  
  switch(direction){
    case UP:
      offset_y = -A;
      break;
    case DOWN:
      offset_y = A;
      break;
    case LEFT:
      offset_x = -A;
      break;
    case RIGHT:
      offset_x = A;
      break;
    default:
      break;
  }
  
  Position *p = snake;
  Position buffer[length];
  for(int i = 0; i < length; i++){
    buffer[i] = *(p + i * step);
  }
  
  snake->x += offset_x;
  snake->y += offset_y;
  
  p = snake;
  for(int i = 1; i < length; i++){
    *(p + i * step) = buffer[i - 1];
  }
  
  CheckImpaction();
  DrawSnake();
  free(&buffer);

  Serial.print(snake->y);
  Serial.print(" ");
  Serial.print((snake + 1 * step)->y);
  Serial.print(" ");
  Serial.println((snake + 2 * step)->y);
}

void CheckImpaction(){
  if(snake->x >= BOUND_RIGHT - A || snake->x <= BOUND_LEFT || snake->y <= BOUND_UP || snake->y >= BOUND_DOWN - A){
    GameOver();
  }
  for(Position *p = snake; p < snake + length * step; p += step){
    if(snake->x == p->x && snake->y == p->y) GameOver();
  }
  if(snake->x == apple->x && snake->y == apple->y){
    Eat();
  }
}

void Eat(){
  score++;
  length++;

  Position *snake_new = calloc(length, step);
  *snake_new = *apple;
  for(Position *p = snake; p < snake + length * step; p += step){
    *(snake_new + step) = *p;
  }
  snake = snake_new;
  
  UpdateApple();
}

void UpdateApple(){
  apple->x = BOUND_MARGIN + random(WIDTH - A - 2 * BOUND_MARGIN);
  apple->y = BOUND_MARGIN + random(BOUND_HEIGHT - A - 2 * BOUND_MARGIN);
}

void GameOver(){
  free(snake);
  NewGame();
}
