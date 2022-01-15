void checkButtons(){
  byte direction_past = direction;
  byte direction_new = (PIND & BUTTON_MASK) >> 2;
  if(direction_new != ~direction_past) direction = direction_new;
}

void NewGame(){
  score = 0;
  direction = 1;
  length = START_LENGTH;
  snake = calloc(length, sizeof(Position));
  Position *p = snake;
  int i = 0;
  
  for(; p < snake + length * sizeof(Position); p += sizeof(Position)){
    p->x = START_X - A * i;
    p->y = START_Y;
    i++;
  }
  
  apple->x = BOUND_MARGIN + random(WIDTH - A - 2 * BOUND_MARGIN);
  apple->y = BOUND_MARGIN + random(BOUND_HEIGHT - A - 2 * BOUND_MARGIN);

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

  Position *p0 = calloc(length, sizeof(Position));
  for(int i = 0; i < length * sizeof(Position); i += sizeof(Position)){
    *(p0 + i) = *(snake + i);
  }
  snake->x += offset_x;
  snake->y += offset_y;
  /*Position *p = snake + (length - 1) * sizeof(Position);
  *(snake + sizeof(Position)) = p0;
  for(; p > snake; p -= sizeof(Position)){
    *p = *(p - sizeof(Position));
  }*/
  for(int i = 1; i < length * sizeof(Position); i += sizeof(Position)){
    *(snake + i) = *(p0 + i - sizeof(Position));
  }
  
  DrawSnake();
  //CheckImpaction();

  Serial.print(snake->y);
  Serial.print(" ");
  Serial.print((snake + 1 * sizeof(Position))->y);
  Serial.print(" ");
  Serial.println((snake + 2 * sizeof(Position))->y);
}

void CheckImpaction(){
  if(snake->x >= BOUND_RIGHT || snake->x <= BOUND_LEFT || snake->y <= BOUND_UP || snake->y >= BOUND_DOWN){
    GameOver();
  }
  for(Position *p = snake; p < snake + length * sizeof(Position); p += sizeof(Position)){
    if(snake->x == p->x && snake->y == p->y) GameOver();
  }
  if(snake->x == apple->x && snake->y == apple->y){
    Eat();
  }
}

void Eat(){
  score++;
  length++;

  snake = realloc(snake, length * sizeof(Position));
  apple->x = BOUND_MARGIN + random(WIDTH - A - 2 * BOUND_MARGIN);
  apple->y = BOUND_MARGIN + random(BOUND_HEIGHT - A - 2 * BOUND_MARGIN);
}

void GameOver(){
  free(snake);
  NewGame();
}
