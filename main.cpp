#include <QApplication>
#include "mainwindow.h"




int main(int argc, char *argv[])
{
        /*cpucycles between lcd interupts =~ 69905
        Cartridge cart;
        Memory mem;
        LCD lcd;
        resetZ80(&mem,&lcd);
        //read_cart_file("killer_instinct.gb",&cart);
        //read_cart_file("motocross_maniacs.gb",&cart);
        read_cart_file("MEGANIME.GB",&cart);
        //read_cart_file("super_mario_land.gb",&cart);
        parse_cart_Header(EGB,&cart);
        initMemory(&mem,&cart);
        for(int i=0;i<20000;i++){
            execute(69905);
            //renderscreen();
            //sleep
        }

        destroyMemory(&mem);*/
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
