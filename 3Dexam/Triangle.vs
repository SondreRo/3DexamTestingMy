#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aNormal; // the color variable has attribute position 2
layout (location = 2) in vec3 aColor; // the normal variable has attribute position 1
  
out vec3 ourColor; // output a color to the fragment shader
out vec3 Normal; // output a normal to the fragment shader


uniform mat4 view;
uniform mat4 projection;
uniform mat4 meshMat;



void main()
{
    Normal = normalize(mat3(transpose(inverse(meshMat))) * aNormal);
    gl_Position = projection * view * meshMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //ourColor = aColor; // set ourColor to the input color we got from the vertex data
    ourColor = Normal; // set ourColor to the input color we got from the vertex data
}       