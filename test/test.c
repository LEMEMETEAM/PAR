#include "glad/glad.h"
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

    PARContext* ctx = parInit((PARParams){0});
    parSetErrorCallback(ctx, par_error_callback);

    PARShader* vs = parCreateShader(ctx, VERTEX, &vs_source, NULL, 1);
    PARShader* fs = parCreateShader(ctx, FRAGMENT, &fs_source, NULL, 1);
    PARShader* shaders[2] = {vs, fs};
    PARShaderProgram* prog = parCreateShaderProgram(ctx, shaders, 2);

    PARVertexAttrib atts[3] = {{glGetAttribLocation(prog->id, "in_Position"), 3, PAR_FLOAT}, {glGetAttribLocation(prog->id, "in_UV"), 2, PAR_FLOAT}, {glGetAttribLocation(prog->id, "in_Color"), 4, PAR_FLOAT}};
    PARVertexBuffer* vb = parCreateVertexBuffer(ctx, PAR_DYNAMIC, NULL, 27*sizeof(float));
    PARVertexBuffer* vb2 = parCreateVertexBuffer(ctx, PAR_DYNAMIC, NULL, 27*sizeof(float));

    float data[27] = {
        -1, -1, 0,  0, 0,  1, 0, 0, 1,
         1, -1, 0,  1, 0,  0, 1, 0, 1,
         1,  1, 0,  1, 1,  0, 0, 1, 1
    };

    float data2[27] = {
        -1, -1, 0,  0, 0,  1, 0, 0, 1,
        -1,  1, 0,  0, 1,  0, 1, 0, 1,
         1,  1, 0,  1, 1,  0, 0, 1, 1
    };

    parUpdateVertexBuffer(ctx, vb, data, 0, sizeof(data));
    parUpdateVertexBuffer(ctx, vb2, data2, 0, sizeof(data2));
    parApplyVertexBuffer(ctx, vb, atts, 3);
    parApplyVertexBuffer(ctx, vb2, atts, 3);

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
    PARTexture* tex = parCreateTexture(ctx, inf, PAR_TEXTURE_2D);

    while(!glfwWindowShouldClose(win))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        parBindTexture(ctx, tex, 0);
        parBindShaderProgram(ctx, prog);
        parDrawVertexBuffer(ctx, vb, GL_TRIANGLES, 0, 3);
        parDrawVertexBuffer(ctx, vb2, GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(win);
    }

    parDeleteVertexBuffer(ctx, vb);
    parDeleteVertexBuffer(ctx, vb2);

    parDeleteShaderProgram(ctx, prog);
    parDeleteShader(ctx, vs);
    parDeleteShader(ctx, fs);

    parDeleteTexture(ctx, tex);

    parShutdown(ctx);

    return 0;
}
