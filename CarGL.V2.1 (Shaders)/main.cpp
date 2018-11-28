
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
            if(car->v<1){
              car->v += velocidadCoche;
            }
            break;
        case GLUT_KEY_DOWN:   // El coche retrocede
            if(car->v>-1){
              car->v -= velocidadCoche;
            }
            break;
        case GLUT_KEY_LEFT:   // Giramos ruedas
            if(car->anguloRuedas < 45)
                car->anguloRuedas += 1;
            break;
        case GLUT_KEY_RIGHT:
            if(car->anguloRuedas > -45)
                car->anguloRuedas -= 1;
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

    TPrimitiva *stop1 = new TPrimitiva(STOP_ID,STOP_ID); //Manzana 1
    TPrimitiva *stop2 = new TPrimitiva(STOP_ID,STOP_ID); //Manzana 2
    TPrimitiva *stop3 = new TPrimitiva(STOP_ID,STOP_ID); //Manzana 3
    TPrimitiva *stop4 = new TPrimitiva(STOP_ID,STOP_ID); //Manzana 4

    //Manzana 1
    TPrimitiva *casa1 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 1
    TPrimitiva *casa2 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 2
    TPrimitiva *casa3 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 1
    TPrimitiva *casa4 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 1
    TPrimitiva *casa5 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 3
    TPrimitiva *casa6 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 3
    TPrimitiva *casa7 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 3
    TPrimitiva *casa8 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 4
    //Manzana 2
    TPrimitiva *casa9 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 5
    TPrimitiva *casa10 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 6
    TPrimitiva *casa11 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 5
    TPrimitiva *casa12 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 5
    TPrimitiva *casa13 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 7
    TPrimitiva *casa14 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 7
    TPrimitiva *casa15 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 7
    TPrimitiva *casa16 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 8
    //Manzana 3
    TPrimitiva *casa17 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 9
    TPrimitiva *casa18 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 10
    TPrimitiva *casa19 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 9
    TPrimitiva *casa20 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 9
    TPrimitiva *casa21 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 11
    TPrimitiva *casa22 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 11
    TPrimitiva *casa23 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 11
    TPrimitiva *casa24 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 12
    //Manzana 4
    TPrimitiva *casa25 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 13
    TPrimitiva *casa26 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 14
    TPrimitiva *casa27 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 13
    TPrimitiva *casa28 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 13
    TPrimitiva *casa29 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 15
    TPrimitiva *casa30 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 15
    TPrimitiva *casa31 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 15
    TPrimitiva *casa32 = new TPrimitiva(CASA_ID,CASA_ID); //Cuadrado 16

    TPrimitiva *semaforo1 = new TPrimitiva(SEMAFORO_ID,SEMAFORO_ID); //Manzana 1
    TPrimitiva *semaforo2 = new TPrimitiva(SEMAFORO_ID,SEMAFORO_ID); //Manzana 2
    TPrimitiva *semaforo3 = new TPrimitiva(SEMAFORO_ID,SEMAFORO_ID); //Manzana 3
    TPrimitiva *semaforo4 = new TPrimitiva(SEMAFORO_ID,SEMAFORO_ID); //Manzana 4

    //Manzana 1
    TPrimitiva *arbol1 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 1
    TPrimitiva *arbol2 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 1
    TPrimitiva *arbol3 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 1
    TPrimitiva *arbol4 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 1
    TPrimitiva *arbol5 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 2
    TPrimitiva *arbol6 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 2
    TPrimitiva *arbol7 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 3
    TPrimitiva *arbol8 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 4
    TPrimitiva *arbol9 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 4
    //Manzana 2
    TPrimitiva *arbol10 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 2
    TPrimitiva *arbol11 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 2
    TPrimitiva *arbol12 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 2
    TPrimitiva *arbol13 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 2
    TPrimitiva *arbol14 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 6
    TPrimitiva *arbol15 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 6
    TPrimitiva *arbol16 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 7
    TPrimitiva *arbol17 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 8
    TPrimitiva *arbol18 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 8
    //Manzana 3
    TPrimitiva *arbol19 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 3
    TPrimitiva *arbol20 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 3
    TPrimitiva *arbol21 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 3
    TPrimitiva *arbol22 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 3
    TPrimitiva *arbol23 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 10
    TPrimitiva *arbol24 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 10
    TPrimitiva *arbol25 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 11
    TPrimitiva *arbol26 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 12
    TPrimitiva *arbol27 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 12
    //Manzana 4
    TPrimitiva *arbol28 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 4
    TPrimitiva *arbol29 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 4
    TPrimitiva *arbol30 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 4
    TPrimitiva *arbol31 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //rotonda 4
    TPrimitiva *arbol32 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 14
    TPrimitiva *arbol33 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 14
    TPrimitiva *arbol34 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 15
    TPrimitiva *arbol35 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 16
    TPrimitiva *arbol36 = new TPrimitiva(ARBOL_ID,ARBOL_ID); //Cuadrado 16


    //Manzana 1
    TPrimitiva *banco1 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 1
    TPrimitiva *banco2 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 2
    TPrimitiva *banco3 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 2
    TPrimitiva *banco4 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 4
    TPrimitiva *banco5 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 4
    //Manzana 2
    TPrimitiva *banco6 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 5
    TPrimitiva *banco7 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 6
    TPrimitiva *banco8 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 6
    TPrimitiva *banco9 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 8
    TPrimitiva *banco10 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 8
    //Manzana 3
    TPrimitiva *banco11 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 9
    TPrimitiva *banco12 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 10
    TPrimitiva *banco13 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 10
    TPrimitiva *banco14 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 12
    TPrimitiva *banco15 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 12
    //Manzana 4
    TPrimitiva *banco16 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 13
    TPrimitiva *banco17 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 14
    TPrimitiva *banco18 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 14
    TPrimitiva *banco19 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 16
    TPrimitiva *banco20 = new TPrimitiva(BANCO_ID,BANCO_ID); //cuadrado 16

    TPrimitiva *papelera1 = new TPrimitiva(PAPELERA_ID,PAPELERA_ID); //Manzana 1
    TPrimitiva *papelera2 = new TPrimitiva(PAPELERA_ID,PAPELERA_ID); //Manzana 2
    TPrimitiva *papelera3 = new TPrimitiva(PAPELERA_ID,PAPELERA_ID); //Manzana 3
    TPrimitiva *papelera4 = new TPrimitiva(PAPELERA_ID,PAPELERA_ID); //Manzana 4

    TPrimitiva *farola1 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 1
    TPrimitiva *farola2 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 2
    TPrimitiva *farola3 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 2
    TPrimitiva *farola4 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 2
    TPrimitiva *farola5 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 4
    TPrimitiva *farola6 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 4
    TPrimitiva *farola7 = new TPrimitiva(FAROLA_ID,FAROLA_ID); //cuadrado 4

    //Manzana 1
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
    TPrimitiva *valla13 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla14 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla15 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla16 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla17 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla18 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla19 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla20 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla21 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla22 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla23 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla24 = new TPrimitiva(VALLA_ID,VALLA_ID);
    //Manzana 2
    TPrimitiva *valla25 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla26 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla27 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla28 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla29 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla30 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla31 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla32 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla33 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla34 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla35 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla36 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla37 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla38 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla39 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla40 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla41 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla42 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla43 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla44 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla45 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla46 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla47 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla48 = new TPrimitiva(VALLA_ID,VALLA_ID);
    //Manzana 3
    TPrimitiva *valla49 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla50 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla51 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla52 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla53 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla54 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla55 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla56 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla57 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla58 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla59 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla60 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla61 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla62 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla63 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla64 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla65 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla66 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla67 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla68 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla69 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla70 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla71 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla72 = new TPrimitiva(VALLA_ID,VALLA_ID);
    //Manzana 4
    TPrimitiva *valla73 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla74 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla75 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla76 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla77 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla78 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla79 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla80 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla81 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla82 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla83 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla84 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla85 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla86 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla87 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla88 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla89 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla90 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla91 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla92 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla93 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla94 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla95 = new TPrimitiva(VALLA_ID,VALLA_ID);
    TPrimitiva *valla96 = new TPrimitiva(VALLA_ID,VALLA_ID);


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
        Para pasar de Manzana 1 a Manzana 2 hay que sumar 60 en tz
        Para pasar de Manzana 1 a Manzana 3 hay que sumar 68 en tx
        Y pues obviamnete de Manzana 3 a Manzana 4 es sumar 60 en tz los datos de Manzana 3

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
    //Manzana 1
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
    //Manzana 2
    casa9->tx = +5;
    casa9->tz = +56;
    casa10->tx = +30;
    casa10->tz = +58;
    casa10->ry = 180;
    casa11->tx = -4;
    casa11->tz = +65;
    casa11->ry = 270;
    casa12->tx = -4;
    casa12->tz = +56;
    casa12->ry = 180;
    casa13->tx = +5;
    casa13->tz = +95;
    casa13->ry = 0;
    casa14->tx = -4;
    casa14->tz = +85;
    casa14->ry = 180;
    casa15->tx = -4;
    casa15->tz = +95;
    casa15->ry = 180;
    casa16->tx = +30;
    casa16->tz = +93;
    casa16->ry = 180;
    //Manzana 3
    casa17->tx = +73;
    casa17->tz = -4;
    casa18->tx = +98;
    casa18->tz = -2;
    casa18->ry = 180;
    casa19->tx = +64;
    casa19->tz = +5;
    casa19->ry = 270;
    casa20->tx = +64;
    casa20->tz = -4;
    casa20->ry = 180;
    casa21->tx = +73;
    casa21->tz = +35;
    casa21->ry = 0;
    casa22->tx = +64;
    casa22->tz = +25;
    casa22->ry = 180;
    casa23->tx = +64;
    casa23->tz = +35;
    casa23->ry = 180;
    casa24->tx = +98;
    casa24->tz = +33;
    casa24->ry = 180;
    //Manzana 4
    casa25->tx = +73;
    casa25->tz = +56;
    casa26->tx = +98;
    casa26->tz = +58;
    casa26->ry = 180;
    casa27->tx = +64;
    casa27->tz = +65;
    casa27->ry = 270;
    casa28->tx = +64;
    casa28->tz = +56;
    casa28->ry = 180;
    casa29->tx = +73;
    casa29->tz = +95;
    casa29->ry = 0;
    casa30->tx = +64;
    casa30->tz = +85;
    casa30->ry = 180;
    casa31->tx = +64;
    casa31->tz = +95;
    casa31->ry = 180;
    casa32->tx = +98;
    casa32->tz = +93;
    casa32->ry = 180;


    escena.AddObject(casa1);
    escena.AddObject(casa2);
    escena.AddObject(casa3);
    escena.AddObject(casa4);
    escena.AddObject(casa5);
    escena.AddObject(casa6);
    escena.AddObject(casa7);
    escena.AddObject(casa8);
    escena.AddObject(casa9);
    escena.AddObject(casa10);
    escena.AddObject(casa11);
    escena.AddObject(casa12);
    escena.AddObject(casa13);
    escena.AddObject(casa14);
    escena.AddObject(casa15);
    escena.AddObject(casa16);
    escena.AddObject(casa17);
    escena.AddObject(casa18);
    escena.AddObject(casa19);
    escena.AddObject(casa20);
    escena.AddObject(casa21);
    escena.AddObject(casa22);
    escena.AddObject(casa23);
    escena.AddObject(casa24);
    escena.AddObject(casa25);
    escena.AddObject(casa26);
    escena.AddObject(casa27);
    escena.AddObject(casa28);
    escena.AddObject(casa29);
    escena.AddObject(casa30);
    escena.AddObject(casa31);
    escena.AddObject(casa32);


    //Semaforos
    //Manzana 1
    semaforo1->tx = +31;
    semaforo1->tz = +9;
    //Manzana 2
    semaforo2->tx = +31;
    semaforo2->tz = +69;
    //Manzana 3
    semaforo3->tx = +99;
    semaforo3->tz = +9;
    //Manzana 4
    semaforo4->tx = +99;
    semaforo4->tz = +69;

    escena.AddObject(semaforo1);
    escena.AddObject(semaforo2);
    escena.AddObject(semaforo3);
    escena.AddObject(semaforo4);

    //STOPS
    //Manzana 1
    stop1->tx = +9.4;
    stop1->tz = +27;
    stop1->ry = 270;
    //Manzana 2
    stop2->tx = +9.4;
    stop2->tz = +87;
    stop2->ry = 270;
    //Manzana 3
    stop3->tx = +77.4;
    stop3->tz = +27;
    stop3->ry = 270;
    //Manzana 4
    stop4->tx = +77.4;
    stop4->tz = +89;
    stop4->ry = 270;

    escena.AddObject(stop1);
    escena.AddObject(stop2);
    escena.AddObject(stop3);
    escena.AddObject(stop4);

    //Arboles
    //Manzana 1
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
    //Manzana 2
    arbol10->tx = +17;
    arbol10->tz = +72;
    arbol10->sy = 1.3;
    arbol10->sx = 1.3;
    arbol11->sz = 1.3;
    arbol11->tx = +13;
    arbol11->tz = +75;
    arbol11->ry = 80;
    arbol11->sy = 0.7;
    arbol11->sx = 0.7;
    arbol11->sz = 0.7;
    arbol12->tx = +17;
    arbol12->tz = +78;
    arbol12->ry = 260;
    arbol13->tx = +21;
    arbol13->tz = +76;
    arbol13->ry = 250;
    arbol14->tx = +38;
    arbol14->tz = +62;
    arbol14->ry = 250;
    arbol15->tx = +34;
    arbol15->tz = +67;
    arbol15->ry = 30;
    arbol15->sy = 0.7;
    arbol15->sx = 0.7;
    arbol15->sz = 0.7;
    arbol16->tx = +4;
    arbol16->tz = +82;
    arbol16->ry = 30;
    arbol16->sy = 0.7;
    arbol16->sx = 0.7;
    arbol16->sz = 0.7;
    arbol17->tx = +38;
    arbol17->tz = +88;
    arbol17->ry = 250;
    arbol18->tx = +37;
    arbol18->tz = +93;
    arbol18->ry = 30;
    arbol18->sy = 0.7;
    arbol18->sx = 0.7;
    arbol18->sz = 0.7;
    //Manzana 3
    arbol19->tx = +85;
    arbol19->tz = +12;
    arbol19->sy = 1.3;
    arbol19->sx = 1.3;
    arbol19->sz = 1.3;
    arbol20->tx = +81;
    arbol20->tz = +15;
    arbol20->ry = 80;
    arbol20->sy = 0.7;
    arbol20->sx = 0.7;
    arbol20->sz = 0.7;
    arbol21->tx = +85;
    arbol21->tz = +18;
    arbol21->ry = 260;
    arbol22->tx = +89;
    arbol22->tz = +16;
    arbol22->ry = 250;
    arbol23->tx = +106;
    arbol23->tz = +2;
    arbol23->ry = 250;
    arbol24->tx = +100;
    arbol24->tz = +7;
    arbol24->ry = 30;
    arbol24->sy = 0.7;
    arbol24->sx = 0.7;
    arbol24->sz = 0.7;
    arbol25->tx = +72;
    arbol25->tz = +22;
    arbol25->ry = 30;
    arbol25->sy = 0.7;
    arbol25->sx = 0.7;
    arbol25->sz = 0.7;
    arbol26->tx = +106;
    arbol26->tz = +28;
    arbol26->ry = 250;
    arbol27->tx = +105;
    arbol27->tz = +33;
    arbol27->ry = 30;
    arbol27->sy = 0.7;
    arbol27->sx = 0.7;
    arbol27->sz = 0.7;
    //Manzana 4
    arbol28->tx = +85;
    arbol28->tz = +72;
    arbol28->sy = 1.3;
    arbol28->sx = 1.3;
    arbol28->sz = 1.3;
    arbol29->tx = +81;
    arbol29->tz = +75;
    arbol29->ry = 80;
    arbol29->sy = 0.7;
    arbol29->sx = 0.7;
    arbol29->sz = 0.7;
    arbol30->tx = +85;
    arbol30->tz = +78;
    arbol30->ry = 260;
    arbol31->tx = +89;
    arbol31->tz = +76;
    arbol31->ry = 250;
    arbol32->tx = +106;
    arbol32->tz = +62;
    arbol32->ry = 250;
    arbol33->tx = +100;
    arbol33->tz = +67;
    arbol33->ry = 30;
    arbol33->sy = 0.7;
    arbol33->sx = 0.7;
    arbol33->sz = 0.7;
    arbol34->tx = +72;
    arbol34->tz = +82;
    arbol34->ry = 30;
    arbol34->sy = 0.7;
    arbol34->sx = 0.7;
    arbol34->sz = 0.7;
    arbol35->tx = +106;
    arbol35->tz = +88;
    arbol35->ry = 250;
    arbol36->tx = +105;
    arbol36->tz = +93;
    arbol36->ry = 30;
    arbol36->sy = 0.7;
    arbol36->sx = 0.7;
    arbol36->sz = 0.7;

    escena.AddObject(arbol1);
    escena.AddObject(arbol2);
    escena.AddObject(arbol3);
    escena.AddObject(arbol4);
    escena.AddObject(arbol5);
    escena.AddObject(arbol6);
    escena.AddObject(arbol7);
    escena.AddObject(arbol8);
    escena.AddObject(arbol9);
    escena.AddObject(arbol10);
    escena.AddObject(arbol11);
    escena.AddObject(arbol12);
    escena.AddObject(arbol13);
    escena.AddObject(arbol14);
    escena.AddObject(arbol15);
    escena.AddObject(arbol16);
    escena.AddObject(arbol17);
    escena.AddObject(arbol18);
    escena.AddObject(arbol19);
    escena.AddObject(arbol20);
    escena.AddObject(arbol21);
    escena.AddObject(arbol22);
    escena.AddObject(arbol23);
    escena.AddObject(arbol24);
    escena.AddObject(arbol25);
    escena.AddObject(arbol26);
    escena.AddObject(arbol27);
    escena.AddObject(arbol28);
    escena.AddObject(arbol29);
    escena.AddObject(arbol30);
    escena.AddObject(arbol31);
    escena.AddObject(arbol32);
    escena.AddObject(arbol33);
    escena.AddObject(arbol34);
    escena.AddObject(arbol35);
    escena.AddObject(arbol36);

    //Bancos
    //Manzana 1
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
    //Manzana 2
    banco6->tx = +5.5;
    banco6->tz = +65.5;
    banco6->ry = 310;
    banco7->tx = +42;
    banco7->tz = +60;
    banco8->tx = +36;
    banco8->tz = +68;
    banco8->ry = 270;
    banco9->tx = +42;
    banco9->tz = +87;
    banco10->tx = +36;
    banco10->tz = +95;
    banco10->ry = 270;
    //Manzana 3
    banco11->tx = +73.5;
    banco11->tz = +5.5;
    banco11->ry = 310;
    banco12->tx = +110;
    banco12->tz = 0;
    banco13->tx = +104;
    banco13->tz = +8;
    banco13->ry = 270;
    banco14->tx = +110;
    banco14->tz = +27;
    banco15->tx = +104;
    banco15->tz = +35;
    banco15->ry = 270;
    //Manzana 4
    banco16->tx = +73.5;
    banco16->tz = +65.5;
    banco16->ry = 310;
    banco17->tx = +110;
    banco17->tz = +60;
    banco18->tx = +104;
    banco18->tz = +68;
    banco18->ry = 270;
    banco19->tx = +110;
    banco19->tz = +87;
    banco20->tx = +104;
    banco20->tz = +95;
    banco20->ry = 270;

    escena.AddObject(banco1);
    escena.AddObject(banco2);
    escena.AddObject(banco3);
    escena.AddObject(banco4);
    escena.AddObject(banco5);
    escena.AddObject(banco6);
    escena.AddObject(banco7);
    escena.AddObject(banco8);
    escena.AddObject(banco9);
    escena.AddObject(banco10);
    escena.AddObject(banco11);
    escena.AddObject(banco12);
    escena.AddObject(banco13);
    escena.AddObject(banco14);
    escena.AddObject(banco15);
    escena.AddObject(banco16);
    escena.AddObject(banco17);
    escena.AddObject(banco18);
    escena.AddObject(banco19);
    escena.AddObject(banco20);

    //Papeleras
    papelera1->tx = +4.4;
    papelera1->tz = +6.4;
    papelera1->ry = 30;
    //Papeleras
    papelera2->tx = +4.4;
    papelera2->tz = +66.4;
    papelera2->ry = 30;
    //Papeleras
    papelera3->tx = +72.4;
    papelera3->tz = +6.4;
    papelera3->ry = 30;
    //Papeleras
    papelera4->tx = +72.4;
    papelera4->tz = +66.4;
    papelera4->ry = 30;

    escena.AddObject(papelera1);
    escena.AddObject(papelera2);
    escena.AddObject(papelera3);
    escena.AddObject(papelera4);

    //Farolas
    //Manzana 1
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
    //Cuadrado 2
    //Manzana 1
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
    //Manzana 2
    valla25->tx = +35;
    valla25->tz = +69.5;
    valla25->ry = 90;
    valla26->tx = +39;
    valla26->tz = +69.5;
    valla26->ry = 90;
    valla27->tx = +43;
    valla27->tz = +69.5;
    valla27->ry = 90;
    valla28->tx = +43.7;
    valla28->tz = +68.8;
    valla28->ry = 0;
    valla29->tx = +43.7;
    valla29->tz = +64.8;
    valla29->ry = 0;
    valla30->tx = +43.7;
    valla30->tz = +60.7;
    valla30->ry = 0;
    valla31->tx = +43.7;
    valla31->tz = +57,4;
    valla31->ry = 0;
    valla32->tx = +43;
    valla32->tz = +54.4;
    valla32->ry = 90;
    valla33->tx = +39;
    valla33->tz = +54.4;
    valla33->ry = 90;
    valla34->tx = +37;
    valla34->tz = +54.4;
    valla34->ry = 90;
    valla35->tx = +31.8;
    valla35->tz = +68;
    valla35->ry = 0;
    valla36->tx = +31.8;
    valla36->tz = +64.8;
    valla36->ry = 0;
    //Cuadrado 8
    valla37->tx = +35;
    valla37->tz = +81;
    valla37->ry = 90;
    valla38->tx = +39;
    valla38->tz = +81;
    valla38->ry = 90;
    valla39->tx = +43;
    valla39->tz = +81;
    valla39->ry = 90;
    valla40->tx = +43.7;
    valla40->tz = +84.3;
    valla40->ry = 0;
    valla41->tx = +43.7;
    valla41->tz = +88.3;
    valla41->ry = 0;
    valla42->tx = +43.7;
    valla42->tz = +92.5;
    valla42->ry = 0;
    valla43->tx = +43.7;
    valla43->tz = +96;
    valla43->ry = 0;
    valla44->tx = +43;
    valla44->tz = +97;
    valla44->ry = 90;
    valla45->tx = +39;
    valla45->tz = +97;
    valla45->ry = 90;
    valla46->tx = +37;
    valla46->tz = +97;
    valla46->ry = 90;
    valla47->tx = +31.8;
    valla47->tz = +84;
    valla47->ry = 0;
    valla48->tx = +31.8;
    valla48->tz = +88;
    valla48->ry = 0;
    //Manzana 3
    valla49->tx = +103;
    valla49->tz = +9.5;
    valla49->ry = 90;
    valla50->tx = +107;
    valla50->tz = +9.5;
    valla50->ry = 90;
    valla51->tx = +111;
    valla51->tz = +9.5;
    valla51->ry = 90;
    valla52->tx = +111.7;
    valla52->tz = +8.8;
    valla52->ry = 0;
    valla53->tx = +111.7;
    valla53->tz = +4.8;
    valla53->ry = 0;
    valla54->tx = +111.7;
    valla54->tz = +0.7;
    valla54->ry = 0;
    valla55->tx = +111.7;
    valla55->tz = -3,4;
    valla55->ry = 0;
    valla56->tx = +111;
    valla56->tz = -6.4;
    valla56->ry = 90;
    valla57->tx = +107;
    valla57->tz = -6.4;
    valla57->ry = 90;
    valla58->tx = +105;
    valla58->tz = -6.4;
    valla58->ry = 90;
    valla59->tx = +99.8;
    valla59->tz = +8;
    valla59->ry = 0;
    valla60->tx = +99.8;
    valla60->tz = +4.8;
    valla60->ry = 0;
    //Cuadrado 12
    valla61->tx = +103;
    valla61->tz = +21;
    valla61->ry = 90;
    valla62->tx = +107;
    valla62->tz = +21;
    valla62->ry = 90;
    valla63->tx = +111;
    valla63->tz = +21;
    valla63->ry = 90;
    valla64->tx = +111.7;
    valla64->tz = +24.3;
    valla64->ry = 0;
    valla65->tx = +111.7;
    valla65->tz = +28.3;
    valla65->ry = 0;
    valla66->tx = +111.7;
    valla66->tz = +32.5;
    valla66->ry = 0;
    valla67->tx = +111.7;
    valla67->tz = +36;
    valla67->ry = 0;
    valla68->tx = +111;
    valla68->tz = +37;
    valla68->ry = 90;
    valla69->tx = +107;
    valla69->tz = +37;
    valla69->ry = 90;
    valla70->tx = +105;
    valla70->tz = +37;
    valla70->ry = 90;
    valla71->tx = +99.8;
    valla71->tz = +24;
    valla71->ry = 0;
    valla72->tx = +99.8;
    valla72->tz = +28;
    valla72->ry = 0;
     //Manzana 4
    valla73->tx = +103;
    valla73->tz = +69.5;
    valla73->ry = 90;
    valla74->tx = +107;
    valla74->tz = +69.5;
    valla74->ry = 90;
    valla75->tx = +111;
    valla75->tz = +69.5;
    valla75->ry = 90;
    valla76->tx = +111.7;
    valla76->tz = +68.8;
    valla76->ry = 0;
    valla77->tx = +111.7;
    valla77->tz = +64.8;
    valla77->ry = 0;
    valla78->tx = +111.7;
    valla78->tz = +60.7;
    valla78->ry = 0;
    valla79->tx = +111.7;
    valla79->tz = +57,4;
    valla79->ry = 0;
    valla80->tx = +111;
    valla80->tz = +54.4;
    valla80->ry = 90;
    valla81->tx = +107;
    valla81->tz = +54.4;
    valla81->ry = 90;
    valla82->tx = +105;
    valla82->tz = +54.4;
    valla82->ry = 90;
    valla83->tx = +99.8;
    valla83->tz = +68;
    valla83->ry = 0;
    valla84->tx = +99.8;
    valla84->tz = +64.8;
    valla84->ry = 0;
    //Cuadrado 16
    valla85->tx = +103;
    valla85->tz = +81;
    valla85->ry = 90;
    valla86->tx = +107;
    valla86->tz = +81;
    valla86->ry = 90;
    valla87->tx = +111;
    valla87->tz = +81;
    valla87->ry = 90;
    valla88->tx = +111.7;
    valla88->tz = +84.3;
    valla88->ry = 0;
    valla89->tx = +111.7;
    valla89->tz = +88.3;
    valla89->ry = 0;
    valla90->tx = +111.7;
    valla90->tz = +92.5;
    valla90->ry = 0;
    valla91->tx = +111.7;
    valla91->tz = +96;
    valla91->ry = 0;
    valla92->tx = +111;
    valla92->tz = +97;
    valla92->ry = 90;
    valla93->tx = +107;
    valla93->tz = +97;
    valla93->ry = 90;
    valla94->tx = +105;
    valla94->tz = +97;
    valla94->ry = 90;
    valla95->tx = +99.8;
    valla95->tz = +84;
    valla95->ry = 0;
    valla96->tx = +99.8;
    valla96->tz = +88;
    valla96->ry = 0;

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
    escena.AddObject(valla25);
    escena.AddObject(valla26);
    escena.AddObject(valla27);
    escena.AddObject(valla28);
    escena.AddObject(valla29);
    escena.AddObject(valla30);
    escena.AddObject(valla31);
    escena.AddObject(valla32);
    escena.AddObject(valla33);
    escena.AddObject(valla34);
    escena.AddObject(valla35);
    escena.AddObject(valla36);
    escena.AddObject(valla37);
    escena.AddObject(valla38);
    escena.AddObject(valla39);
    escena.AddObject(valla40);
    escena.AddObject(valla41);
    escena.AddObject(valla42);
    escena.AddObject(valla43);
    escena.AddObject(valla44);
    escena.AddObject(valla45);
    escena.AddObject(valla46);
    escena.AddObject(valla47);
    escena.AddObject(valla48);
    escena.AddObject(valla49);
    escena.AddObject(valla50);
    escena.AddObject(valla51);
    escena.AddObject(valla52);
    escena.AddObject(valla53);
    escena.AddObject(valla54);
    escena.AddObject(valla55);
    escena.AddObject(valla56);
    escena.AddObject(valla57);
    escena.AddObject(valla58);
    escena.AddObject(valla59);
    escena.AddObject(valla60);
    escena.AddObject(valla61);
    escena.AddObject(valla62);
    escena.AddObject(valla63);
    escena.AddObject(valla64);
    escena.AddObject(valla65);
    escena.AddObject(valla66);
    escena.AddObject(valla67);
    escena.AddObject(valla68);
    escena.AddObject(valla69);
    escena.AddObject(valla70);
    escena.AddObject(valla71);
    escena.AddObject(valla72);
    escena.AddObject(valla73);
    escena.AddObject(valla74);
    escena.AddObject(valla75);
    escena.AddObject(valla76);
    escena.AddObject(valla77);
    escena.AddObject(valla78);
    escena.AddObject(valla79);
    escena.AddObject(valla80);
    escena.AddObject(valla81);
    escena.AddObject(valla82);
    escena.AddObject(valla83);
    escena.AddObject(valla84);
    escena.AddObject(valla85);
    escena.AddObject(valla86);
    escena.AddObject(valla87);
    escena.AddObject(valla88);
    escena.AddObject(valla89);
    escena.AddObject(valla90);
    escena.AddObject(valla91);
    escena.AddObject(valla92);
    escena.AddObject(valla93);
    escena.AddObject(valla94);
    escena.AddObject(valla95);
    escena.AddObject(valla96);


    //Resto de objetos
    escena.AddObject(road);
    escena.AddCar(car1);
    escena.AddCar(car2);


    /**** Regular GLUT main loop ****/
    glutMainLoop();

    return EXIT_SUCCESS;
}

