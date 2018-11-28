
/***************************************************************************************

    CarGL (Objects.h)

    Grado en Ingeniería Multimedia.
    Práctica de Gráficos por Computador.
    OpenGL con Shaders.
  --------------------------------------------------------------------------------------

    Noviembre 2012 - Septiembre 2016 (C) Juan Antonio Puchol García (puchol@dccia.ua.es)

****************************************************************************************/

//---------------------------------------------------------------------------
#ifndef ObjectsH
#define ObjectsH
//---------------------------------------------------------------------------

#define GLEW_STATIC

#include "Shader.h"
#include "Program.h"

#include <string.h>
#include <GL/glui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Constantes
#define PI  3.14159265358979
#define velocidadCoche  0.3
#define rozamiento    0.06
#define rotacionRueda    45

// Identificadores internos de los objetos
#define CARRETERA_ID    10
#define STOP_ID         11
#define CASA_ID         12
#define SEMAFORO_ID     13
#define ARBOL_ID        14
#define BANCO_ID        15
#define PAPELERA_ID     16
#define FAROLA_ID       17
#define VALLA_ID        18
#define COCHE_ID	    100 // Un coche cada 100

// IDs para los callbacks de TGui
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT0_POSITION_ID   210
#define LIGHT1_POSITION_ID   211
#define LIGHT0_INTENSITY_ID  220
#define LIGHT1_INTENSITY_ID  221


#define ENABLE_ID            300
#define DISABLE_ID           301

#define RESET_ID             400

#define SEL_ID               500

// Datos del formato 3DS (x, y, z, A, B, C, u, v)
#define POSITION_COMPONENT_COUNT    3
#define NORMAL_COMPONENT_COUNT      3
#define UV_COMPONENT_COUNT          2
// Cálculo del stride (3+3+2)*4 = 8*4 = 32
#define STRIDE                      32

// Nombre de los attributes
#define A_POSITION  "a_Position"
#define A_NORMAL    "a_Normal"

// Nombre de los uniforms
#define U_PROJECTIONMATRIX      "u_ProjectionMatrix"
#define U_MVMATRIX              "u_MVMatrix"
#define U_VMATRIX               "u_VMatrix"
#define U_COLOR                 "u_Color"
#define U_LUZ0                  "u_Luz0"
//Propiedades
#define WIREFRAME_ID         600
#define CULLING_ID           601
#define ZBUFFER_ID           602
//Camaras
#define V_AEREA              411
#define V_SEGUIMIENTO        412
#define V_PRIMERAPERSONA     413

//************************************************************** Clase TPrimtiva

class TPrimitiva
{
public: // Atributos de la clase
		int ID;				    // DisplayLists del objeto
		int tipo;               // Tipo de Objeto
		float tx,ty,tz; 	    // Posición del objeto
		float sx,sy,sz; 	    // Escalado del objeto
		float rx,ry,rz;     	// Rotación del objeto
		float rr;               // Rotación de las ruedas
		float colores[2][4];    // Color RGB y canal Alfa
		float v;                 // Velocidad del coche
		float anguloCoche;
		float anguloRuedas;

		float   *modelo0;        // modelo a representar
		int     num_vertices0;   // número de vértices

        float   *modelo1;        // modelo a representar
		int     num_vertices1;   // número de vértices

public: // Métodos
 		TPrimitiva(int DL, int tipo);
        void __fastcall Render(int seleccion, bool reflejo=false);
};

//************************************************************** Clase TEscena

class TEscena
{
public: // Atributos de la clase
		int   	seleccion;   	// Objeto seleccionado, 0=ninguno
        int		num_objects;    // Número de objetos (excepto coches)
        int     num_cars;       // Número de coches
        int     raton;

        TPrimitiva  *cars[10];
        TPrimitiva  *objects[600];

        int ultimoSelec;

        // Handles de los attributes y uniforms
        int aPositionLocation;
        int aNormalLocation;
        int uProjectionMatrixLocation;
        int uMVMatrixLocation;
		int uVMatrixLocation;
		int uColorLocation;
		int uLuz0Location;

		glm::mat4 projectionMatrix; // Almacena la matriz de proyección
        glm::mat4 viewMatrix;       // Almacena la matriz de la vista (cámara)

		Program  *shaderProgram;    // Almacena el programa de OpenGL (ShaderProgram)

        // Vectores de luces y materiales
        GLfloat light0_ambient[4];
        GLfloat light0_diffuse[4];
        GLfloat light0_specular[4];
        GLfloat light0_position[4];

        GLfloat light1_ambient[4];
        GLfloat light1_diffuse[4];
        GLfloat light1_specular[4];
        GLfloat light1_position[4];

        GLfloat mat_ambient[4];
        GLfloat mat_diffuse[4];
        GLfloat mat_specular[4];
        GLfloat mat_shininess[1];


        float   xy_aspect;
        int     last_x, last_y;

        // live variables usadas por GLUI en TGui
        int     wireframe;
        int     z_buffer;
        int     culling;

        int     show_car;
        int     show_wheels;
        int     show_road;
        int     show_casas;
        int     show_stops;
        int     show_semaforos;
        int     show_arboles;
        int     show_bancos;
        int     show_papeleras;
        int     show_farolas;
        int     show_vallas;

        int tipoVista;
        int camaraSeguimiento;
        int vistaAerea;
        int primeraPersona;


        GLfloat view_position[3];
        GLfloat view_rotate[16];
        float   scale;

public: // Métodos
		TEscena();

        void __fastcall InitGL();
		void __fastcall Render();
		void __fastcall RenderCars(bool reflejo=false);
		void __fastcall RenderObjects(bool reflejo=false);

		void __fastcall AddCar(TPrimitiva *car);
		void __fastcall AddObject(TPrimitiva *object);

		TPrimitiva __fastcall *GetCar(int id);

		void __fastcall Pick3D(int mouse_x, int mouse_y);


};

//************************************************************** Clase TGui

class TGui
{
public:
        int             window_id;

        // live variables usadas por GLUI
        int             sel;
        int             enable_panel2;

        int             light0_enabled;
        int             light1_enabled;
        float           light0_intensity;
        float           light1_intensity;
        float           light0_position[4];
        float           light1_position[4];

        GLUI            *glui, *glui2;
        GLUI_Spinner    *light0_spinner;
        GLUI_Spinner    *light1_spinner;
        GLUI_RadioGroup *radio;
        GLUI_Panel      *obj_panel;
        GLUI_Rotation   *view_rot;


public:
        TGui();
        void __fastcall Init(int main_window);
        void __fastcall ControlCallback(int control);
        void __fastcall Idle( void );
        void __fastcall Reshape( int x, int y  );
        void __fastcall Motion( int x, int y  );
        void __fastcall Mouse(int button, int button_state, int x, int y );
};

//************************************************************** Variables de clase

extern TEscena  escena;
extern TGui     gui;

#endif
