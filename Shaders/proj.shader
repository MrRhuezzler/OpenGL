#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main(){
    vec4 aPos = vec4(position, 1.0f);
    gl_Position = u_Projection * u_View * u_Model  * aPos;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main(){

    // color = vec4(1.0f, 1.0f, 1.0f, 0.5f);
    color = vec4(1.0f);
};