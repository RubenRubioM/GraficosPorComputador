
/****************************************************************************************************

    CarGL (main.cpp)

    Grado en Ingeniería Multimedia.
    Práctica de Gráficos por Computador.
    OpenGL con Shaders.
  ------------------------------------------------------------------------------------------

    CarsGL (C) 2012-2016 - Juan Antonio Puchol García (puchol@dccia.ua.es)

    Changelog:

    Versión 1.0 (Noviembre 2012)
        - Versión inicial para Code::Blocks 10.05

    Versión 1.1 (Noviembre 2012)
        - Arreglado el bug de selección incorrecta debido al panel inferior de controles

    Versión 1.2 (Octubre 2013 )
        - Adaptación de la librería GLUI a Code::Blocks 12.11 y 13.12

    Versión 1.3 (Octubre 2014 )
        - Adaptación de la librería GLUI a Code::Blocks 13.12

    Versión 2.0 (Octubre 2015 )
        - Adaptación del código empleando Shaders (Modern OpenGL Graphics)

    Versión 2.1 (Septiembre 2016 )
        - Modificación de los scrollbars de las luces para manipular la posisión (compatible con Code::Blocks 16.01)

    NOTA:   Para que esta aplicación compile se necesita tener copiados los
            siguientes ficheros desde la carpeta "Para Copiar":

            glut32.dll  -> C:\Windows\system

            Si es un Windows de 32 bits:
            glew32s.lib -> C:\Program Files\CodeBlocks\MinGW\lib
            glew32.lib  -> C:\Program Files\CodeBlocks\MinGW\lib
            libglui32.a -> C:\Program Files\CodeBlocks\MinGW\lib
            glut32.lib  -> C:\Program Files\CodeBlocks\MinGW\lib

            glui.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL
            glut.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL
            glew.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL

            y la carpeta completa
            glm         -> C:\Program Files\CodeBlocks\MinGW\include

            Si es un Windows de 64 bits:
            glew32s.lib -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glew32.lib  -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            libglui32.a -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glut32.lib  -> C:\Program Files (x86)\CodeBlocks\MinGW\lib

            glui.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glut.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glew.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL

            y la carpeta completa
            glm         -> C:\Program Files (x86)\CodeBlocks\MinGW\include


            ACLARACIÓN:
                Hay varias librerías libglui32.a en la carpeta "otros"
                - Renombrar libglui32.10.05.a a libglui32.a para usar Code::Blocks 10.05
                - Renombrar libglui32.12.11.a a libglui32.a para usar Code::Blocks 12.11
                - Renombrar libglui32.13.12.a a libglui32.a para usar Code::Blocks 13.12 o superior

****************************************************************************************************/

#include "Objects.h"
#include <GL\glui.h>

#define velocidadCoche  0.3
#define rotacionRueda 40

/**************************************** myGlutKeyboard() **********/

void Keyboard(unsigned char Key, int x, int y)
{
    switch(Key)
    {
        case 27:
        case 'q':
            exit(0);
            break;

    }

    glutPostRedisplay();
}

/**************************************** mySpecialKey() *************/

static void SpecialKey(int key, int x, int y)
{
    TPrimitiva *car = escena.GetCar(escena.seleccion);

    switch (key)
    {
        case GLUT_KEY_UP:   // El coche avanza
            car->rr+=rotacionRueda;
            car->tz += velocidadCoche;
            break;
        case GLUT_KEY_DOWN:   // El coche retrocede
            car->rr-=rotacionRueda;
            car->tz -= velocidadCoche;
            break;

    }

    glutPostRedisplay();
}

/***************************************** myGlutMenu() ***********/

void Menu( int value )
{
  Keyboard( value, 0, 0 );
}

void Mouse(int button, int button_state, int x, int y )
{
    gui.Mouse(button, button_state, x, y);
}

void Render()
{
    escena.Render();
}

void Idle()
{
    gui.Idle();
}

void Reshape(int x, int y){
    gui.Reshape(x, y);
}

void Motion(int x, int y){
    gui.Motion(x, y);
}

/**************************************** main() ********************/

