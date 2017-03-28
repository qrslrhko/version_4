#version 410 core 


uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;


layout (location = 0) in vec3 position;
out vec4 vertexColor;

void main()
{
//    gl_Position = vec4(position.x, position.y, position.z, 1.0);
//    gl_Position = vec4(position, 1.0);
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);
    vertexColor = vec4(1, 0, 0.3, 1.0);
}


//layout (location = 0) in vec3 position; // The position variable has attribute position 0


//out vec4 vertexColor;
////out vec4 vertexColor; // Specify a color output to the fragment shader
////out vec4 gl_Position;
//
//void main()
//{
////    gl_Position = vec4(position, 1.0); // See how we directly give a vec3 to vec4's constructor
//    gl_Position = ftransform();
//    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // Set the output variable to a dark-red color
//}



// void main(){
//         gl_Position = ftransform();
//     }


