varying highp vec4 outColor;
varying highp vec2 outTexCoord;
varying   highp vec3 outPos;
varying   highp vec3 outNormal;

uniform sampler2D texture0;

uniform highp vec4 light_ambient_color;
uniform highp vec4 light_diffuse_color;
uniform highp vec4 light_specular_color;
uniform highp float light_specular_strength;
uniform highp vec3 light_position;
uniform highp vec3 eye_position;

void main(void)
{
    highp vec4 col1 = outColor;
    highp vec4 col2 = vec4(0.0, 0.0, 0.0, 1.0);

    highp float res = mod(floor(26.0*outTexCoord.s)+floor(10.0*outTexCoord.t), 2.0);
    highp vec4 color = (col1*res + col2*(1.0 - res));

    //calcul de la composante ambiante
    highp vec4 ambient = color * light_ambient_color;

    //calcul de la composante diffuse
    highp vec3 norm = normalize(outNormal);
    highp vec3 lightdir = normalize(light_position - outPos);
    highp float coeff_diffusion = max(dot(lightdir, norm), 0.0);
    highp vec4 diffuse = (coeff_diffusion * light_diffuse_color) * color;

    //calcul de la composante spéculaire
    highp vec3 viewdir = normalize(outPos - eye_position);
    highp vec3 reflectdir = reflect(lightdir, norm);
    highp float coeff_specular = pow(max(dot(viewdir, reflectdir), 0.0), light_specular_strength);
    highp vec4 specular = (coeff_specular * light_specular_color) * vec4(1.0, 1.0, 1.0, 1.0);

    //couleur finale
    gl_FragColor = ambient + diffuse + specular ;
    gl_FragColor.a = outColor.a;

}
