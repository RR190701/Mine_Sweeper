#include<bits/stdc++.h>
#include<windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<iostream>

class Painter{

public:
    enum {
    cellWidth = 15,
    cellHeight=15
    };
    void drawCloseField(int x,int y);
    void drawOpenField(int x,int y,int mine_count_around);
    void drawFlag(int x,int y);
    void drawMine(int x,int y);

private :

    void drawOpenedField(int x,int y);
    };



    void Painter::drawCloseField(int x,int y){

        glColor3f(0.8f,0.8f,0.8f);
        glBegin(GL_QUADS);
        glVertex2f(x* cellWidth,y* cellHeight);
        glVertex2f((x+1)* cellWidth,y* cellHeight);
        glVertex2f((x+1)* cellWidth,(y+1)* cellHeight);
        glVertex2f(x* cellWidth,(y+1)* cellHeight);

        glEnd();
        glColor3f(1.0f,1.0f,1.0f);
        glBegin(GL_LINES);

        glVertex2f(x* cellWidth,y* cellHeight);
        glVertex2f((x+1)* cellWidth-1,y* cellHeight);
        glVertex2f(x* cellWidth,y* cellHeight);
        glVertex2f(x* cellWidth,(y+1)* cellHeight-1);

        glEnd();
        glColor3f(0.2f,0.02f,0.2f);
        glBegin(GL_LINES);

        glVertex2f((x+1)* cellWidth-1,y* cellHeight);
        glVertex2f((x+1)* cellWidth-1,(y+1)* cellHeight-1);
        glVertex2f((x)* cellWidth,(y+1)* cellHeight-1);
        glVertex2f((x+1)* cellWidth-1,(y+1)* cellHeight-1);

        glEnd();


    }

    void  Painter::drawOpenField(int x,int y,int mine_count_around){

       drawOpenedField(x,y);

        if(mine_count_around>0){

                switch(mine_count_around){

            case 1:
                glColor3f(0.0f,1.0f,0.0f);
                break;

            case 2:
                glColor3f(0.0f,0.0f,1.0f);
                break;
            case 3:
                glColor3f(1.0f,0.0f,0.0f);
                break;
            case 4:
                glColor3f(0.0f,0.7f,0.0f);
                break;
            case 5:
                glColor3f(0.5f,0.4f,0.0f);
                break;
            case 6:
                glColor3f(0.0f,0.8f,0.5f);
                break;
            case 7:
                glColor3f(0.1f,0.1f,0.1f);
                break;
            case 8:
                glColor3f(0.3f,0.3f,0.3f);
                break;


                }


            glRasterPos2f( x* cellWidth+2.5,(y+1)*cellHeight-2);

            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + mine_count_around);
        }

        }



    void  Painter::drawFlag(int x,int y){



     glColor3f(0.8f,0.8f,0.8f);
        glBegin(GL_QUADS);
        glVertex2f(x* cellWidth,y* cellHeight);
        glVertex2f((x+1)* cellWidth,y* cellHeight);
        glVertex2f((x+1)* cellWidth,(y+1)* cellHeight);
        glVertex2f(x* cellWidth,(y+1)* cellHeight);

        glEnd();

        glColor3f(0.0f,0.0f,0.0f);
        glBegin(GL_LINES);
        glVertex2f(x* cellWidth + cellWidth/2, y * cellHeight + 3);
        glVertex2f(x* cellWidth + cellWidth/2,(y+1)* cellHeight-3);
         glVertex2f(x* cellWidth + 5 , (y+1)* cellHeight-3);
        glVertex2f((x+1)* cellWidth - 6 ,(y+1)* cellHeight-3);
        glEnd();

        glColor3f(1.0f,0.0f,0.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(x* cellWidth + cellWidth/2, y * cellHeight+ 3);
        glVertex2f(x* cellWidth + cellWidth/2 - 4,y * cellHeight + 6);
         glVertex2f(x* cellWidth + cellWidth/2, y * cellHeight + 6);
        glEnd();


    }


    void  Painter::drawMine(int x,int y){

         drawOpenedField(x,y);

         glColor3f(0.0f,0.0f,0.0f);
         glBegin(GL_POLYGON);
        for(int i=0;i<5;i++){

             glVertex2f(x* cellWidth + cellWidth/2  + 5 * cos( 2 * 3.1415926 * i/5),
                        y * cellHeight +  cellHeight/2  + 5 * sin( 2 * 3.1415926 * i/5));

        }
        glEnd();
    }

    void Painter::drawOpenedField(int x,int y){

     glColor3f(0.6f,0.6f,0.6f);
        glBegin(GL_QUADS);
        glVertex2f(x* cellWidth,y* cellHeight);
        glVertex2f((x+1)* cellWidth,y* cellHeight);
        glVertex2f((x+1)* cellWidth,(y+1)* cellHeight);
        glVertex2f(x* cellWidth,(y+1)* cellHeight);

        glEnd();
         glColor3f(0.2f,0.02f,0.2f);
        glBegin(GL_LINES);

        glVertex2f((x+1)* cellWidth-1,y* cellHeight);
        glVertex2f((x+1)* cellWidth-1,(y+1)* cellHeight-1);
        glVertex2f((x)* cellWidth,(y+1)* cellHeight-1);
        glVertex2f((x+1)* cellWidth-1,(y+1)* cellHeight-1);

        glEnd();

        }


class Game {

public:

    enum {
        WIDTH=9,
        HEIGHT=9,
        MINES=9
    };
     enum State {

        CLOSED,
        OPEN,
        FLAG

    };
    Game();

    void Draw();
    void open(int x,int y);
    void mark(int x,int y);
    int mineCounter(int x,int y);
    void openUntil(int x,int y);
    void Expose();

    private :

    struct Cell {
    State state;
    bool hasMine;
     };

     Cell field[WIDTH][HEIGHT];

       };

 Game::Game(){

for(int i=0;i<WIDTH;i++){
    for( int j=0;j<HEIGHT;j++){
        field[i][j].state=CLOSED;
        field[i][j].hasMine=false;

    }
}

for(int i=1;i<=MINES;i++){


    int x,y;

    do{
        x=rand()% WIDTH;
        y=rand()%HEIGHT;

    }while(field[x][y].hasMine);

    field[x][y].hasMine=true;
}
}

Painter p;
void Game::Draw (){



    for(int x=0;x<WIDTH;x++){
        for(int y=0;y<HEIGHT; y++){

                switch(field[x][y].state){

                case CLOSED:
                            p.drawCloseField(x,y);
                            break;
                case OPEN:
                    if(!field[x][y].hasMine){



                                         int mine_count= mineCounter(x,y);
                                       p.drawOpenField(x,y,mine_count);
                    }
                    else {
                            p.drawMine(x,y);

                    }


                           break;
                case FLAG:
                           p.drawFlag(x,y);
                           break;

                    }


        } }

}

void Game::openUntil(int x,int y){


 std::cout<<x<<" "<<y;
std::cout<<"\n";

if(field[x][y].hasMine)
    return;

int mine_count= mineCounter(x,y);


    field[x][y].state=OPEN;

    if(mine_count==0){




			if ((x+1) >=0 && (x+1) < WIDTH && y >=0 && y< HEIGHT)
			{
				if (field[x+1][y].hasMine == false)
				openUntil(x+1,y);
			}





    }






}

void Game::Expose(){

    for(int i=0;i<WIDTH;i++){
    for( int j=0;j<HEIGHT;j++){
            if(field[i][j].hasMine)
        field[i][j].state=OPEN;

    }
}
}

int Game:: mineCounter(int x,int y){

      int mine_count=0;

                          for(int yy = y-1;yy<=y+1; yy++){
                            for(int xx= x-1; xx<=x+1; xx++){

                                if((xx == x && yy== y)|| xx<0 || xx >=WIDTH||yy<0 || yy>=HEIGHT)
                                    continue;
                                if(field[xx][yy].hasMine)
                                    mine_count++;
                            }
                          }


                          return mine_count;

}

void Game::open(int x,int y){

if(field[x][y].hasMine){

    Expose();

}
else{

    openUntil(x,y);

}

}

void Game::mark(int x,int y){

switch(field[x][y].state){

case OPEN: break;
case CLOSED:
    field[x][y].state=FLAG;
          break;
case FLAG:
    field[x][y].state=CLOSED;
          break;

}

}





Game game;

void display(){

glClear(GL_COLOR_BUFFER_BIT);

game.Draw();
glutSwapBuffers();

}

void mouse(int button,int state, int x,int y){
    if(state==GLUT_UP){

        switch(button){

    case GLUT_LEFT_BUTTON:
        game.open(x/Painter::cellWidth, y/Painter::cellHeight);
        break;

    case GLUT_RIGHT_BUTTON:
        game.mark(x/Painter::cellWidth, y/Painter::cellHeight);
        break;
        }

        glutPostRedisplay();
    }

}

int main(int argc, char** argv){

  glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

    glutInitWindowSize(Game::HEIGHT*Painter::cellWidth,Game::WIDTH*Painter::cellHeight);
    glutInitWindowPosition(700,300);

    glutCreateWindow("Mine Sweeper");
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Game::HEIGHT*Painter::cellWidth ,Game::WIDTH*Painter::cellHeight ,0,-1.0,1.0);
     glutMouseFunc(mouse);
    glutDisplayFunc(display);
       glutMainLoop();


       return 0;

}
