#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
/*STRUCT para llevar el rastro de la posicion (x,y) en la pantalla. */
typedef struct _Bullet{
    int x;
    int y;
}Bullet;
/*STRUCT para llevar rastro de la direccion del movimiento
    En este caso _Bullet podria estar compuesto con un _Direction
    si se necesitara simular multiples 'Balas' en el tablero.*/
typedef struct _Direction{
    int x;
    int y;
}Direction;

int main(){
    /*Inicializamos la instancia de ncurses*/
    initscr();
    nodelay(stdscr, TRUE);
    cbreak();
    curs_set(FALSE);

    int hght = 0;
    int wdt = 0;
    /*Inicializamos una bala y su rastreador de direccion*/
    Bullet b = {1,1};
    Direction dir = {1,1};

    /*Llamamos a getmax para crear la pantalla y delimitar las paredes.*/
    getmaxyx(stdscr, hght, wdt);

    while(getch() == ERR){ /*Ejecutar hasta que se presione una tecla*/
        /*reimpresion*/
        mvprintw(b.y,b.x,"o");
        b.y += dir.y;
        b.x += dir.x;
        /*Limites horizontales*/
        if(b.x == wdt-1 || b.x == 1){
            dir.x *= -1;
            b.x += dir.x;
        }
        /*Limites verticales*/
        if(b.y == hght-1 || b.y == 1){
            dir.y *= -1;
            b.y += dir.y;
        }
        refresh();
        usleep(75000); /*Pausa para poder obserar el movimiento*/
        clear();
    }
}