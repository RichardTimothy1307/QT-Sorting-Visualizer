#include "main.h"
using namespace std;
void delay(){   //this is to slower the visualization
    QTime dieTime=QTime::currentTime().addMSecs(SLEEP_ms);
    while(QTime::currentTime()<dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }

}

//creating or updating random array each time

void updateArray(int data[],int length){
    for(int i=0;i<length;i++){
        int value=MIN+(rand()%(MAX-MIN+1)); //thru mod we keep it in our range
        data[i]=value;
    }
}
//we call whenever operation is made on the number

void highlightButton(QPushButton * button){
    button->setStyleSheet("\
        background-color:yellow;\
        color:blue; \
        font-weight:bold; \
                          ");
}
//after operation we unhighlight it

void unhighlightButton(QPushButton * button){
    button->setStyleSheet("\
         font-weight:bold; \
        ");
}

void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

//we will pass the values to button to switch

void setButtonValue(QPushButton *button,int data){
   string name=to_string(data);
   button->setText(name.c_str());
}
         //BUBBLE SORT//
void bubbleSort(QPushButton *button[],int data[],int length){
    for(int it=0;it<length-1;it++){
        int swapped=0;
        for(int i=0;i<length-1;i++){
            highlightButton(button[i]);    //highlighting the 2 buttons we are dealing with
            highlightButton(button[i+1]);
            delay();//creating a bit of a delay
            if(data[i]>data[i+1]){
                swap(&data[i],&data[i+1]);
                setButtonValue(button[i],data[i]);         //setting the new value
                 setButtonValue(button[i+1],data[i+1]);
                 delay();
                 swapped=1;

            }
            unhighlightButton(button[i]);    //unhighlighting after our operation
            unhighlightButton(button[i+1]);
        }
        //if there is no swapping it is already sorted
        if(swapped==0){
            break;
        }
    }
}

            //SELECTION SORT//
void selectionSort(QPushButton *button[],int data[],int length){
    for(int step=0;step<length-1;step++){
        int min_idx=step;
        for(int i=step+1;i<length;i++){
            highlightButton(button[i]);
            highlightButton(button[step]);
            delay();

            if(data[i]<data[min_idx]){
                min_idx=i;
            }
            unhighlightButton(button[step]);
            unhighlightButton(button[i]);
        }
        highlightButton(button[min_idx]);   //the two values from sorted and unsorted which we are going to swap
        highlightButton(button[step]);
        //put min at the correct position
        swap(&data[min_idx],&data[step]);
        setButtonValue(button[min_idx],data[min_idx]);
        setButtonValue(button[step],data[step]);
        delay();
        unhighlightButton(button[min_idx]);
        unhighlightButton(button[step]);

    }
}

       //Insertion Sort
void insertionSort(QPushButton *button[],int data[],int length)
{
    int i, key, j;
    for (i = 1; i < length; i++)
    {
        key = data[i];
        j = i - 1;
        highlightButton(button[i]);
        delay();

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && data[j] > key)
        {
            highlightButton(button[j]);
            delay();

             swap(&data[j],&data[j+1]);
             setButtonValue(button[j+1],data[j+1]);
             setButtonValue(button[j],data[j]);
             delay();

            unhighlightButton(button[j]);

            j = j - 1;


        }

        data[j + 1] = key;
        setButtonValue(button[j+1],data[j+1]);
        setButtonValue(button[i],data[i]);
        delay();

        unhighlightButton(button[i]);





    }
}







void updateButton(QPushButton *button[],int data[],int length){
    string name;
    for(int i=0;i<length;i++){
        name=to_string(data[i]);
        button[i]->setText(name.c_str());
    }
}



int main(int argc,char **argv){
    //size of array
    const int length=10;
    int data[length];

    //for tracking sorting
    int sorting =false;

    QApplication app(argc,argv);

    //creating the window
    QWidget *window=new QWidget;
    window->resize(200,100);
    window->setWindowTitle("Sorting Algorithms Visualizer");
    //creating grid layout inside the window
    QGridLayout *layout=new QGridLayout(window);
    QPushButton *button[length];
    updateArray(data,length);
    for(int i=0;i<length;i++){
        string name=to_string(data[i]);  //returns c style string
         button[i] = new QPushButton(name.c_str());
        button[i]->setStyleSheet("\
            font-weight:bold; \
                                 ");

         layout->addWidget(button[i],0,i,1,1);

    }
    //now creating the options

    QRadioButton *radioBubble=new QRadioButton(QObject::tr("BUBBLE SORT"));
    QRadioButton *radioSelection=new QRadioButton(QObject::tr("SELECTION SORT"));
     QRadioButton *radioInsertion=new QRadioButton(QObject::tr("INSERTION SORT"));
    // radioBubble->setChecked(true);
    layout->addWidget(radioBubble,3,0,1,1);
    layout->addWidget(radioSelection,3,1,1,1);
     layout->addWidget(radioInsertion,3,2,1,1);

    //reset button
    QPushButton *resetButton =new QPushButton("Reset");
    resetButton->setStyleSheet("\
    color:white;\
    font-weight:bold;\
                               ");

    layout->addWidget(resetButton, 3, 8, 1 , 1);

    //sort button
    QPushButton *sortbutton = new QPushButton("Sort");
    sortbutton->setStyleSheet("\
        color:white;\
        font-weight:bold;\
                              ");
    layout->addWidget(sortbutton,3,9,1,1);

    QObject::connect(resetButton,&QPushButton::clicked,[&](){
        //when reset button is pressed we generate another random set of array
        //and update it in GUI
        updateArray(data,length);
        updateButton(button,data,length);
        sortbutton->setText("SORT");
    });

    //when sort button is pressed

    QObject::connect(sortbutton,&QPushButton::clicked,[&](){
        if(sorting==true){
            return;
        }
        sorting=true;
        resetButton->setVisible(false);
        sortbutton->setText("Sorting...");
        //If bubble sort radio button is clicked do bubble sort
        //else we will do selection sort

        if(radioBubble->isChecked()){
                    bubbleSort(button,data,length);
                    resetButton->setVisible(true);
                    sortbutton->setText("SORT");
                    sorting=false;

        }
        else if(radioSelection->isChecked()){
                    selectionSort(button,data,length);
                    resetButton->setVisible(true);
                    sortbutton->setText("SORT");
                    sorting=false;

        }
        else{
            insertionSort(button,data,length);
            resetButton->setVisible(true);
            sortbutton->setText("SORT");
            sorting=false;

        }




    });
    window->show();
    return app.exec();
}






