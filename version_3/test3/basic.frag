#version 410 core 


out vec4 color;
in vec4 vertexColor; // The input variable from the vertex shader (same name and same type)



void main()
{
 color = vertexColor;
   
//color = vec4(1,0,0,1.0);
}

//in vec4 vertexColor; // The input variable from the vertex shader (same name and same type)

//out vec4 color;
//out vec4 gl_FragColor;

//void main()
//{
////    color = vertexColor;
//    gl_FragColor =vertexColor;
//}
//



//void main() {
//
//        gl_FragColor = vec4(1,0,0,1.0);
//}