int main(int argc, char* argv[])
{
    // Inicializa GLUT and crea la ventana principal
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE );
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( 1400, 800 );

    int main_window = glutCreateWindow( "Practica 1" );

    // Inicializa los valores de OpenGL para esta Aplicación
    escena.InitGL();
    gui.Init(main_window);

    glutDisplayFunc( Render );
    GLUI_Master.set_glutReshapeFunc( Reshape );
    GLUI_Master.set_glutKeyboardFunc( Keyboard );
    GLUI_Master.set_glutSpecialFunc( SpecialKey );
    GLUI_Master.set_glutMouseFunc( Mouse );
    glutMotionFunc( Motion );

    /**** We register the idle callback with GLUI, *not* with GLUT ****/
    GLUI_Master.set_glutIdleFunc( Idle );

    // Crea los objetos
    TPrimitiva *road = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *car1 = new TPrimitiva(1, COCHE_ID);
    TPrimitiva *car2 = new TPrimitiva(2, COCHE_ID);

    TPrimitiva *stop1 = new TPrimitiva(STOP_ID,STOP_ID); //Cuadrado 3

    TPrimitiva *casa1= new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 1
    TPrimitiva *casa2= new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 2
    TPrimitiva *casa3= new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 1
    TPrimitiva *casa4= new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 1
    TPrimitiva *casa5= new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 3
    TPrimitiva *casa6= new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 3
    TPrimitiva *casa7= new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 3
    TPrimitiva *casa8= new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 4

    TPrimitiva *semaforo1 = new TPrimitiva(SEMAFORO_ID,SEMAFORO_ID);

    //Arboles de la primera rotonda
    TPrimitiva *arbol1 = new TPrimitiva(ARBOL_ID,ARBOL_ID);
    TPrimitiva *arbol2 = new TPrimitiva(ARBOL_ID,ARBOL_ID);
    TPrimitiva *arbol3 = new TPrimitiva(ARBOL_ID,ARBOL_ID);
    TPrimitiva *arbol4 = new TPrimitiva(ARBOL_ID,ARBOL_ID);

    TPrimitiva *arbol5 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 2
    TPrimitiva *arbol6 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 2
    TPrimitiva *arbol7 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 3
    TPrimitiva *arbol8 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 4
    TPrimitiva *arbol9 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 4


    TPrimitiva *banco1 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 1
    TPrimitiva *banco2 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 2
    TPrimitiva *banco3 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 2
    TPrimitiva *banco4 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 4
    TPrimitiva *banco5 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 4

    TPrimitiva *papelera1 = new TPrimitiva(PAPELERA_ID,PAPELERA_ID); //cuadrado 1

    TPrimitiva *farola1 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 1
    TPrimitiva *farola2 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 2
    TPrimitiva *farola3 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 2
    TPrimitiva *farola4 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 2
    TPrimitiva *farola5 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 4
    TPrimitiva *farola6 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 4
    TPrimitiva *farola7 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 4

    //Vallas del cuadrado 2
    TPrimitiva *valla1 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla2 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla3 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla4 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla5 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla6 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla7 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla8 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla9 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla10 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla11 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla12 = new TPrimitiva(VALLA_ID,VALLA_ID);

    //Vallas del cuadrado 4
    TPrimitiva *valla13 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla14 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla15 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla16 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla17 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla18= new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla19= new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla20= new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla21= new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla22 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla23 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla24 = new TPrimitiva(VALLA_ID,VALLA_ID);

    /*Asignacion de posiciones y rotaciones

             -z
              |
              |
      -x-------------+x
              |
              |
             +z

    La rotacion para dar la vuelta a algo es en el ry

    */

    /*

        Se supone que las valdosas son 0.5 de altas con respecto a la calle

    */

    //Cochecitos
    car1->tx = +20;
    car1->tz = -8;
    car2->tx = +14;
    car2->tz = -5;
    car2->colores[0][0] = 0.3;
    car2->colores[0][1] = 0.8;
    car2->colores[0][2] = 0.4;
    car2->colores[0][3] = 1.0;

    //Casas
    casa1->tx = +5;
    casa1->tz = -4;
    casa2->tx = +30;
    casa2->tz = -2;
    casa2->ry = 180;
    casa3->tx = -4;
    casa3->tz = +5;
    casa3->ry = 270;
    casa4->tx = -4;
    casa4->tz = -4;
    casa4->ry = 180;
    casa5->tx = +5;
    casa5->tz = +35;
    casa5->ry = 0;
    casa6->tx = -4;
    casa6->tz = +25;
    casa6->ry = 180;
    casa7->tx = -4;
    casa7->tz = +35;
    casa7->ry = 180;
    casa8->tx = +30;
    casa8->tz = +33;
    casa8->ry = 180;


    escena.AddObject(casa1);
    escena.AddObject(casa2);
    escena.AddObject(casa3);
    escena.AddObject(casa4);
    escena.AddObject(casa5);
    escena.AddObject(casa6);
    escena.AddObject(casa7);
    escena.AddObject(casa8);

    //Semaforos
    semaforo1->tx = +31;
    semaforo1->tz = +9;

    escena.AddObject(semaforo1);

    //STOPS
    stop1->tx = +9.4;
    stop1->tz = +27;
    stop1->ry = 270;

    escena.AddObject(stop1);

    //Arboles
    arbol1->tx = +17;
    arbol1->tz = +12;
    arbol1->sy = 1.3;
    arbol1->sx = 1.3;
    arbol1->sz = 1.3;
    arbol2->tx = +13;
    arbol2->tz = +15;
    arbol2->ry = 80;
    arbol2->sy = 0.7;
    arbol2->sx = 0.7;
    arbol2->sz = 0.7;
    arbol3->tx = +17;
    arbol3->tz = +18;
    arbol3->ry = 260;
    arbol4->tx = +21;
    arbol4->tz = +16;
    arbol4->ry = 250;
    arbol5->tx = +38;
    arbol5->tz = +2;
    arbol5->ry = 250;
    arbol6->tx = +34;
    arbol6->tz = +7;
    arbol6->ry = 30;
    arbol6->sy = 0.7;
    arbol6->sx = 0.7;
    arbol6->sz = 0.7;
    arbol7->tx = +4;
    arbol7->tz = +22;
    arbol7->ry = 30;
    arbol7->sy = 0.7;
    arbol7->sx = 0.7;
    arbol7->sz = 0.7;
    arbol8->tx = +38;
    arbol8->tz = +28;
    arbol8->ry = 250;
    arbol9->tx = +37;
    arbol9->tz = +33;
    arbol9->ry = 30;
    arbol9->sy = 0.7;
    arbol9->sx = 0.7;
    arbol9->sz = 0.7;


    escena.AddObject(arbol1);
    escena.AddObject(arbol2);
    escena.AddObject(arbol3);
    escena.AddObject(arbol4);
    escena.AddObject(arbol5);
    escena.AddObject(arbol6);
    escena.AddObject(arbol7);
    escena.AddObject(arbol8);
    escena.AddObject(arbol9);

    //Bancos
    banco1->tx = +5.5;
    banco1->tz = +5.5;
    banco1->ry = 310;
    banco2->tx = +42;
    banco2->tz = 0;
    banco3->tx = +36;
    banco3->tz = +8;
    banco3->ry = 270;
    banco4->tx = +42;
    banco4->tz = +27;
    banco5->tx = +36;
    banco5->tz = +35;
    banco5->ry = 270;

    escena.AddObject(banco1);
    escena.AddObject(banco2);
    escena.AddObject(banco3);
    escena.AddObject(banco4);
    escena.AddObject(banco5);

    //Papeleras
    papelera1->tx = +4.4;
    papelera1->tz = +6.4;
    papelera1->ry = 30;

    escena.AddObject(papelera1);

    //Farolas
    farola1->tx = +3.5;
    farola1->tz = +9;
    farola1->ry = 83;
    farola2->tx = +42.3;
    farola2->tz = +7.5;
    farola2->ry = 83;
    farola3->tx = +38;
    farola3->tz = -5;
    farola3->ry = 0;
    farola4->tx = +29;
    farola4->tz = +5;
    farola4->ry = 30;
    farola5->tx = +42.3;
    farola5->tz = +35;
    farola5->ry = 83;
    farola6->tx = +38;
    farola6->tz = +25;
    farola6->ry = 0;
    farola7->tx = +29;
    farola7->tz = +25;
    farola7->ry = 330;

    escena.AddObject(farola1);
    escena.AddObject(farola2);
    escena.AddObject(farola3);
    escena.AddObject(farola4);
    escena.AddObject(farola5);
    escena.AddObject(farola6);
    escena.AddObject(farola7);

    //Vallas
    //La longitud de una valla es 4
    //Cuadrado 2
    valla1->tx = +35;
    valla1->tz = +9.5;
    valla1->ry = 90;
    valla2->tx = +39;
    valla2->tz = +9.5;
    valla2->ry = 90;
    valla3->tx = +43;
    valla3->tz = +9.5;
    valla3->ry = 90;
    valla4->tx = +43.7;
    valla4->tz = +8.8;
    valla4->ry = 0;
    valla5->tx = +43.7;
    valla5->tz = +4.8;
    valla5->ry = 0;
    valla6->tx = +43.7;
    valla6->tz = +0.7;
    valla6->ry = 0;
    valla7->tx = +43.7;
    valla7->tz = -3,4;
    valla7->ry = 0;
    valla8->tx = +43;
    valla8->tz = -6.4;
    valla8->ry = 90;
    valla9->tx = +39;
    valla9->tz = -6.4;
    valla9->ry = 90;
    valla10->tx = +37;
    valla10->tz = -6.4;
    valla10->ry = 90;
    valla11->tx = +31.8;
    valla11->tz = +8;
    valla11->ry = 0;
    valla12->tx = +31.8;
    valla12->tz = +4.8;
    valla12->ry = 0;

    //Cuadrado 4
    valla13->tx = +35;
    valla13->tz = +21;
    valla13->ry = 90;
    valla14->tx = +39;
    valla14->tz = +21;
    valla14->ry = 90;
    valla15->tx = +43;
    valla15->tz = +21;
    valla15->ry = 90;
    valla16->tx = +43.7;
    valla16->tz = +24.3;
    valla16->ry = 0;
    valla17->tx = +43.7;
    valla17->tz = +28.3;
    valla17->ry = 0;
    valla18->tx = +43.7;
    valla18->tz = +32.5;
    valla18->ry = 0;
    valla19->tx = +43.7;
    valla19->tz = +36;
    valla19->ry = 0;
    valla20->tx = +43;
    valla20->tz = +37;
    valla20->ry = 90;
    valla21->tx = +39;
    valla21->tz = +37;
    valla21->ry = 90;
    valla22->tx = +37;
    valla22->tz = +37;
    valla22->ry = 90;
    valla23->tx = +31.8;
    valla23->tz = +24;
    valla23->ry = 0;
    valla24->tx = +31.8;
    valla24->tz = +28;
    valla24->ry = 0;

    escena.AddObject(valla1);
    escena.AddObject(valla2);
    escena.AddObject(valla3);
    escena.AddObject(valla4);
    escena.AddObject(valla5);
    escena.AddObject(valla6);
    escena.AddObject(valla7);
    escena.AddObject(valla8);
    escena.AddObject(valla9);
    escena.AddObject(valla10);
    escena.AddObject(valla11);
    escena.AddObject(valla12);
    escena.AddObject(valla13);
    escena.AddObject(valla14);
    escena.AddObject(valla15);
    escena.AddObject(valla16);
    escena.AddObject(valla17);
    escena.AddObject(valla18);
    escena.AddObject(valla19);
    escena.AddObject(valla20);
    escena.AddObject(valla21);
    escena.AddObject(valla22);
    escena.AddObject(valla23);
    escena.AddObject(valla24);


    //Resto de objetos
    escena.AddObject(road);
    escena.AddCar(car1);
    escena.AddCar(car2);


    /**** Regular GLUT main loop ****/
    glutMainLoop();

    return EXIT_SUCCESS;
}

