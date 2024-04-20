// The same class that was provided as part
// of the curses example.

#ifndef CURSESEX_MYDISPLAYBUFFER_H
#define CURSESEX_MYDISPLAYBUFFER_H

#define ROWMAX 10
#define COLMAX 15

class MyDisplayBuffer {
public:

    MyDisplayBuffer();
    ~MyDisplayBuffer();

    void move_left(void);
    void move_right(void);
    void move_up(void);
    void move_down(void);

    void load_buffer(void);

    int max_rows(void);
    int max_cols(void);

    char buffer_value(int row, int col);

protected:

    char buffer[ROWMAX][COLMAX];

    int colpos;
    int rowpos;
};


#endif //CURSESEX_MYDISPLAYBUFFER_H
