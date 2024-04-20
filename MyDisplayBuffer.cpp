//
// Created by Jeffrey Pfaffmann on 3/2/24.
//

#include "MyDisplayBuffer.h"

MyDisplayBuffer::MyDisplayBuffer() {
    rowpos = 5;
    colpos = 5;
}

MyDisplayBuffer::~MyDisplayBuffer() {
    // nothing to do
}

void MyDisplayBuffer::move_left(void) {
    if(colpos > 1) {
        colpos--;
    }
}

void MyDisplayBuffer::move_right(void) {
    if(colpos < COLMAX - 2) {
        colpos++;
    }
}

void MyDisplayBuffer::move_up(void) {
    if(rowpos > 1) {
        rowpos--;
    }
}

void MyDisplayBuffer::move_down(void) {
    if(rowpos < ROWMAX - 2) {
        rowpos++;
    }
}

void MyDisplayBuffer::load_buffer() {

    // initialized the display buffer
    for (int row = 0; row < ROWMAX; row++) {
        for (int col = 0; col < COLMAX; col++) {
            if     (row == 0)           buffer[row][col] = '-';
            else if(row == ROWMAX - 1)  buffer[row][col] = '-';
            else if(col == 0)           buffer[row][col] = '|';
            else if(col == COLMAX - 1)  buffer[row][col] = '|';
            else                        buffer[row][col] = '.';
        }
    }

    // place the game item
    buffer[rowpos][colpos] = '@';
}

int MyDisplayBuffer::max_rows(void) {
    return ROWMAX;
}

int MyDisplayBuffer::max_cols(void) {
    return COLMAX;
}

char MyDisplayBuffer::buffer_value(int row, int col) {
    return buffer[row][col];
}