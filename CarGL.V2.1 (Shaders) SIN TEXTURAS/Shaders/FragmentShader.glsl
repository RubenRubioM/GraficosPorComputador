
precision mediump float;	// Precisi�n media

varying vec4 v_Color;		// in: color del vertex shader
varying vec4 v_Luz;        // in: luz calculada del vertex



void main()
{
    gl_FragColor = v_Color;

}
