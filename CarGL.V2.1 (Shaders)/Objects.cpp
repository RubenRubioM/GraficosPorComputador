
/****************************************************************************************

    CarGL (Objects.cpp)

    Grado en Ingeniería Multimedia.
    Práctica de Gráficos por Computador.
    OpenGL con Shaders.
  ---------------------------------------------------------------------------------------

    Noviembre 2012 - Septiembre 2016 (C) Juan Antonio Puchol García (puchol@dccia.ua.es)


*****************************************************************************************/

#include "Objects.h"
#include <GL/glui.h>

#include "load3ds.c"

// Variable para inicializar los vectores correpondientes con los valores iniciales
GLfloat light0_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light0_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light0_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light0_position_c[4] = {-10.0f, -10.0f, -30.0f, 1.0f };

GLfloat light1_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light1_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light1_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light1_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f };

GLfloat mat_ambient_c[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse_c[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular_c[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_shininess_c[1] = { 100.0f };

// Matriz de 4x4 = (I)
float view_rotate_c[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_position_c[3] = { 0.0, -20.0, -70.0 };

float coloresc_c[2][4] = { {0.8, 0.5, 0.0, 1.0}, {0.5, 0.5, 0.5, 1.0}}; // Color del coche
float coloresr_c[2][4] = { {0.4, 0.3, 0.3, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de la carretera
float coloresStop_c[2][4] = { {0.93, 0.28, 0.1, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de los stops
float coloresArbol_c[2][4] = { {0.48, 0.86, 0.4, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de los arboles
float coloresCasa_c[2][4] = { {0.84, 0.8, 0.54, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de las casas
float coloresSemaforo_c[2][4] = { {0.78, 0.78, 0.78, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de los semaforos
float coloresBanco_c[2][4] = { {0.44, 0.4, 0.14, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de los bancos
float coloresPapelera_c[2][4] = { {0.33, 0.51, 0.32, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de las papeleras
float coloresFarola_c[2][4] = { {0.83, 0.83, 0.83, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de las farolas
float coloresValla_c[2][4] = { {0.53, 0.5, 0.17, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de las vallas

//************************************************************** Variables de clase

TEscena escena;
TGui    gui;

//************************************************************** Clase TPrimitiva

TPrimitiva::TPrimitiva(int DL, int t)
{

    ID   = DL;
    tipo = t;
    anguloRuedas=0;
    sx = sy = sz = 1;
    rx = ry = rz = 0;
	switch (tipo) {
		case CARRETERA_ID: {  // Creación de la carretera
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/terreno.3ds", &num_vertices0);

            break;
		}
		case COCHE_ID: { // Creación del coche
		    rr =  0.0;
		    ty=0.6;

		    memcpy(colores, coloresc_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Coche menos ruedas.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/rueda.3ds", &num_vertices1);
            break;
		}
		case CASA_ID: {
            //asignamos siempre una altura minima para todas los objetos para que no se solape con el suelo
            ty=0.6;
            memcpy(colores, coloresCasa_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/casa.3ds",&num_vertices0);
            break;
		}
		case STOP_ID: {
            ty=0.6;
            memcpy(colores, coloresStop_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/STOP.3ds",&num_vertices0);
            break;
		}

		case SEMAFORO_ID: {
            ty=0.6;
            memcpy(colores, coloresSemaforo_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/semaforo.3ds",&num_vertices0);
            break;
		}

		case ARBOL_ID: {
            ty=0.6;
            memcpy(colores, coloresArbol_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/arbol.3ds",&num_vertices0);
            break;
		}

		case BANCO_ID: {
            ty=0.6;
            memcpy(colores, coloresBanco_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/banco.3ds",&num_vertices0);
            break;
		}

		case PAPELERA_ID: {
            ty=0.6;
            memcpy(colores, coloresPapelera_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/papelera.3ds",&num_vertices0);
            break;
		}

		case FAROLA_ID: {
            ty=0.6;
            memcpy(colores, coloresFarola_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/farola.3ds",&num_vertices0);
            break;
		}

		case VALLA_ID: {
            ty=0.9;
            memcpy(colores, coloresValla_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/valla.3ds",&num_vertices0);
            break;
		}
	} // switch
}

void __fastcall TPrimitiva::Render(int seleccion, bool reflejo)
{
    glm::mat4   modelMatrix;
    glm::mat4   modelViewMatrix;




    switch (tipo) {

        case CARRETERA_ID: {
            if (escena.show_road) {
                    glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Cálculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);




            }
            break;
        }

        case STOP_ID: {

            if(escena.show_stops){
                    glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Cálculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }

            break;
        }

        case SEMAFORO_ID: {

            if(escena.show_semaforos){
                    glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Cálculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }

            break;
        }

        case ARBOL_ID: {

            if(escena.show_arboles){

                glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Cálculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));



                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }

            break;
        }

        case BANCO_ID: {

            if(escena.show_bancos){
                    glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Cálculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }

            break;
        }

        case PAPELERA_ID: {

            if(escena.show_papeleras){
                    glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Cálculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }

            break;
        }

        case FAROLA_ID: {

            if(escena.show_farolas){
                    glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Cálculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }

            break;
        }

         case VALLA_ID: {

            if(escena.show_vallas){
                    glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Cálculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }

            break;
        }

        case CASA_ID: {


            if(escena.show_casas){
                    glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Cálculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));   // en radianes


                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);

            }

            break;
        }
        case COCHE_ID: {
            if (escena.show_car) {

                if( v != 0)
                {

                    float angulo = (ry*PI)/180.0;


                    float coseno = cos(angulo);
                    float seno = sin(angulo);

                    //Aqui movemos el coche
                    tz += v * coseno;
                    tx += v * seno;


                    rr += v*rotacionRueda;

                    if(v > 0){
                        v -= rozamiento;

                        if(v<=0)
                            v=0;
                    }
                    else if(v < 0){
                        v += rozamiento;

                        if(v >= 0)
                            v = 0;
                    }
                    ry += (anguloRuedas * v);
                }


                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[0]);
                // Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                // Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty+0.4, tz));
                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));
                //rotacion
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));      // en radianes
                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);


            }


            if (escena.show_wheels)
            {
                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[1]);
                // Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);

                // RUEDA Delantera Derecha : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+1.15, ty+0.5, tz+2));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(anguloRuedas), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Delantera Izquierda : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx-2, ty+0.5, tz+2));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(anguloRuedas), glm::vec3(0,1,0));      // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Trasera Derecha : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+1.15, ty+0.5, tz-1.9));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Trasera Izquierda : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx-2, ty+0.5, tz-1.9));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));


                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
                break;
            }
        }

    } // switch

}

//************************************************************** Clase TEscena

TEscena::TEscena() {

    seleccion = 1;
    ultimoSelec = 0;
    num_objects = 0;
    num_cars = 0;

    /*

        Aqui inicializamos las variables de la interfaz, como por ejemplo los ticks de mostrar objetos

    */
    show_car = 1;
    show_wheels = 1;
    show_road = 1;
    show_casas = 0;
    show_stops = 0;
    show_semaforos = 0;
    show_arboles = 0;
    show_bancos = 0;
    show_papeleras = 0;
    show_farolas = 0;
    show_vallas = 0;

    tipoVista = 0;
    primeraPersona = 0;
    camaraSeguimiento = 0;
    vistaAerea = 0;

    // live variables usadas por GLUI en TGui
    wireframe = 0;
    z_buffer = 1;
    culling = 0;

    scale = 1.0;
    xy_aspect = 1;
    last_x = 0;
    last_y = 0;

    memcpy(view_position, view_position_c, 3*sizeof(float));
    memcpy(view_rotate, view_rotate_c, 16*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));
    memcpy(light0_diffuse, light0_diffuse_c, 4*sizeof(float));
    memcpy(light0_specular, light0_specular_c, 4*sizeof(float));
    memcpy(light0_position, light0_position_c, 4*sizeof(float));

    memcpy(light1_ambient, light1_ambient_c, 4*sizeof(float));
    memcpy(light1_diffuse, light1_diffuse_c, 4*sizeof(float));
    memcpy(light1_specular, light1_specular_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));

    memcpy(mat_ambient, mat_ambient_c, 4*sizeof(float));
    memcpy(mat_diffuse, mat_diffuse_c, 4*sizeof(float));
    memcpy(mat_specular, mat_specular_c, 4*sizeof(float));
    memcpy(mat_shininess, mat_shininess_c, 1*sizeof(float));
}

void __fastcall TEscena::InitGL()
{
    int tx, ty, tw, th;

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Inicialización de GLEW
    std::cout << "Inicializando GLEW" << std::endl << std::endl;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendedor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // Carga de los Shaders
    std::cout << std::endl << "Cargando Shaders" << std::endl;

    Shader shader;

    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("../../Shaders/VertexShader.glsl", GL_VERTEX_SHADER));
    //std::cout << "Vertex Shader: " << shader.ReturnShaderID() << std::endl;
    shaders.push_back(shader.LoadShader("../../Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER));
    //std::cout << "Fragment Shader: " << shader.ReturnShaderID() << std::endl;
    shaderProgram = new Program(shaders);

    //std::cout << "Shader Program: " << shaderProgram->ReturnProgramID() << std::endl;

    glUseProgram(shaderProgram->ReturnProgramID());
    //glValidateProgram(shaderProgram->ReturnProgramID());

    aPositionLocation=shaderProgram->attrib(A_POSITION);
    aNormalLocation=shaderProgram->attrib(A_NORMAL);

    uProjectionMatrixLocation=shaderProgram->uniform(U_PROJECTIONMATRIX);
    uMVMatrixLocation=shaderProgram->uniform(U_MVMATRIX);
    uVMatrixLocation=shaderProgram->uniform(U_VMATRIX);
    uColorLocation=shaderProgram->uniform(U_COLOR);
    uLuz0Location=shaderProgram->uniform(U_LUZ0);

    /*
    std::cout << "a_Position Location: " << aPositionLocation << std::endl;
    std::cout << "a_Normal Location: " << aNormalLocation << std::endl;

    std::cout << "u_ProjectionMatrix Location: " << uProjectionMatrixLocation << std::endl;
    std::cout << "u_MVMatrix Location: " << uMVMatrixLocation << std::endl;
    std::cout << "u_VMatrix Location: " << uVMatrixLocation << std::endl;
    std::cout << "u_Color Location: " << uColorLocation << std::endl;
    std::cout << "u_Luz0 Location: " << uLuz0Location << std::endl;
    */

    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(aPositionLocation);
    glEnableVertexAttribArray(aNormalLocation);

    // Estableciendo la matriz de proyección perspectiva
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    xy_aspect = (float)tw / (float)th;
    projectionMatrix = glm::perspective(45.0f, xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}


/************************** TEscena::AddCar(TPrimitiva *car) *****************/

void __fastcall TEscena::AddCar(TPrimitiva *car)
{
    cars[num_cars] = car;
    num_cars++;
}

/******************** TEscena::AddObject(TPrimitiva *object) *****************/

void __fastcall TEscena::AddObject(TPrimitiva *object)
{
    objects[num_objects] = object;
    num_objects++;
}

/******************** TPrimitiva *TEscena::GetCar(int id) ********************/

TPrimitiva __fastcall *TEscena::GetCar(int id)
{
    TPrimitiva *p=NULL;

    for (int i=0; i<num_cars; i++)
    {
        if (cars[i]->ID==id)
        {
            p = cars[i];
        }

    }
    return(p);
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderCars(bool reflejo) {

    for (int i=0; i<num_cars; i++)
    {
        cars[i]->Render(seleccion, reflejo);
    }
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderObjects(bool reflejo) {

    for (int i=0; i<num_objects; i++)
    {
        objects[i]->Render(seleccion, reflejo);
    }
}

/***************************************** TEscena::Render() *****************/

void __fastcall TEscena::Render()
{

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Transformación del escenario
    glTranslatef( view_position[0], view_position[1], view_position[2] );   // Traslación
    glMultMatrixf(view_rotate);                                             // Rotación
    glScalef(scale, scale, scale);                                          // Escalado

    if(escena.camaraSeguimiento==1)
    {
        TPrimitiva *cam = NULL;
        cam = GetCar(seleccion);   //Obtenemos el coche

        if(cam)     //Situamos camara detrás del coche
        {
            float angulo = (cam->ry*PI)/180.0;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(cam->tx-20*sin(angulo),cam->ty+10,cam->tz-20*cos(angulo),cam->tx,cam->ty+5,cam->tz,0,1,0);
        }
    }else if(escena.vistaAerea == 1)
    {
        //Obtenemos el coche
        TPrimitiva *cam = NULL;
        cam = GetCar(seleccion);

        //Situamos camara arriba del coche
        if(cam)
        {
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            //PosCamX,PosCamY,PosCamZ,  DondeMiraX,DondeMiraY,DondeMiraZ,   0,1,0
            gluLookAt(cam->tx,cam->ty+150,cam->tz,cam->tx,cam->ty,cam->tz,0,0,1);
        }
    }else if(escena.primeraPersona == 1)
    {
        //Obtenemos el coche
        TPrimitiva *cam = NULL;
        cam = GetCar(seleccion);

        //Situamos camara detrás del coche
        if(cam)
        {
            float angulo = (cam->ry*PI)/180.0;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            //PosCamX,PosCamY,PosCamZ,  DondeMiraX,DondeMiraY,DondeMiraZ,   0,1,0(direccion arriba camara)
            gluLookAt(cam->tx+sin(angulo),cam->ty+2,cam->tz+cos(angulo),cam->tx+5*sin(angulo),cam->ty+2,cam->tz+5*cos(angulo),0,1,0);
        }
    }

    glm::mat4 rotateMatrix;

    glClearColor(0.0, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Cálculo de la vista (cámara)
    viewMatrix      = glm::mat4(1.0f);
    rotateMatrix    = glm::make_mat4(view_rotate);
    viewMatrix      = glm::translate(viewMatrix,glm::vec3(view_position[0], view_position[1], view_position[2]));
    viewMatrix      = viewMatrix*rotateMatrix;
    viewMatrix      = glm::scale(viewMatrix,glm::vec3(scale, scale, scale));

    glUniform1i(uLuz0Location, gui.light0_enabled);
    glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix)); // Para la luz matrix view pero sin escalado!

    // Dibujar carretera y objetos
    RenderObjects(seleccion);

    // Dibujar coches
    RenderCars(seleccion);

    glutSwapBuffers();
}

// Selecciona un objeto a través del ratón
void __fastcall TEscena::Pick3D(int mouse_x, int mouse_y)
{

}

//************************************************************** Clase TGui

TGui::TGui()
{
    sel = 1;
    enable_panel2 = 1;

    light0_enabled = 1;
    light1_enabled = 1;
    light0_intensity = 0.8;
    light1_intensity = 0.8;
    memcpy(light0_position, light0_position_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));
}

void controlCallback(int control)
{
    gui.ControlCallback(control);
}

void __fastcall TGui::Init(int main_window) {

    /****************************************************/
    /*        Código con el interfaz Gráfico GLUI       */
    /****************************************************/
    printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

    window_id = main_window;

    /*** Crea a ventana lateral ***/
    glui = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_RIGHT );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    // Añade un panel con texto con el valor de la selección
    GLUI_Panel *panel0 = new GLUI_Panel(glui, "Seleccion");
    GLUI_RadioGroup *radioGroup = new GLUI_RadioGroup(panel0, &sel, SEL_ID, controlCallback);
    glui->add_radiobutton_to_group(radioGroup, "NINGUNO");


    glui->add_radiobutton_to_group(radioGroup, "COCHE 1");
    glui->add_radiobutton_to_group(radioGroup, "COCHE 2");


    // Añade una separación
    new GLUI_StaticText( glui, "" );

    obj_panel = new GLUI_Rollout(glui, "Propiedades", true );

    /***** Control para las propiedades de escena *****/

    new GLUI_Checkbox( obj_panel, "Modo Wireframe", &escena.wireframe, WIREFRAME_ID, controlCallback );

    glui->add_column_to_panel(obj_panel, true);
    new GLUI_Checkbox( obj_panel, "Culling", &escena.culling, CULLING_ID, controlCallback );
    new GLUI_Checkbox( obj_panel, "Z Buffer", &escena.z_buffer, ZBUFFER_ID, controlCallback );

    /******** Añade controles para las luces ********/

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Luces", false );

    GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Luz 1" );
    GLUI_Panel *light1 = new GLUI_Panel( roll_lights, "Luz 2" );

    new GLUI_Checkbox( light0, "Encendida", &light0_enabled, LIGHT0_ENABLED_ID, controlCallback );
    light0_spinner = new GLUI_Spinner( light0, "Intensidad:", &light0_intensity,
                            LIGHT0_INTENSITY_ID, controlCallback );
    light0_spinner->set_float_limits( 0.0, 1.0 );
    GLUI_Scrollbar *sb;
    sb = new GLUI_Scrollbar( light0, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[0],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[1],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[2],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_Checkbox( light1, "Encendida", &light1_enabled, LIGHT1_ENABLED_ID, controlCallback );
    light1_spinner = new GLUI_Spinner( light1, "Intensidad:", &light1_intensity,
                            LIGHT1_INTENSITY_ID, controlCallback );
    light1_spinner->set_float_limits( 0.0, 1.0 );
    sb = new GLUI_Scrollbar( light1, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[0],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[1],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[2],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_StaticText( glui, "" );

    GLUI_Rollout *camaras = new GLUI_Rollout(glui, "Camaras", false );
    new GLUI_Button( camaras, "Vista Seguimiento", V_SEGUIMIENTO, controlCallback );
    new GLUI_Button( camaras, "Primera Persona", V_PRIMERAPERSONA, controlCallback );
    new GLUI_Button( camaras, "Vista Aerea", V_AEREA, controlCallback );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    /***  Rollout de Opciones ***/
    GLUI_Rollout *options = new GLUI_Rollout(glui, "Opciones", true );
    new GLUI_Checkbox( options, "Dibujar Coche", &escena.show_car );
    new GLUI_Checkbox( options, "Dibujar Ruedas", &escena.show_wheels );
    new GLUI_Checkbox( options, "Dibujar Carretera", &escena.show_road );
    new GLUI_Checkbox( options, "Dibujar Casas", &escena.show_casas );
    new GLUI_Checkbox( options, "Dibujar Stops", &escena.show_stops );
    new GLUI_Checkbox( options, "Dibujar Semaforos", &escena.show_semaforos );
    new GLUI_Checkbox( options, "Dibujar Arboles", &escena.show_arboles );
    new GLUI_Checkbox( options, "Dibujar Bancos", &escena.show_bancos );
    new GLUI_Checkbox( options, "Dibujar Papeleras", &escena.show_papeleras );
    new GLUI_Checkbox( options, "Dibujar Farolas", &escena.show_farolas );
    new GLUI_Checkbox( options, "Dibujar Vallas", &escena.show_vallas );



    /*** Disable/Enable botones ***/
    // Añade una separación
    new GLUI_StaticText( glui, "" );
    new GLUI_Checkbox( glui, "Bloquear Movimiento", &enable_panel2 );
    // Añade una separación
    new GLUI_StaticText( glui, "" );
    new GLUI_Button( glui, "Resetear Posicion", RESET_ID, controlCallback );

    // Añade una separación
    new GLUI_StaticText( glui, "" );


    // Añade una separación
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

     // Añade una separación
    new GLUI_StaticText( glui, "" );

    new GLUI_StaticText( glui, "  Autor:" );
    new GLUI_StaticText( glui, "  2018-2019 (C) Ruben Rubio Martinez  " );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    /****** A 'quit' button *****/
    new GLUI_Button( glui, "Salir", 0,(GLUI_Update_CB)exit );

    // Crea la subventana inferior
    glui2 = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_BOTTOM );

    /**** Link windows to GLUI, and register idle callback ******/
    glui->set_main_gfx_window( window_id );
    glui2->set_main_gfx_window( window_id );

    view_rot = new GLUI_Rotation(glui2, "Rotacion Escena", escena.view_rotate );
    view_rot->set_spin( 1.0 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_xy = new GLUI_Translation(glui2, "Traslacion Escena XY", GLUI_TRANSLATION_XY, escena.view_position );
    trans_xy->set_speed( .05 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_x =  new GLUI_Translation(glui2, "Traslacion Escena X", GLUI_TRANSLATION_X, escena.view_position );
    trans_x->set_speed( .05 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_y = new GLUI_Translation( glui2, "Traslacion Escena Y", GLUI_TRANSLATION_Y, &escena.view_position[1] );
    trans_y->set_speed( .05 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_z = new GLUI_Translation( glui2, "Traslacion Escena Z", GLUI_TRANSLATION_Z, &escena.scale );
    trans_z->set_speed( .005 );

}

/**************************************** TGui::ControlCallback() *******************/

void __fastcall TGui::ControlCallback( int control )
{
    switch (control) {
        case WIREFRAME_ID:{

            //MODO ALAMBRICO
            if(escena.wireframe)
            {
                glPolygonMode(GL_FRONT, GL_LINE);//DELANTERO
                glPolygonMode(GL_BACK, GL_LINE);//TRASERO
            }
            else
            {
                glPolygonMode(GL_FRONT, GL_FILL);
                glPolygonMode(GL_BACK, GL_FILL);
            }
            break;
        }
        case CULLING_ID: {
            if(escena.culling){
                glEnable(GL_CULL_FACE);
                glCullFace(GL_FRONT);
            }
            else
                glDisable(GL_CULL_FACE);
            break;
        }case ZBUFFER_ID: {
            if(escena.z_buffer)
                glEnable(GL_DEPTH_TEST);
            else
                glDisable(GL_DEPTH_TEST);
            break;
        }
        case LIGHT0_ENABLED_ID: {
            if ( light0_enabled )
                light0_spinner->enable();
            else
                light0_spinner->disable();
            break;
        }
        case LIGHT1_ENABLED_ID: {
            if ( light1_enabled )
                light1_spinner->enable();
            else
                light1_spinner->disable();
            break;
        }
        case LIGHT0_INTENSITY_ID: {

            float v[] = {
                escena.light0_diffuse[0],  escena.light0_diffuse[1],
                escena.light0_diffuse[2],  escena.light0_diffuse[3] };

            v[0] *= light0_intensity;
            v[1] *= light0_intensity;
            v[2] *= light0_intensity;
            break;
        }
        case LIGHT1_INTENSITY_ID: {

            float v[] = {
                escena.light1_diffuse[0],  escena.light1_diffuse[1],
                escena.light1_diffuse[2],  escena.light1_diffuse[3] };

            v[0] *= light1_intensity;
            v[1] *= light1_intensity;
            v[2] *= light1_intensity;
            break;
        }
        case ENABLE_ID: {
            glui2->enable();
            break;
        }
        case DISABLE_ID: {
            glui2->disable();
            break;
        }
        case RESET_ID: {

            memcpy(escena.view_position,view_position_c,3*sizeof(float));
            view_rot->reset();
            escena.scale = 1.0;
            break;
        }
        case SEL_ID: {
            escena.seleccion = sel;
            //GLUI_Master.SetFocus(true);
            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
        case V_SEGUIMIENTO:{

            escena.seleccion = escena.ultimoSelec;

            if(escena.camaraSeguimiento)
            {
                escena.camaraSeguimiento=0;
                escena.seleccion=0;
            }else{
                if(escena.seleccion != 0) //Anulamos las otras vistas
                {
                    escena.camaraSeguimiento=1;
                    escena.vistaAerea=0;
                    escena.primeraPersona=0;
                }
            }
            break;
        }
        case V_AEREA:{
            escena.seleccion = escena.ultimoSelec;

            if(escena.vistaAerea)
            {
                escena.vistaAerea=0;
                escena.seleccion=0;
            }else{
                //Anulamos las otras vistas
                if(escena.seleccion != 0)
                {
                    escena.tipoVista=0;
                    escena.vistaAerea=1;
                    escena.camaraSeguimiento=0;
                    escena.primeraPersona=0;
                }
            }
            break;
        }
        case V_PRIMERAPERSONA:{
            escena.seleccion = escena.ultimoSelec;

            if(escena.primeraPersona)
            {
                escena.primeraPersona=0;
                escena.seleccion=0;
            }
            else{
                if(escena.seleccion != 0)
                {
                    escena.tipoVista=0;
                    escena.primeraPersona=1;
                    escena.vistaAerea=0;
                    escena.camaraSeguimiento=0;
                }
            }
            break;
        }
  } // switch
}

/***************************************** TGui::Idle() ***********/

void __fastcall TGui::Idle( void )
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != window_id )
    glutSetWindow(window_id);

  /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
                                       application  */
    if (enable_panel2)

        glui2->enable();
    else
        glui2->disable();

  glutPostRedisplay();
}

/**************************************** TGui::reshape() *************/

void __fastcall TGui::Reshape( int x, int y )
{
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    glViewport( tx, ty, tw, th );

    escena.xy_aspect = (float)tw / (float)th;
    escena.projectionMatrix = glm::perspective(45.0f, escena.xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(escena.uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(escena.projectionMatrix));

    //std::cout << "xy aspect: " << escena.xy_aspect << std::endl;

    glutPostRedisplay();
}

/***************************************** gui::motion() **********/

void __fastcall TGui::Motion(int x, int y )
{
    glutPostRedisplay();
}

/***************************************** gui::Mouse() **********/

void __fastcall TGui::Mouse(int button, int button_state, int x, int y )
{
    escena.Pick3D(x, y);
}

