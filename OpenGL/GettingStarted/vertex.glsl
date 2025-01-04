#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform vec3 offset;
out vec3 ourColor;
void main() {
//    aPos = vec3(aPos.x,aPos.y,aPos.z);
//    gl_Position = vec4(aPos.x,-aPos.y,aPos.z,1.0);
//    gl_Position = vec4(aPos + offset,1.0);
    gl_Position = vec4(aPos,1.0);
    ourColor = aPos;
//    ourColor = aColor;
}
