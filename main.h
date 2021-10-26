#ifndef MAIN_H
#define MAIN_H



#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QTime>
#include <QTextEdit>
#include <QThread>
#include <QRadioButton>

//numbers generated will be between MAX and MIN
#define MIN   0
#define MAX 99
#define SLEEP_ms 500

/* create dealy in the qt */
void delay();
/* filling array with random numbers */
void updateArray(int data[], int length);
/* set the background of button to yellow to attract view */
void highlightButton(QPushButton * button);
/* set the button to normal color */
void unhighlightButton(QPushButton * button);
/* swap value of a and b */
void swap(int *a, int *b);
/* set button */
void setButtonValue( QPushButton *button, int data);
/* run selection sort algorithm and update ui */
void bubbleSort(QPushButton *button[], int data[], int length);
/* run selection sort algorithm and update ui */
void selectionSort(QPushButton *button[], int data[], int length);
/* run selection sort algorithm and update ui */
void insertionSort(QPushButton *button[],int data[],int length);


/* set button value corresponding to position data equivalent to zip in python */
void updateButton(QPushButton *button[],  int data[], int length);



#endif // MAIN_H
