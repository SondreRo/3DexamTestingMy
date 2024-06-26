#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aNormal; // the color variable has attribute position 1
layout (location = 2) in vec3 aColor; // the normal variable has attribute position 2
layout (location = 3) in vec2 aTextureCoord; // the texturecoord variable has attribute position 3
  
out vec3 ourColor; 



uniform mat4 camMat;
uniform mat4 meshMat;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    TexCoord = aTextureCoord;
    FragPos = vec3(meshMat * vec4(aPos, 1.0));
    Normal = normalize(mat3(transpose(inverse(meshMat))) * aNormal);
    gl_Position = camMat * meshMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //ourColor = aColor; // set ourColor to the input color we got from the vertex data
    ourColor = Normal; // set ourColor to the input color we got from the vertex data
}       