#pragma once

// Native Shader Model 4 programs. Each entry point is a concrete render pass.
// The glow kernels and authored lighting conventions also appear in the
// source-native renderer in zigrebuild/src/graphics/{client,actor}.hlsl.
namespace shaiya::graphics::native {
constexpr char render_shader_source[] = R"HLSL(
cbuffer SceneData : register(b0) {
    row_major float4x4 viewProjection;
    row_major float4x4 view;
    float4 lightAmbient;
    float4 lightDiffuse;
    float4 lightDirection;
    float4 camera;
    float4 fogParameters;
    float4 fogColor;
    float4 clipPlane;
    float4 viewport;
    float4 pointColor;
    float4 pointPositionRange;
    float4 pointAttenuation;
};
cbuffer ObjectData : register(b1) {
    row_major float4x4 world;
    row_major float4x4 reflectionProjection;
    float4 tint;
    float4 materialDiffuse;
    float4 materialAmbient;
    float4 parameters; // alpha cutoff, distortion, reflectivity, post alpha
    float4 uvParameters; // UV offset, source texel size
    float4 specularColor;
    float4 surfaceParameters; // shininess
    float4 emissiveColor;
    row_major float4x4 environmentTransform;
    float4 environmentEye;
    row_major float4x4 textureProjection;
    float4 projectionFlags;
};
cbuffer SkinData : register(b2) { row_major float4x4 bones[256]; };
cbuffer WaterData : register(b3) {
    row_major float4x4 refractionProjection;
    float4 waterColor;
    float4 waterParameters;
    float4 waterOffsets;
};
Texture2D image : register(t0);
Texture2D secondary : register(t1);
Texture2D detailImage : register(t2);
Texture2D secondNormal : register(t3);
SamplerState imageSampler : register(s0);
SamplerState clampSampler : register(s1);
SamplerState wrapSampler : register(s2);
struct Output {
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
    float2 lightmapUv : TEXCOORD1;
    float4 projected : TEXCOORD2;
    float fog : TEXCOORD3;
    float4 color : COLOR0;
    float2 reflectionUv : TEXCOORD4;
    float specular : TEXCOORD5;
    float2 detailUv : TEXCOORD6;
    float4 textureProjected:TEXCOORD9;
    float clipDistance : SV_ClipDistance0;
};
struct WaterOutput {
    float4 position:SV_POSITION;float2 uv:TEXCOORD0;float2 uv1:TEXCOORD1;
    float3 worldPosition:TEXCOORD2;float3 normal:TEXCOORD3;
    float4 reflected:TEXCOORD4;float4 refracted:TEXCOORD5;
    float fog:TEXCOORD6;float clipDistance:SV_ClipDistance0;
};
struct UiInput { float4 position:POSITION; float4 color:COLOR0; float2 uv:TEXCOORD0; };
struct BumpOutput {
    float4 position:SV_POSITION;float2 uv:TEXCOORD0;float3 worldPosition:TEXCOORD1;
    float4 color:COLOR0;float fog:TEXCOORD2;float clipDistance:SV_ClipDistance0;
};
struct UiDualInput {float4 position:POSITION;float4 color:COLOR0;float2 uv:TEXCOORD0;float2 maskUv:TEXCOORD1;};
struct MeshInput { float3 position:POSITION; float3 normal:NORMAL; float4 color:COLOR0; float2 uv:TEXCOORD0; };
struct LightmapInput { float3 position:POSITION; float3 normal:NORMAL; float4 color:COLOR0; float2 uv:TEXCOORD0; float2 lightmapUv:TEXCOORD1; };
struct ModelInput { float3 position:POSITION; float3 normal:NORMAL; float2 uv:TEXCOORD0; };
struct SkinInput { float3 position:POSITION; float weight:BLENDWEIGHT; uint4 indices:BLENDINDICES; float3 normal:NORMAL; float2 uv:TEXCOORD0; };
struct WorldInput { float3 position:POSITION; float4 color:COLOR0; float2 uv:TEXCOORD0; };
struct TexturedWorldInput {float3 position:POSITION;float2 uv:TEXCOORD0;};
struct Multi28Input {float3 position:POSITION;float2 uv:TEXCOORD0;float2 secondaryUv:TEXCOORD1;};
struct Multi36Input {float3 position:POSITION;float2 uv:TEXCOORD0;float2 secondaryUv:TEXCOORD1;float2 detailUv:TEXCOORD2;};
struct Water32Input {float3 position:POSITION;float4 color:COLOR0;float2 uv:TEXCOORD0;float2 reflectionUv:TEXCOORD1;};
struct Water56Input {float3 position:POSITION;float3 normal:NORMAL;float2 uv:TEXCOORD0;float2 uv1:TEXCOORD1;float2 uv2:TEXCOORD2;float2 uv3:TEXCOORD3;};
Output ui_vs(UiInput input) {
    Output output = (Output)0;
    float w = input.position.w == 0 ? 1 : rcp(input.position.w);
    float2 coordinate = input.position.xy + 0.5;
    output.position = float4((coordinate*float2(2,-2)/viewport.xy+float2(-1,1))*w,input.position.z*w,w);
    output.uv = input.uv;
    output.color = input.color.bgra*tint;
    output.fog = output.clipDistance = 1;
    return output;
}
Output ui_dual_vs(UiDualInput input){
    UiInput base;base.position=input.position;base.color=input.color;base.uv=input.uv;
    Output output=ui_vs(base);output.lightmapUv=input.maskUv;return output;
}
Output mesh_vertex(float3 position,float3 normal,float4 color,float2 uv,bool lit) {
    Output output = (Output)0;
    float4 worldPosition = mul(float4(position,1),world);
    output.position = mul(worldPosition,viewProjection);
    output.position.xy += float2(1,-1)/viewport.xy*output.position.w;
    output.uv = uv;
    output.color = color*tint;
    if(lit) {
        float3 worldNormal = normalize(mul(float4(normal,0),world).xyz);
        float3 illumination = lightAmbient.rgb*materialAmbient.rgb+
            lightDiffuse.rgb*materialDiffuse.rgb*max(dot(worldNormal,normalize(-lightDirection.xyz)),0);
        if(pointAttenuation.w>0) {
            float3 toPoint=pointPositionRange.xyz-worldPosition.xyz;
            float distance=length(toPoint);
            float attenuation=pointAttenuation.x+pointAttenuation.y*distance+pointAttenuation.z*distance*distance;
            if(distance<=pointPositionRange.w)
                illumination+=pointColor.rgb*materialDiffuse.rgb*max(dot(worldNormal,toPoint/max(distance,0.000001)),0)/max(attenuation,0.000001);
        }
        output.color.rgb = output.color.rgb*saturate(illumination)+tint.rgb*emissiveColor.rgb;
        output.color.a *= materialDiffuse.a;
    }
    float depth = mul(worldPosition,view).z;
    output.fog = fogParameters.z>0 ? saturate((fogParameters.y-depth)/max(0.0001,fogParameters.y-fogParameters.x)) : 1;
    output.clipDistance = any(clipPlane!=0) ? dot(worldPosition,clipPlane) : 1;
    output.projected = mul(worldPosition,reflectionProjection);
    if(projectionFlags.x>0)output.textureProjected=mul(mul(worldPosition,view),textureProjection);
    return output;
}
Output mesh_vs(MeshInput input) { return mesh_vertex(input.position,input.normal,input.color.bgra,input.uv,false); }
Output world_vs(WorldInput input) { return mesh_vertex(input.position,float3(0,0,0),input.color.bgra,input.uv,false); }
BumpOutput bump_reflect_vs(WorldInput input) {
    BumpOutput output;float4 position=mul(float4(input.position,1),world);
    output.position=mul(position,viewProjection);output.position.xy+=float2(1,-1)/viewport.xy*output.position.w;
    output.worldPosition=position.xyz;output.uv=input.uv+uvParameters.xy;output.color=input.color.bgra*tint;
    float depth=mul(position,view).z;output.fog=fogParameters.z>0?saturate((fogParameters.y-depth)/max(0.0001,fogParameters.y-fogParameters.x)):1;
    output.clipDistance=any(clipPlane!=0)?dot(position,clipPlane):1;return output;
}
Output textured_world_vs(TexturedWorldInput input) { return mesh_vertex(input.position,float3(0,0,0),float4(1,1,1,1),input.uv,false); }
Output multi28_vs(Multi28Input input) {
    Output output=mesh_vertex(input.position,float3(0,0,0),float4(1,1,1,1),input.uv,false);
    output.lightmapUv=input.secondaryUv;return output;
}
Output multi36_vs(Multi36Input input) {
    Output output=mesh_vertex(input.position,float3(0,0,0),float4(1,1,1,1),input.uv,false);
    output.lightmapUv=input.secondaryUv;output.detailUv=input.detailUv;return output;
}
Output lit_vs(MeshInput input) { return mesh_vertex(input.position,input.normal,input.color.bgra,input.uv,true); }
Output lightmap_vs(LightmapInput input) {
    Output output = mesh_vertex(input.position,input.normal,input.color.bgra,input.uv,false);
    output.lightmapUv = input.lightmapUv;
    return output;
}
Output model_vs(ModelInput input) { return mesh_vertex(input.position,input.normal,float4(1,1,1,1),input.uv,true); }
Output water32_vs(Water32Input input){return mesh_vertex(input.position,float3(0,1,0),input.color.bgra,input.uv,false);}
WaterOutput water56_vs(Water56Input input){
    WaterOutput output;float4 position=mul(float4(input.position,1),world);
    output.position=mul(position,viewProjection);output.position.xy+=float2(1,-1)/viewport.xy*output.position.w;
    output.worldPosition=position.xyz;output.normal=normalize(mul(float4(input.normal,0),world).xyz);
    output.uv=input.uv+waterOffsets.xy;output.uv1=input.uv1+waterOffsets.zw;
    output.reflected=mul(position,reflectionProjection);output.refracted=mul(position,refractionProjection);
    float depth=mul(position,view).z;output.fog=fogParameters.z>0?saturate((fogParameters.y-depth)/max(0.0001,fogParameters.y-fogParameters.x)):1;
    output.clipDistance=any(clipPlane!=0)?dot(position,clipPlane):1;return output;
}
Output unlit_model_vs(ModelInput input) { return mesh_vertex(input.position,input.normal,float4(1,1,1,1),input.uv,false); }
void reflection_vertex(inout Output output,float3 position,float3 normal) {
    float3 worldPosition = mul(float4(position,1),world).xyz;
    float3 worldNormal = normalize(mul(float4(normal,0),world).xyz);
    float3 toEye = normalize(camera.xyz-worldPosition);
    float3 halfVector = normalize(toEye-normalize(lightDirection.xyz));
    output.specular = specularColor.r*pow(max(dot(worldNormal,halfVector),0),max(surfaceParameters.x,0.0001));
    float3 viewPosition = surfaceParameters.w>0?mul(float4(worldPosition,1),environmentTransform).xyz:mul(float4(worldPosition,1),view).xyz;
    float3 viewNormal = normalize(surfaceParameters.w>0?mul(float4(worldNormal,0),environmentTransform).xyz:mul(float4(worldNormal,0),view).xyz);
    float3 towardEye=surfaceParameters.w>0?normalize(environmentEye.xyz-viewPosition):normalize(-viewPosition);
    float3 reflected = reflect(-towardEye,viewNormal);
    float divisor = sqrt(max(0.000001,0.5-0.5*reflected.z));
    output.reflectionUv = (reflected.xy*(0.25/divisor)+0.5)*float2(1,-1);
}
Output reflective_model_vs(ModelInput input) {
    Output output = model_vs(input);
    reflection_vertex(output,input.position,input.normal);
    return output;
}
Output skin_vs(SkinInput input) {
    float4 position = mul(float4(input.position,1),bones[input.indices.x])*input.weight+
        mul(float4(input.position,1),bones[input.indices.y])*(1-input.weight);
    float3 normal = mul(float4(input.normal,0),bones[input.indices.x]).xyz*input.weight+
        mul(float4(input.normal,0),bones[input.indices.y]).xyz*(1-input.weight);
    return mesh_vertex(position.xyz,normal,float4(1,1,1,1),input.uv,true);
}
Output reflective_skin_vs(SkinInput input) {
    float4 position = mul(float4(input.position,1),bones[input.indices.x])*input.weight+
        mul(float4(input.position,1),bones[input.indices.y])*(1-input.weight);
    float3 normal = mul(float4(input.normal,0),bones[input.indices.x]).xyz*input.weight+
        mul(float4(input.normal,0),bones[input.indices.y]).xyz*(1-input.weight);
    Output output = mesh_vertex(position.xyz,normal,float4(1,1,1,1),input.uv,true);
    reflection_vertex(output,position.xyz,normal);
    return output;
}
float2 surface_uv(Output input){return projectionFlags.x>0?input.textureProjected.xy/input.textureProjected.w:input.uv;}
float4 finish_surface(float4 color,Output input) {
    clip(color.a-parameters.x);
    color.rgb = lerp(fogColor.rgb,color.rgb,input.fog);
    return color;
}
float4 ui_ps(Output input):SV_TARGET {
    float4 color = image.Sample(imageSampler,input.uv)*input.color;
    clip(color.a-parameters.x);
    return color;
}
float4 mask_ps(Output input):SV_TARGET {
    float4 color = image.Sample(imageSampler,input.uv)*input.color;
    color.a *= secondary.Sample(imageSampler,input.uv).a;
    clip(color.a-parameters.x);
    return color;
}
float4 ui_dual_ps(Output input):SV_TARGET {
    float4 color=image.Sample(imageSampler,input.uv)*input.color;
    float4 mask=secondary.Sample(imageSampler,input.lightmapUv);
    color.a*=mask.a;if(surfaceParameters.z>0)color.rgb=mask.rgb;
    clip(color.a-parameters.x);return color;
}
float4 surface_ps(Output input):SV_TARGET { return finish_surface(image.Sample(imageSampler,surface_uv(input))*input.color,input); }
float4 reflection_ps(Output input):SV_TARGET {
    float4 base = image.Sample(imageSampler,surface_uv(input));
    float3 environment = secondary.Sample(imageSampler,input.reflectionUv).rgb;
    return finish_surface(float4(base.rgb*input.color.rgb+environment*base.a*input.specular,tint.a),input);
}
float4 lightmap_ps(Output input):SV_TARGET {
    float4 color = image.Sample(imageSampler,surface_uv(input))*input.color;
    color.rgb *= secondary.Sample(clampSampler,input.lightmapUv).rgb;
    return finish_surface(color,input);
}
float4 material_layers(Output input,bool detail,int blend) {
    float4 base=image.Sample(imageSampler,surface_uv(input));
    float3 rgb=surfaceParameters.y>0?base.rgb:float3(1,1,1);
    float3 second=secondary.Sample(wrapSampler,input.lightmapUv).rgb;
    if(blend==1)rgb=second;
    else if(blend==2)rgb=saturate(rgb+second-0.5);
    else rgb*=second;
    if(detail)rgb*=detailImage.Sample(imageSampler,input.detailUv).rgb;
    return finish_surface(float4(rgb*input.color.rgb,base.a*input.color.a),input);
}
float4 multi28_ps(Output input):SV_TARGET{return material_layers(input,false,0);}
float4 replace28_ps(Output input):SV_TARGET{return material_layers(input,false,1);}
float4 signed28_ps(Output input):SV_TARGET{return material_layers(input,false,2);}
float4 multi36_ps(Output input):SV_TARGET{return material_layers(input,true,0);}
float4 replace36_ps(Output input):SV_TARGET{return material_layers(input,true,1);}
float4 signed36_ps(Output input):SV_TARGET{return material_layers(input,true,2);}
float4 water_ps(Output input):SV_TARGET {
    float2 uv = input.projected.xy/input.projected.w;
    uv += image.Sample(imageSampler,input.uv+uvParameters.xy).rg*parameters.y;
    float3 reflection = secondary.Sample(clampSampler,uv).rgb;
    return finish_surface(float4(lerp(input.color.rgb,reflection,parameters.z),input.color.a),input);
}
float4 projected_shadow_ps(Output input):SV_TARGET {
    float2 uv=input.projected.xy/input.projected.w;
    clip(uv);clip(1-uv);
    return finish_surface(float4(0,0,0,image.Sample(clampSampler,uv).a*parameters.z),input);
}
float4 projected_effect_ps(Output input):SV_TARGET {
    float2 uv=input.projected.xy/input.projected.w;
    clip(uv);clip(1-uv);
    return finish_surface(image.Sample(clampSampler,uv),input);
}
float4 water56_ps(WaterOutput input):SV_TARGET {
    float3 first=image.Sample(imageSampler,input.uv).xyz;
    float3 second=secondNormal.Sample(imageSampler,input.uv1).xyz;
    if(waterParameters.w<0.5){first=first*2-1;second=second*2-1;}
    float3 normal=normalize(input.normal+float3(first.x+second.x,0,first.y+second.y)*0.5);
    float2 distortion=(first.xy+second.xy)*waterParameters.x*0.5;
    float2 reflectedUv=input.reflected.xy/input.reflected.w+distortion;
    float2 refractedUv=input.refracted.xy/input.refracted.w-distortion;
    float fresnel=waterParameters.y+(1-waterParameters.y)*pow(1-saturate(dot(normal,normalize(camera.xyz-input.worldPosition))),5);
    float3 reflected=secondary.Sample(clampSampler,reflectedUv).rgb;
    float3 refracted=detailImage.Sample(clampSampler,refractedUv).rgb*waterColor.rgb;
    float4 color=float4(lerp(refracted,reflected,saturate(fresnel))*tint.rgb,waterParameters.z*tint.a);
    clip(color.a-parameters.x);color.rgb=lerp(fogColor.rgb,color.rgb,input.fog);return color;
}
float4 bump_reflect_ps(BumpOutput input):SV_TARGET {
    float3 sampled=image.Sample(imageSampler,input.uv).xyz*2-1;
    float3 normal=normalize(mul(float4(sampled.x,sampled.z,sampled.y,0),world).xyz);
    float3 eye=mul(float4(0,0,0,1),environmentTransform).xyz;
    float3 towardEye=normalize(eye-input.worldPosition);
    float3 reflected=reflect(-towardEye,normal);
    float divisor=sqrt(max(0.000001,0.5-0.5*reflected.z));
    float2 environmentUv=(reflected.xy*(0.25/divisor)+0.5)*float2(1,-1);
    float illumination=0.25+0.75*saturate(dot(normal,normalize(environmentEye.xyz-input.worldPosition)));
    float4 color=float4(secondary.Sample(imageSampler,environmentUv).rgb*illumination*input.color.rgb,input.color.a);
    clip(color.a-parameters.x);color.rgb=lerp(fogColor.rgb,color.rgb,input.fog);return color;
}
Output fullscreen_vs(uint id:SV_VertexID) {
    Output output = (Output)0;
    output.uv = float2((id<<1)&2,id&2);
    output.position = float4(output.uv*float2(2,-2)+float2(-1,1),0,1);
    output.color = float4(1,1,1,parameters.w);
    output.fog = output.clipDistance = 1;
    return output;
}
float4 copy_ps(Output input):SV_TARGET { return float4(image.Sample(imageSampler,input.uv).rgb,parameters.w); }
float4 gamma_ps(Output input):SV_TARGET { return float4(pow(saturate(image.Sample(imageSampler,input.uv).rgb),parameters.yyy),1); }
float4 eight_tap_ps(Output input):SV_TARGET {
    float3 sum = 0;
    [unroll] for(int x=0;x<2;++x) {
        [unroll] for(int y=0;y<4;++y) {
            float2 offset = float2(x==0?-1:3,y==0?-1:(y==1?-3:(y==2?1:3)));
            sum += image.Sample(imageSampler,input.uv+offset*uvParameters.zw).rgb;
        }
    }
    return float4(sum/6,parameters.w);
}
float4 gaussian(Output input,float2 axis) {
    static const float weights[7] = {1.0/64,6.0/64,15.0/64,20.0/64,15.0/64,6.0/64,1.0/64};
    float3 sum = 0;
    [unroll] for(int i=0;i<7;++i)
        sum += image.Sample(imageSampler,input.uv+(i-3)*axis*uvParameters.zw).rgb*weights[i];
    return float4(sum,parameters.w);
}
float4 gaussian_x_ps(Output input):SV_TARGET { return gaussian(input,float2(1,0)); }
float4 gaussian_y_ps(Output input):SV_TARGET { return gaussian(input,float2(0,1)); }
)HLSL";
} // namespace shaiya::graphics::native
