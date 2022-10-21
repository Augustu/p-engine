#version 430

out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

in vec2 TexCoords;
uniform sampler2D texture_diffuse1;

in vec4 varyingColor;

void main(void)
{
    color =  texture(texture_diffuse1, TexCoords);
    // color = varyingColor;
}