
#version 140

uniform sampler2D fTerrain;
smooth in vec2 fTexCoord;

out vec4 out_Color0;

void main(void)
{	
	vec4 tex = texture(fTerrain, fTexCoord);
	
	//Lightmap stored in alpha channel
	tex.rgb = tex.rgb * tex.a;
	
	out_Color0 = vec4(tex.rgb, 1.0);
}
