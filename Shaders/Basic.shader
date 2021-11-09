#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
out gl_PerVertex { vec4 gl_Position; };

void main(){
    gl_Postion = vec4(position);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main(){
    color = vec4(1.0, 0.5, 0.0, 1.0);
};