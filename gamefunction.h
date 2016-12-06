#ifndef _GAMEFUNCTION_H_
#define _GAMEFUNCTION_H_

typedef struct undo {
	int pos_x;
	int pos_y;
	int top;
}undostack;

void init(undostack *s);
int is_empty(undostack *s);
int is_full(undostack *s);
void push(undostack *s, int item);
void push(undostack *s, int item);
int pop(undostack *s);
int pop1(undostack *s);
void Draw();
void Move(int _x, int _y);
void MoveCursor(int _x, int _y);
void Popup(char _message[]);
void Level_Popup(char _message[]);
void LoadData(char _fileName[]);

#endif //_GAMEFUNCTION_H_