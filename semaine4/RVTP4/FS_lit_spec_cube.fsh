varying   highp vec3 outPos;
varying   highp vec3 outNormal;

uniform vec3 eye_position;
uniform samplerCube skybox;

void main(void)
{
    vec3 viewdir = normalize(outPos - eye_position);
    vec3 reflect_dir = reflect(viewdir, normalize(outNormal));
    gl_FragColor = textureCube(skybox, reflect_dir);
}
