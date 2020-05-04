#define PAR_GL2_IMPLEMENTATION
#include "../src/PAR.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <stdint.h>

static const char* vs_source =
    "#version 110\n"
    "attribute vec3 in_Position;\n"
    "attribute vec2 in_UV;\n"
    "attribute vec4 in_Color;\n"
    "\n"
    "varying vec3 out_Position;\n"
    "varying vec2 out_UV;\n"
    "varying vec4 out_Color;\n"
    "void main()\n"
    "{\n"
        "gl_Position = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);\n"
        "out_Position = in_Position;\n"
        "out_UV = in_UV;\n"
        "out_Color = in_Color;\n"
    "}\0";
static const char* fs_source =
    "#version 110\n"
    "varying vec3 out_Position;\n"
    "varying vec2 out_UV;\n"
    "varying vec4 out_Color;\n"
    "uniform sampler2D tex;\n"
    "void main()\n"
    "{\n"
        "vec4 tc = texture2D(tex, out_UV);\n"
        "gl_FragColor = vec4(tc.rgb * out_Color.rgb, 1);\n"
    "}\0";

void par_error_callback(const char* error, int size)
{
    printf("%s", error);
}

int main()
{
    if(!glfwInit())
    {
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* win = glfwCreateWindow(800, 600, "test", 0, 0);

    glfwMakeContextCurrent(win);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return 1;
    }

    glfwShowWindow(win);

    parInit((PARParams){0});

    PARShader* vs = parCreateShader(VERTEX, &vs_source, NULL, 1);
    PARShader* fs = parCreateShader(FRAGMENT, &fs_source, NULL, 1);
    PARShader* shaders[2] = {vs, fs};
    PARShaderProgram* prog = parCreateShaderProgram(shaders, 2);

    PARVertexAttrib atts[3] = {{glGetAttribLocation(prog->id, "in_Position"), 3, PAR_FLOAT}, {glGetAttribLocation(prog->id, "in_UV"), 2, PAR_FLOAT}, {glGetAttribLocation(prog->id, "in_Color"), 4, PAR_FLOAT}};
    PARBuffer* vb = parCreateBuffer(PAR_VERTEX_BUFFER, PAR_DYNAMIC, NULL, 27*sizeof(float));
    PARBuffer* ib = parCreateBuffer(PAR_INDEX_BUFFER, PAR_DYNAMIC, NULL, 27*sizeof(float));

    float vb_data[36] = {
        -1, -1, 0,  0, 0,  1, 0, 0, 1,
         1, -1, 0,  1, 0,  0, 1, 0, 1,
         1,  1, 0,  1, 1,  0, 0, 1, 1
        -1,  1, 0,  0, 1,  1, 1, 0, 1
    };

    float ib_data[6] = {
        0, 1, 2,
        2, 3, 0
    }

    parUpdateBuffer(vb, vb_data, 0, sizeof(vb_data));
    parUpdateBuffer(ib, ib_data, 0, sizeof(ib_data));

    PARPipelineParams p_params = {0};
    p_params.attributes = atts;
    p_params.attributes_count = 3;
    p_params.shader = prog;
    PARPipeline *p = parCreatePipeline(p_params);

    uint32_t tex_data[3*3] = {
        0xFFFFFF, 0x000000, 0xFFFFFF,
        0x000000, 0xFFFFFF, 0x000000,
        0xFFFFFF, 0x000000, 0xFFFFFF
    };

    // unsigned char tex_data[3*3*3] = {
    //     0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
    //     0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    //     0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF
    // };

    PARTextureInfo inf = {tex_data, PAR_PIXEL_FORMAT_RGBA8, 3, 3, 0, {{PAR_TEXTURE_MIN_FILTER, PAR_NEAREST}, {PAR_TEXTURE_MAG_FILTER, PAR_NEAREST}}, 2};
    PARTexture* tex = parCreateTexture(inf, PAR_TEXTURE_2D);

    while(!glfwWindowShouldClose(win))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        parBindTexture(tex, 0);
        parBindShaderProgram(prog);
        parDraw(r1, GL_TRIANGLES, 0, 3);
        parDraw(r2, GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(win);
    }
    
    parFreeDrawBuffers(r1);
    parFreeDrawBuffers(r2);

    parDeleteBuffer(vb);
    parDeleteBuffer(vb2);

    parDeleteShaderProgram(prog);
    parDeleteShader(vs);
    parDeleteShader(fs);

    parDeleteTexture(tex);

    parShutdown(ctx);

    return 0;
}
