varying highp vec3 outTexCoord;
uniform samplerCube texture0;

void main(void)
{
    gl_FragColor = textureCube(texture0, outTexCoord);
    gl_FragColor.a = 1.0;
}
