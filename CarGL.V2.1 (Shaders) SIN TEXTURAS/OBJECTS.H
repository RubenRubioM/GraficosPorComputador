
/***************************************************************************************

    CarGL (Objects.h)

    Grado en Ingenier�a Multimedia.
    Pr�ctica de Gr�ficos por Computador.
    OpenGL con Shaders.
  --------------------------------------------------------------------------------------

    Noviembre 2012 - Septiembre 2016 (C) Juan Antonio Puchol Garc�a (puchol@dccia.ua.es)

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
#define velocidadCoche  0.6
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




#define ENABLE_ID            300
#define DISABLE_ID           301

#define RESET_ID             400

#define SEL_ID               500

// Datos del formato 3DS (x, y, z, A, B, C, u, v)
#define POSITION_COMPONENT_COUNT    3
#define NORMAL_COMPONENT_COUNT      3
#define UV_COMPONENT_COUNT          2
// C�lculo del stride (3+3+2)*4 = 8*4 = 32
#define STRIDE                      32

// Nombre de los attributes
#define A_POSITION  "a_Position"
#define A_NORMAL    "a_Normal"
#define A_TEXTURECORD "a_TextureCoord"

// Nombre de los uniforms
#define U_PROJECTIONMATRIX      "u_ProjectionMatrix"
#define U_MVMATRIX              "u_MVMatrix"
#define U_VMATRIX               "u_VMatrix"
#define U_COLOR                 "u_Color"

#define U_SAMPLER               "u_Sampler"

//Cosas para luz 0
#define U_LUZ0                  "u_Luz0"

#define U_LIGHT0_X               "u_Light0_x"
#define U_LIGHT0_Y               "u_Light0_y"
#define U_LIGHT0_Z               "u_Light0_z"
#define U_LIGHT0_I               "u_Light0_i"

#define LIGHT0_ENABLED_ID    200
#define LIGHT0_POSITION_ID   210
#define LIGHT0_INTENSITY_ID  220

//Cosas para luz 1
#define U_LUZ1                  "u_Luz1"

#define U_LIGHT1_X               "u_Light1_x"
#define U_LIGHT1_Y               "u_Light1_y"
#define U_LIGHT1_Z               "u_Light1_z"
#define U_LIGHT1_I               "u_Light1_i"

#define LIGHT1_ENABLED_ID    201
#define LIGHT1_POSITION_ID   211
#define LIGHT1_INTENSITY_ID  221

//Cosas para luz 2
#define U_LUZ2                  "u_Luz2"

#define U_LIGHT2_X               "u_Light2_x"
#define U_LIGHT2_Y               "u_Light2_y"
#define U_LIGHT2_Z               "u_Light2_z"
#define U_LIGHT2_I               "u_Light2_i"

#define LIGHT2_ENABLED_ID    202
#define LIGHT2_POSITION_ID   212
#define LIGHT2_INTENSITY_ID  222

#define U_LUZ_ESPECULAR           "u_luz_especular"

//Propiedades
#define WIREFRAME_ID         600
#define CULLING_ID           601
#define ZBUFFER_ID           602
#define SOMBREADO_ID         603
#define SENTIDO_ID           604
#define VISUALIZACION_ID     605
#define LUZ_ESPECULAR_ID     606

#define CAM_ID               420

#define CLICKADO            "clickado"

//************************************************************** Clase TPrimtiva

class TPrimitiva
{
public: // Atributos de la clase
		int ID;				    // DisplayLists del objeto
		int tipo;               // Tipo de Objeto
		float tx,ty,tz; 	    // Posici�n del objeto
		float sx,sy,sz; 	    // Escalado del objeto
		float rx,ry,rz;     	// Rotaci�n del objeto
		float rr;               // Rotaci�n de las ruedas
		float ryCoche;
		float colores[2][4];    // Color RGB y canal Alfa
		float v;                 // Velocidad del coche
		float anguloCoche;
		float anguloRuedas;


		float   *modelo0;        // modelo a representar
		int     num_vertices0;   // n�mero de v�rtices

        float   *modelo1;        // modelo a representar
		int     num_vertices1;   // n�mero de v�rtices

public: // M�todos
 		TPrimitiva(int DL, int tipo);
        void __fastcall Render(int seleccion, bool reflejo=false);
};

//************************************************************** Clase TEscena

class TEscena
{
public: // Atributos de la clase
		int   	seleccion;   	// Objeto seleccionado, 0=ninguno
        int		num_objects;    // N�mero de objetos (excepto coches)
        int     num_cars;       // N�mero de coches
        int     raton;

        unsigned char *texturas[3]; //array de dos texturas.
        int texturas_width[3]; //array con las dimensiones de las texturas
        int texturas_height[3]; // array con las dimensiones de las texturas
        GLuint texturas_id[3];


        int aTextureCoordLocation; //atributo con la coordenada de textura para cada vertice
        int u_SamplerLocation; //la variable que usaremos para cargarle la textura
        int activadaLocation; //para saber si tenemos que aplicar textura en el fragment shader.




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
		int seleccionarLocation;

		//Cosas necesarias para la Luz0

		int uLight0_xLocation;             //Posicion en x de la luz 0 para el vertexShader
		int uLight0_yLocation;             //Posicion en y de la luz 0 para el vertexShader
		int uLight0_zLocation;             //Posicion en z de la luz 0 para el vertexShader
		int uLight0_iLocation;             //Intensidad de la luz
		int uLuz0Location;

		//Cosas necesarias para la Luz1

		int uLight1_xLocation;             //Posicion en x de la luz 0 para el vertexShader
		int uLight1_yLocation;             //Posicion en y de la luz 0 para el vertexShader
		int uLight1_zLocation;             //Posicion en z de la luz 0 para el vertexShader
		int uLight1_iLocation;             //Intensidad de la luz
		int uLuz1Location;

		//Cosas necesarias para la Luz2

		int uLight2_xLocation;             //Posicion en x de la luz 0 para el vertexShader
		int uLight2_yLocation;             //Posicion en y de la luz 0 para el vertexShader
		int uLight2_zLocation;             //Posicion en z de la luz 0 para el vertexShader
		int uLight2_iLocation;             //Intensidad de la luz
		int uLuz2Location;

		int luzEspecular;
		int uLuzEspecularLocation;

		glm::mat4 projectionMatrix; // Almacena la matriz de proyecci�n
        glm::mat4 viewMatrix;       // Almacena la matriz de la vista (c�mara)

		Program  *shaderProgram;    // Almacena el programa de OpenGL (ShaderProgram)

        // Vectores de luces y materiales
        GLfloat light0_ambient[4];
        GLfloat light0_diffuse[4];
        GLfloat light0_specular[4];
        GLfloat light0_position[4]; //Posicion de la camara que lo recoge el spinner

        GLfloat light1_ambient[4];
        GLfloat light1_diffuse[4];
        GLfloat light1_specular[4];
        GLfloat light1_position[4];

        GLfloat light2_ambient[4];
        GLfloat light2_diffuse[4];
        GLfloat light2_specular[4];
        GLfloat light2_position[4];

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
        int     sombreado;

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

        int     reflejo; // reflejos
        int     tipoVista;
        int     sentido;

        int     visualizacion;


        int     mode_cam;
        int     cam;



        GLfloat view_position[3];
        GLfloat view_rotate[16];
        float   scale;

public: // M�todos
		TEscena();

        void __fastcall InitGL();
		void __fastcall Render();
		void __fastcall RenderCars(bool reflejo=false);
		void __fastcall RenderObjects(bool reflejo=false);

		void __fastcall AddCar(TPrimitiva *car);
		void __fastcall AddObject(TPrimitiva *object);

		TPrimitiva __fastcall *GetCar(int id);

		void __fastcall Pick3D(int mouse_x, int mouse_y);
		void __fastcall renderSeleccion();



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
        int             light2_enabled;
        float           light0_intensity;
        float           light1_intensity;
        float           light2_intensity;
        float           light0_position[4];
        float           light1_position[4];
        float           light2_position[4];

        GLUI            *glui, *glui2;
        GLUI_Spinner    *light0_spinner;
        GLUI_Spinner    *light1_spinner;
        GLUI_Spinner    *light2_spinner;
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
