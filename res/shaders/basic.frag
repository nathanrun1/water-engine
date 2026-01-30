#version 460

in vec2 texCoord;

out vec4 fragColor;

void main() {
    fragColor = vec4(mix(vec2(0.0), vec2(1.0), texCoord), 0.5, 1.0);
}