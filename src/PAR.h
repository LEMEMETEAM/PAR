#ifndef PAR_H_
    #define PAR_H_

    #ifdef _cplusplus
        extern "C"
        {
    #endif
        typedef struct PARParams
        {
            void* d3d11_device;
            void* d3d11_device_context;
        } PARParams;

        typedef void (*PARErrorCallback)(const char* error, int length);

        typedef struct PARContext
        {
            void* usr_ptr;
            PARErrorCallback error;

            void* d3d10_device;
            void* d3d10_device_ctx;
        } PARContext;

        typedef enum
        {
            PAR_BYTE,
            PAR_UNSIGNED_BYTE,
            PAR_SHORT,
            PAR_UNSIGNED_SHORT,
            PAR_HALF_FLOAT,
            PAR_INT,
            PAR_UNSIGNED_INT,
            PAR_FIXED,
            PAR_FLOAT,
            PAR_DOUBLE
        } PARDataType;

        typedef struct PARVertexAttrib
        {
            int position, size;
            PARDataType format;
        } PARVertexAttrib;
        typedef enum PARVertexBufferType
        {
            PAR_STATIC,
            PAR_DYNAMIC
        } PARVertexBufferType;
        struct PARVertexBufferImplData;
        typedef struct PARVertexBuffer {
            int stride;
            PARVertexAttrib* attribs;
            int attribs_size;
            PARVertexBufferType vb_type;
            int size;
            struct PARVertexBufferImplData* impl_data;
        } PARVertexBuffer;

        typedef enum PARShaderType
        {
            VERTEX,
            FRAGMENT,
            GEOMETRY
        } PARShaderType;
        struct PARUniform
        {
            int location;
            int size;
            PARDataType type;
        };
        typedef struct PARShader {unsigned int id;} PARShader;
        typedef struct PARShaderProgram
        {
            unsigned int id;
            struct PARUniform* uniforms;
        } PARShaderProgram;

        typedef struct PARTexture {unsigned int id; int target;} PARTexture;
      	typedef enum
      	{
      		PAR_TEXTURE_1D,
      		PAR_TEXTURE_2D,
      		PAR_TEXTURE_3D
      	} PARTextureType;
        typedef enum
        {
            PAR_PIXEL_FORMAT_DEPTH16,
            PAR_PIXEL_FORMAT_DEPTH24,
            PAR_PIXEL_FORMAT_DEPTH32F,

            PAR_PIXEL_FORMAT_DEPTH24_STENCIL8,
            PAR_PIXEL_FORMAT_DEPTH32F_STENCIL8,

            PAR_PIXEL_FORMAT_R8,
            PAR_PIXEL_FORMAT_R16,
            PAR_PIXEL_FORMAT_R8_SNORM,
            PAR_PIXEL_FORMAT_R16_SNORM,
            PAR_PIXEL_FORMAT_R16F,
            PAR_PIXEL_FORMAT_R32F,
            PAR_PIXEL_FORMAT_R8I,
            PAR_PIXEL_FORMAT_R16I,
            PAR_PIXEL_FORMAT_R32I,
            PAR_PIXEL_FORMAT_R8UI,
            PAR_PIXEL_FORMAT_R16UI,
            PAR_PIXEL_FORMAT_R32UI,

            PAR_PIXEL_FORMAT_RG8,
            PAR_PIXEL_FORMAT_RG16,
            PAR_PIXEL_FORMAT_RG8_SNORM,
            PAR_PIXEL_FORMAT_RG16_SNORM,
            PAR_PIXEL_FORMAT_RG16F,
            PAR_PIXEL_FORMAT_RG32F,
            PAR_PIXEL_FORMAT_RG8I,
            PAR_PIXEL_FORMAT_RG16I,
            PAR_PIXEL_FORMAT_RG32I,
            PAR_PIXEL_FORMAT_RG8UI,
            PAR_PIXEL_FORMAT_RG16UI,
            PAR_PIXEL_FORMAT_RG32UI,

            PAR_PIXEL_FORMAT_RGB8,
            PAR_PIXEL_FORMAT_RGB16,
            PAR_PIXEL_FORMAT_RGB8_SNORM,
            PAR_PIXEL_FORMAT_RGB16_SNORM,
            PAR_PIXEL_FORMAT_RGB16F,
            PAR_PIXEL_FORMAT_RGB32F,
            PAR_PIXEL_FORMAT_RGB8I,
            PAR_PIXEL_FORMAT_RGB16I,
            PAR_PIXEL_FORMAT_RGB32I,
            PAR_PIXEL_FORMAT_RGB8UI,
            PAR_PIXEL_FORMAT_RGB16UI,
            PAR_PIXEL_FORMAT_RGB32UI,

            PAR_PIXEL_FORMAT_RGBA8,
            PAR_PIXEL_FORMAT_RGBA16,
            PAR_PIXEL_FORMAT_RGBA8_SNORM,
            PAR_PIXEL_FORMAT_RGBA16_SNORM,
            PAR_PIXEL_FORMAT_RGBA16F,
            PAR_PIXEL_FORMAT_RGBA32F,
            PAR_PIXEL_FORMAT_RGBA8I,
            PAR_PIXEL_FORMAT_RGBA16I,
            PAR_PIXEL_FORMAT_RGBA32I,
            PAR_PIXEL_FORMAT_RGBA8UI,
            PAR_PIXEL_FORMAT_RGBA16UI,
            PAR_PIXEL_FORMAT_RGBA32UI,

            PAR_PIXEL_FORMAT_SRGB8,
            PAR_PIXEL_FORMAT_RGB9_E5,
            PAR_PIXEL_FORMAT_SRGB8_ALPHA8,
            PAR_PIXEL_FORMAT_RGB10_A2,
            PAR_PIXEL_FORMAT_RGB10_A2UI,
            PAR_PIXEL_FORMAT_R11F_G11F_B10F
        } PARTextureFormat;
        typedef enum
        {
            PAR_TEXTURE_MIN_FILTER,
            PAR_TEXTURE_MAG_FILTER,
            PAR_TEXTURE_WRAP_S,
            PAR_TEXTURE_WRAP_T,
            PAR_TEXTURE_WRAP_R,

            PAR_TEXTURE_PARAMETER_COUNT
        } PARTextureParameter;
        typedef enum
        {
            PAR_NEAREST,
            PAR_LINEAR,
            PAR_CLAMP_TO_EDGE,
            PAR_CLAMP_TO_BORDER,
            PAR_MIRRORED_REPEAT,
            PAR_REPEAT
        } PARTextureParamValue;
        typedef struct PARTextureParamsPair
        {
            PARTextureParameter param;
            PARTextureParamValue value;
        } PARTextureParamsPair;
        typedef struct PARTextureInfo
        {
            void* data;
            PARTextureFormat format;
            int width, height, depth;
            PARTextureParamsPair params[PAR_TEXTURE_PARAMETER_COUNT];
            int params_count;
        } PARTextureInfo;
        typedef struct PARFramebuffer
        {

        } PARFramebuffer;

        /**************************
         * FUNCTIONS              *
         **************************/

        PARContext* parInit(PARParams params);
        void parShutdown(PARContext* ctx);
        void parSetErrorCallback(PARContext* ctx, PARErrorCallback error);

        PARVertexBuffer* parCreateVertexBuffer(PARContext* ctx, PARVertexBufferType type, void* data, int data_size);
        void parUpdateVertexBuffer(PARContext* ctx, PARVertexBuffer* b, void* data, int offset, int size);
        void parAppendVertexBuffer(PARContext* ctx, PARVertexBuffer* b, void* data, int size);
        void parApplyVertexBuffer(PARContext* ctx, PARVertexBuffer* vb, PARVertexAttrib* att, int att_size);
        void parDrawVertexBuffer(PARContext* ctx, PARVertexBuffer* b, unsigned int primitive, int start, int count);
        void parDeleteVertexBuffer(PARContext* ctx, PARVertexBuffer* vb);

        PARShader* parCreateShader(PARContext* ctx, PARShaderType type, const char** strings, const int* length, int count);
        void parDeleteShader(PARContext* ctx, PARShader* shader);
        PARShaderProgram* parCreateShaderProgram(PARContext* ctx, PARShader** shaders, int count);
        void parSetUniform(PARContext* ctx, PARShaderProgram* prog, const char* name, void* data, int size, char type);
        void parBindShaderProgram(PARContext* ctx, PARShaderProgram* prog);
        void parDeleteShaderProgram(PARContext* ctx, PARShaderProgram* prog);

    	PARTexture* parCreateTexture(PARContext* ctx, PARTextureInfo info, PARTextureType type);
    	void parBindTexture(PARContext* ctx, PARTexture* tex, int unit);
    	void parDeleteTexture(PARContext* ctx, PARTexture* tex);
    #ifdef _cplusplus
        }
    #endif

#endif //PAR_H_

#if defined(PAR_GL2_IMPLEMENTATION) || defined(PAR_GL3_IMPLEMENTATION) || defined(PAR_D3D11_IMPLEMENTATION)
    #include <stdlib.h>

    PARContext* parInit(PARParams params)
    {
        PARContext* ctx = malloc(sizeof(PARContext));
        ctx->usr_ptr = NULL;
        ctx->error = NULL;

        ctx->d3d10_device = params.d3d11_device;
        ctx->d3d10_device_ctx = params.d3d11_device_context;

        return ctx;
    }

    void parShutdown(PARContext* ctx)
    {
        if(ctx->usr_ptr) ctx->usr_ptr = NULL;
        if(ctx->error) ctx->error = NULL;

        if(ctx->d3d10_device) ctx->d3d10_device = NULL;
        if(ctx->d3d10_device_ctx) ctx->d3d10_device_ctx = NULL;

        free(ctx);
    }

    void parSetErrorCallback(PARContext* ctx, PARErrorCallback error)
    {
        ctx->error = error;
    }

    #if defined(PAR_GL2_IMPLEMENTATION) || defined(PAR_GL3_IMPLEMENTATION)
        struct PARVertexBufferImplData
        {
            int vbo;
            #ifdef PAR_GL3_IMPLEMENTATION
                int vao;
            #endif
        };

        PARVertexBuffer* parCreateVertexBuffer(PARContext* ctx, PARVertexBufferType type, void* data, int data_size)
        {
            PARVertexBuffer* vb = malloc(sizeof(PARVertexBuffer));

            struct PARVertexBufferImplData* id = malloc(sizeof(struct PARVertexBufferImplData));

            #ifdef PAR_GL3_IMPLEMENTATION
                glGenVertexArrays(1, &id->vao);
            #endif

            glGenBuffers(1, &id->vbo);
            glBindBuffer(GL_ARRAY_BUFFER, id->vbo);

            if(type == PAR_STATIC)
            {
                glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
            }
            else if(type == PAR_DYNAMIC)
            {
                glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_DYNAMIC_DRAW);
            }

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            vb->stride = 0;
            vb->attribs = NULL;
            vb->vb_type = type;
            vb->impl_data = id;
            vb->size = data_size;

            return vb;
        }

        void parUpdateVertexBuffer(PARContext* ctx, PARVertexBuffer* b, void* data, int offset, int size)
        {
            if(b->vb_type == PAR_DYNAMIC)
            {
                glBindBuffer(GL_ARRAY_BUFFER, b->impl_data->vbo);
                glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

        }

        void parAppendVertexBuffer(PARContext* ctx, PARVertexBuffer* b, void* data, int size)
        {
            if(b->vb_type == PAR_DYNAMIC)
            {
                    glBindBuffer(GL_ARRAY_BUFFER, b->impl_data->vbo);
                    void* old_data;
                    glGetBufferSubData(GL_ARRAY_BUFFER, 0, b->size, old_data);
                    glBufferData(GL_ARRAY_BUFFER, b->size + size, old_data, GL_DYNAMIC_DRAW);
                    glBufferSubData(GL_ARRAY_BUFFER, b->size, size, data);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);

                    b->size += size;
            }
        }

        static int gl_parGetGLTypeSize(PARDataType type)
        {
            switch(type)
            {
                case PAR_BYTE: case PAR_UNSIGNED_BYTE: return 1;
                case PAR_SHORT: case PAR_UNSIGNED_SHORT: case PAR_HALF_FLOAT: return 2;
                case PAR_INT: case PAR_UNSIGNED_INT: case PAR_FIXED: case PAR_FLOAT: return 4;
                case PAR_DOUBLE: return 8;
            }
        }

        static int gl_parToGLType(PARDataType type)
        {
            switch(type)
            {
                case PAR_BYTE: return GL_BYTE;
                case PAR_UNSIGNED_BYTE: return GL_UNSIGNED_BYTE;
                case PAR_SHORT: return GL_SHORT;
                case PAR_UNSIGNED_SHORT: return GL_UNSIGNED_SHORT;
                case PAR_HALF_FLOAT: return GL_HALF_FLOAT;
                case PAR_INT: return GL_INT;
                case PAR_UNSIGNED_INT: return GL_UNSIGNED_INT;
                case PAR_FIXED: return GL_FIXED;
                case PAR_FLOAT: return GL_FLOAT;
                case PAR_DOUBLE: return GL_DOUBLE;
            }
        }

        void parApplyVertexBuffer(PARContext* ctx, PARVertexBuffer* vb, PARVertexAttrib* att, int att_size)
        {
            #ifdef PAR_GL2_IMPLEMENTATION
                int stride = 0;
                for(int i = 0; i < att_size; i++)
                {
                    PARVertexAttrib a = att[i];
                    stride += a.size;
                }

                vb->stride = stride;
                vb->attribs = att;
                vb->attribs_size = att_size;
            #elif defined(PAR_GL3_IMPLEMENTATION)
                int stride = 0;
                for(int i = 0; i < att_size; i++)
                {
                    PARVertexAttrib a = att[i];
                    stride += a.size;
                }

                vb->stride = stride;
                vb->attribs = att;

                glBindBuffer(GL_ARRAY_BUFFER, vb->impl_data->vbo);

                glBindVertexArray(vb->impl_data->vao);

                int offset = 0;

                for(int i = 0; i < att_size; i++)
                {
                    PARVertexAttrib a = att[i];
                    glVertexAttribPointer(a.position, a.size, gl_parToGLType(a.format), GL_FALSE, stride * gl_parGetGLTypeSize(a.format), (void*)(offset*gl_parGetGLTypeSize(a.format)));
                    glEnableVertexAttribArray(a.position);
                    offset += a.size;
                }

                glBindVertexArray(0);

                glBindBuffer(GL_ARRAY_BUFFER, 0);
            #endif
        }

        void parDrawVertexBuffer(PARContext* ctx, PARVertexBuffer* b, unsigned int primitive, int start, int count)
        {
            #ifdef PAR_GL2_IMPLEMENTATION
                glBindBuffer(GL_ARRAY_BUFFER, b->impl_data->vbo);

                int offset = 0;

                for(int i = 0; i < b->attribs_size; i++)
                {
                    PARVertexAttrib a = b->attribs[i];
                    glVertexAttribPointer(a.position, a.size, gl_parToGLType(a.format), GL_FALSE, b->stride * gl_parGetGLTypeSize(a.format), (void*)(offset*gl_parGetGLTypeSize(a.format)));
                    glEnableVertexAttribArray(a.position);
                    offset += a.size;
                }

                glDrawArrays(primitive, start, count);

                for(int i = 0; i < b->attribs_size; i++)
                {
                    PARVertexAttrib a = b->attribs[i];
                    glDisableVertexAttribArray(a.position);
                }

                glBindBuffer(GL_ARRAY_BUFFER, 0);
            #elif defined(PAR_GL3_IMPLEMENTATION)
                glBindVertexArray(b->impl_data->vao);
                glDrawArrays(primitive, start, count);
                glBindVertexArray(0);
            #endif
        }

        void parDeleteVertexBuffer(PARContext* ctx, PARVertexBuffer* vb)
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDeleteBuffers(1, &vb->impl_data->vbo);

            #ifdef PAR_GL3_IMPLEMENTATION
                glBindVertexArray(0);
                glDeleteVertexArrays(1, &vb->impl_data->vao);
            #endif

            vb->stride = 0;
            vb->attribs = NULL;

            free(vb->impl_data);
            vb->impl_data = NULL;

            free(vb);
        }

        PARShader* parCreateShader(PARContext* ctx, PARShaderType type, const char** strings, const int* length, int count)
        {
            PARShader* shader = malloc(sizeof(PARShader));

            if(type == VERTEX)
            {
                shader->id = glCreateShader(GL_VERTEX_SHADER);
            }
            else if(type == FRAGMENT)
            {
                shader->id = glCreateShader(GL_FRAGMENT_SHADER);
            }
            #ifdef PAR_GL3_IMPLEMENTATION
                else if(type == GEOMETRY)
                {
                    shader->id = glCreateShader(GL_GEOMETRY_SHADER);
                }
            #endif
            glShaderSource(shader->id, count, strings, length);
            glCompileShader(shader->id);
            /*check for shader compile errors*/
            int success;
            int logLength;
            glGetShaderiv(shader->id, GL_INFO_LOG_LENGTH, &logLength);
            char infoLog[logLength];
            int err_length;
            glGetShaderiv(shader->id, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader->id, logLength, &err_length, infoLog);
                ctx->error(infoLog, err_length);
            }

            return shader;
        }

        void parDeleteShader(PARContext* ctx, PARShader* shader)
        {
            glDeleteShader(shader->id);

            free(shader);
        }

        PARShaderProgram* parCreateShaderProgram(PARContext* ctx, PARShader** shaders, int count)
        {
            PARShaderProgram* sp = malloc(sizeof(PARShaderProgram));

            sp->id = glCreateProgram();
            for(int i = 0; i < count; i++)
            {
                glAttachShader(sp->id, shaders[i]->id);
            }

            glLinkProgram(sp->id);

            int success;
            int logLength;
            glGetProgramiv(sp->id, GL_INFO_LOG_LENGTH, &logLength);
            char infoLog[logLength];
            int err_length;
            glGetProgramiv(sp->id, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(sp->id, logLength, &err_length, infoLog);
                ctx->error(infoLog, err_length);
            }

            glValidateProgram(sp->id);

            for(int i = 0; i < count; i++)
            {
                glDetachShader(sp->id, shaders[i]->id);
            }

            return sp;
        }

        void parSetUniform(PARContext* ctx, PARShaderProgram* prog, const char* name, void* data, int size, const char type)
        {
            int loc = glGetUniformLocation(prog->id, name);
            if(type == 'f')
            {
                if(size == 1)
                {
                    glUniform1fv(loc, 1, (const GLfloat*)data);
                }
                else if(size == 2)
                {
                    glUniform2fv(loc, 1, (const GLfloat*)data);
                }
                else if(size == 3)
                {
                    glUniform3fv(loc, 1, (const GLfloat*)data);
                }
                else if(size == 4)
                {
                    glUniform4fv(loc, 1, (const GLfloat*)data);
                }
            }
            else if(type == 'i')
            {
                if(size == 1)
                {
                    glUniform1iv(loc, 1, (const GLint*)data);
                }
                else if(size == 2)
                {
                    glUniform2iv(loc, 1, (const GLint*)data);
                }
                else if(size == 3)
                {
                    glUniform3iv(loc, 1, (const GLint*)data);
                }
                else if(size == 4)
                {
                    glUniform4iv(loc, 1, (const GLint*)data);
                }
            }
            else if(type == 'm')
            {
                if(size == 2)
                {
                    glUniformMatrix2fv(loc, 1, GL_FALSE, (const GLfloat*)data);
                }
                else if(size == 3)
                {
                    glUniformMatrix3fv(loc, 1, GL_FALSE, (const GLfloat*)data);
                }
                else if(size == 4)
                {
                    glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat*)data);
                }
            }
        }

        void parBindShaderProgram(PARContext* ctx, PARShaderProgram* prog)
        {
            glUseProgram(prog ? prog->id : 0);
        }

        void parDeleteShaderProgram(PARContext* ctx, PARShaderProgram* prog)
        {
            glUseProgram(0);

            glDeleteProgram(prog->id);

            free(prog);
        }

        GLenum gl_parToGLPixelFormat(PARTextureFormat f)
        {
            switch(f)
            {
                case PAR_PIXEL_FORMAT_DEPTH16:
                case PAR_PIXEL_FORMAT_DEPTH24:
                case PAR_PIXEL_FORMAT_DEPTH32F:
                    return GL_DEPTH_COMPONENT;
                case PAR_PIXEL_FORMAT_DEPTH24_STENCIL8:
                case PAR_PIXEL_FORMAT_DEPTH32F_STENCIL8:
                    return GL_DEPTH_STENCIL;
                case PAR_PIXEL_FORMAT_R8:
                case PAR_PIXEL_FORMAT_R16:
                case PAR_PIXEL_FORMAT_R8_SNORM:
                case PAR_PIXEL_FORMAT_R16_SNORM:
                case PAR_PIXEL_FORMAT_R16F:
                case PAR_PIXEL_FORMAT_R32F:
                    return GL_RED;
                case PAR_PIXEL_FORMAT_R8I:
                case PAR_PIXEL_FORMAT_R16I:
                case PAR_PIXEL_FORMAT_R32I:
                case PAR_PIXEL_FORMAT_R8UI:
                case PAR_PIXEL_FORMAT_R16UI:
                case PAR_PIXEL_FORMAT_R32UI:
                    return GL_RED_INTEGER;
                case PAR_PIXEL_FORMAT_RG8:
                case PAR_PIXEL_FORMAT_RG16:
                case PAR_PIXEL_FORMAT_RG8_SNORM:
                case PAR_PIXEL_FORMAT_RG16_SNORM:
                case PAR_PIXEL_FORMAT_RG16F:
                case PAR_PIXEL_FORMAT_RG32F:
                    return GL_RG;
                case PAR_PIXEL_FORMAT_RG8I:
                case PAR_PIXEL_FORMAT_RG16I:
                case PAR_PIXEL_FORMAT_RG32I:
                case PAR_PIXEL_FORMAT_RG8UI:
                case PAR_PIXEL_FORMAT_RG16UI:
                case PAR_PIXEL_FORMAT_RG32UI:
                    return GL_RG_INTEGER;
                case PAR_PIXEL_FORMAT_RGB8:
                case PAR_PIXEL_FORMAT_RGB16:
                case PAR_PIXEL_FORMAT_RGB8_SNORM:
                case PAR_PIXEL_FORMAT_RGB16_SNORM:
                case PAR_PIXEL_FORMAT_RGB16F:
                case PAR_PIXEL_FORMAT_RGB32F:
                case PAR_PIXEL_FORMAT_SRGB8:
                case PAR_PIXEL_FORMAT_R11F_G11F_B10F:
                case PAR_PIXEL_FORMAT_RGB9_E5:
                    return GL_RGB;
                case PAR_PIXEL_FORMAT_RGB8I:
                case PAR_PIXEL_FORMAT_RGB16I:
                case PAR_PIXEL_FORMAT_RGB32I:
                case PAR_PIXEL_FORMAT_RGB8UI:
                case PAR_PIXEL_FORMAT_RGB16UI:
                case PAR_PIXEL_FORMAT_RGB32UI:
                    return GL_RGB_INTEGER;
                case PAR_PIXEL_FORMAT_RGBA8:
                case PAR_PIXEL_FORMAT_RGBA16:
                case PAR_PIXEL_FORMAT_RGBA8_SNORM:
                case PAR_PIXEL_FORMAT_RGBA16_SNORM:
                case PAR_PIXEL_FORMAT_RGBA16F:
                case PAR_PIXEL_FORMAT_RGBA32F:
                case PAR_PIXEL_FORMAT_SRGB8_ALPHA8:
                case PAR_PIXEL_FORMAT_RGB10_A2:
                    return GL_RGBA;
                case PAR_PIXEL_FORMAT_RGBA8I:
                case PAR_PIXEL_FORMAT_RGBA16I:
                case PAR_PIXEL_FORMAT_RGBA32I:
                case PAR_PIXEL_FORMAT_RGBA8UI:
                case PAR_PIXEL_FORMAT_RGBA16UI:
                case PAR_PIXEL_FORMAT_RGBA32UI:
                case PAR_PIXEL_FORMAT_RGB10_A2UI:
                    return GL_RGBA_INTEGER;
            }
        }

        GLenum gl_parToGLInternalFormat(PARTextureFormat f)
        {
            switch(f)
            {
                case PAR_PIXEL_FORMAT_DEPTH16: return GL_DEPTH_COMPONENT16;
                case PAR_PIXEL_FORMAT_DEPTH24: return GL_DEPTH_COMPONENT24;
                case PAR_PIXEL_FORMAT_DEPTH32F: return GL_DEPTH_COMPONENT32F;
                case PAR_PIXEL_FORMAT_DEPTH24_STENCIL8: return GL_DEPTH24_STENCIL8;
                case PAR_PIXEL_FORMAT_DEPTH32F_STENCIL8: return GL_DEPTH32F_STENCIL8;
                case PAR_PIXEL_FORMAT_R8: return GL_R8;
                case PAR_PIXEL_FORMAT_R16: return GL_R16;
                case PAR_PIXEL_FORMAT_R8_SNORM: return GL_R8_SNORM;
                case PAR_PIXEL_FORMAT_R16_SNORM: return GL_R16_SNORM;
                case PAR_PIXEL_FORMAT_R16F: return GL_R16F;
                case PAR_PIXEL_FORMAT_R32F: return GL_R32F;
                case PAR_PIXEL_FORMAT_R8I:  return GL_R8I;
                case PAR_PIXEL_FORMAT_R16I: return GL_R16I;
                case PAR_PIXEL_FORMAT_R32I: return GL_R32I;
                case PAR_PIXEL_FORMAT_R8UI: return GL_R8UI;
                case PAR_PIXEL_FORMAT_R16UI: return GL_R16UI;
                case PAR_PIXEL_FORMAT_R32UI: return GL_R32UI;
                case PAR_PIXEL_FORMAT_RG8: return GL_RG8;
                case PAR_PIXEL_FORMAT_RG16: return GL_RG16;
                case PAR_PIXEL_FORMAT_RG8_SNORM: return GL_RG8_SNORM;
                case PAR_PIXEL_FORMAT_RG16_SNORM: return GL_RG16_SNORM;
                case PAR_PIXEL_FORMAT_RG16F: return GL_RG16F;
                case PAR_PIXEL_FORMAT_RG32F: return GL_RG32F;
                case PAR_PIXEL_FORMAT_RG8I: return GL_RG8I;
                case PAR_PIXEL_FORMAT_RG16I: return GL_RG16I;
                case PAR_PIXEL_FORMAT_RG32I: return GL_RG32I;
                case PAR_PIXEL_FORMAT_RG8UI: return GL_RG8UI;
                case PAR_PIXEL_FORMAT_RG16UI: return GL_RG16UI;
                case PAR_PIXEL_FORMAT_RG32UI: return GL_RG32UI;
                case PAR_PIXEL_FORMAT_RGB8: return GL_RGB8;
                case PAR_PIXEL_FORMAT_RGB16: return GL_RGB16;
                case PAR_PIXEL_FORMAT_RGB8_SNORM: return GL_RGB8_SNORM;
                case PAR_PIXEL_FORMAT_RGB16_SNORM: return GL_RGB16_SNORM;
                case PAR_PIXEL_FORMAT_RGB16F: return GL_RGB16F;
                case PAR_PIXEL_FORMAT_RGB32F: return GL_RGB32F;
                case PAR_PIXEL_FORMAT_SRGB8: return GL_SRGB8;
                case PAR_PIXEL_FORMAT_R11F_G11F_B10F: return GL_R11F_G11F_B10F;
                case PAR_PIXEL_FORMAT_RGB9_E5: return GL_RGB9_E5;
                case PAR_PIXEL_FORMAT_RGB8I: return GL_RGB8I;
                case PAR_PIXEL_FORMAT_RGB16I: return GL_RGB16I;
                case PAR_PIXEL_FORMAT_RGB32I: return GL_RGB32I;
                case PAR_PIXEL_FORMAT_RGB8UI: return GL_RGB8UI;
                case PAR_PIXEL_FORMAT_RGB16UI: return GL_RGB16UI;
                case PAR_PIXEL_FORMAT_RGB32UI: return GL_RGB32UI;
                case PAR_PIXEL_FORMAT_RGBA8: return GL_RGBA8;
                case PAR_PIXEL_FORMAT_RGBA16: return GL_RGBA16;
                case PAR_PIXEL_FORMAT_RGBA8_SNORM: return GL_RGBA8_SNORM;
                case PAR_PIXEL_FORMAT_RGBA16_SNORM: return GL_RGBA16_SNORM;
                case PAR_PIXEL_FORMAT_RGBA16F: return GL_RGBA16F;
                case PAR_PIXEL_FORMAT_RGBA32F: return GL_RGBA32F;
                case PAR_PIXEL_FORMAT_SRGB8_ALPHA8: return GL_SRGB8_ALPHA8;
                case PAR_PIXEL_FORMAT_RGB10_A2: return GL_RGB10_A2;
                case PAR_PIXEL_FORMAT_RGBA8I: return GL_RGBA8I;
                case PAR_PIXEL_FORMAT_RGBA16I: return GL_RGBA16I;
                case PAR_PIXEL_FORMAT_RGBA32I: return GL_RGBA32I;
                case PAR_PIXEL_FORMAT_RGBA8UI: return GL_RGBA8UI;
                case PAR_PIXEL_FORMAT_RGBA16UI: return GL_RGBA16UI;
                case PAR_PIXEL_FORMAT_RGBA32UI: return GL_RGBA32UI;
                case PAR_PIXEL_FORMAT_RGB10_A2UI: return GL_RGB10_A2UI;
            }
        }

        GLenum gl_parToGLFormatType(PARTextureFormat f)
        {
            switch(f)
            {
                case PAR_PIXEL_FORMAT_R8:
                case PAR_PIXEL_FORMAT_RG8:
                case PAR_PIXEL_FORMAT_RGB8:
                case PAR_PIXEL_FORMAT_RGBA8:
                case PAR_PIXEL_FORMAT_SRGB8:
                case PAR_PIXEL_FORMAT_SRGB8_ALPHA8:
                    return GL_UNSIGNED_BYTE;
                case PAR_PIXEL_FORMAT_R8_SNORM:
                case PAR_PIXEL_FORMAT_RG8_SNORM:
                case PAR_PIXEL_FORMAT_RGB8_SNORM:
                case PAR_PIXEL_FORMAT_RGBA8_SNORM:
                    return GL_BYTE;
                case PAR_PIXEL_FORMAT_DEPTH16:
                case PAR_PIXEL_FORMAT_R16:
                case PAR_PIXEL_FORMAT_RG16:
                case PAR_PIXEL_FORMAT_RGB16:
                case PAR_PIXEL_FORMAT_RGBA16:
                    return GL_UNSIGNED_SHORT;
                case PAR_PIXEL_FORMAT_R16_SNORM:
                case PAR_PIXEL_FORMAT_RG16_SNORM:
                case PAR_PIXEL_FORMAT_RGB16_SNORM:
                case PAR_PIXEL_FORMAT_RGBA16_SNORM:
                    return GL_SHORT;
                case PAR_PIXEL_FORMAT_R16F:
                case PAR_PIXEL_FORMAT_RG16F:
                case PAR_PIXEL_FORMAT_RGB16F:
                case PAR_PIXEL_FORMAT_RGBA16F:
                    return GL_HALF_FLOAT;
                case PAR_PIXEL_FORMAT_R32F:
                case PAR_PIXEL_FORMAT_RG32F:
                case PAR_PIXEL_FORMAT_RGB32F:
                case PAR_PIXEL_FORMAT_RGBA32F:
                case PAR_PIXEL_FORMAT_DEPTH32F:
                    return GL_FLOAT;
                case PAR_PIXEL_FORMAT_R8UI:
                case PAR_PIXEL_FORMAT_R16UI:
                case PAR_PIXEL_FORMAT_R32UI:
                case PAR_PIXEL_FORMAT_RG8UI:
                case PAR_PIXEL_FORMAT_RG16UI:
                case PAR_PIXEL_FORMAT_RG32UI:
                case PAR_PIXEL_FORMAT_RGB8UI:
                case PAR_PIXEL_FORMAT_RGB16UI:
                case PAR_PIXEL_FORMAT_RGB32UI:
                case PAR_PIXEL_FORMAT_RGBA8UI:
                case PAR_PIXEL_FORMAT_RGBA16UI:
                case PAR_PIXEL_FORMAT_RGBA32UI:
                case PAR_PIXEL_FORMAT_DEPTH24:
                    return GL_UNSIGNED_INT;
                case PAR_PIXEL_FORMAT_R8I:
                case PAR_PIXEL_FORMAT_R16I:
                case PAR_PIXEL_FORMAT_R32I:
                case PAR_PIXEL_FORMAT_RG8I:
                case PAR_PIXEL_FORMAT_RG16I:
                case PAR_PIXEL_FORMAT_RG32I:
                case PAR_PIXEL_FORMAT_RGB8I:
                case PAR_PIXEL_FORMAT_RGB16I:
                case PAR_PIXEL_FORMAT_RGB32I:
                case PAR_PIXEL_FORMAT_RGBA8I:
                case PAR_PIXEL_FORMAT_RGBA16I:
                case PAR_PIXEL_FORMAT_RGBA32I:
                    return GL_INT;
                case PAR_PIXEL_FORMAT_DEPTH24_STENCIL8:
                    return GL_UNSIGNED_INT_24_8;
                case PAR_PIXEL_FORMAT_DEPTH32F_STENCIL8:
                    return GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
                case PAR_PIXEL_FORMAT_R11F_G11F_B10F:
                    return GL_UNSIGNED_INT_10F_11F_11F_REV;
                case PAR_PIXEL_FORMAT_RGB9_E5:
                    return GL_UNSIGNED_INT_5_9_9_9_REV;
                case PAR_PIXEL_FORMAT_RGB10_A2:
                case PAR_PIXEL_FORMAT_RGB10_A2UI:
                    return GL_UNSIGNED_INT_10_10_10_2;
            }
        }

        GLenum gl_parToGLTexParam(PARTextureParameter p)
        {
            switch(p)
            {
                case PAR_TEXTURE_MIN_FILTER: return GL_TEXTURE_MIN_FILTER;
                case PAR_TEXTURE_MAG_FILTER: return GL_TEXTURE_MAG_FILTER;
                case PAR_TEXTURE_WRAP_S: return GL_TEXTURE_WRAP_S;
                case PAR_TEXTURE_WRAP_T: return GL_TEXTURE_WRAP_T;
                case PAR_TEXTURE_WRAP_R: return GL_TEXTURE_WRAP_R;
            }
        }

        GLenum gl_parToGLTexParamValue(PARTextureParamValue p)
        {
            switch(p)
            {
                case PAR_NEAREST: return GL_NEAREST;
                case PAR_LINEAR: return GL_LINEAR;
                case PAR_CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
                case PAR_CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
                case PAR_MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
                case PAR_REPEAT: return GL_REPEAT;
            }
        }

		PARTexture* parCreateTexture(PARContext* ctx, PARTextureInfo info, PARTextureType type)
		{
            PARTexture* tex = malloc(sizeof(PARTexture));

            GLenum gltype;
            switch(type)
            {
                case PAR_TEXTURE_1D:
                    gltype = GL_TEXTURE_1D;
                    break;
                case PAR_TEXTURE_2D:
                    gltype = GL_TEXTURE_2D;
                    break;
                case PAR_TEXTURE_3D:
                    gltype = GL_TEXTURE_3D;
                    break;
            }

            glGenTextures(1, &tex->id);
            glBindTexture(gltype, tex->id);

            for(int i = 0 ; i < info.params_count; i++)
            {
                glTexParameteri(gltype, gl_parToGLTexParam(info.params[i].param), gl_parToGLTexParamValue(info.params[i++].value));
            }

            #ifdef PAR_GL2_IMPLEMENTATION
                #ifdef GL_GENERATE_MIPMAP
                    glTexParameteri(gltype, GL_GENERATE_MIPMAP, GL_TRUE);
                #elif defined(GL_GENERATE_MIPMAP_SGIS)
                    glTexParameteri(gltype, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
                #endif
            #endif

            if(type == PAR_TEXTURE_1D)
            {
                glTexImage1D(gltype, 0, gl_parToGLInternalFormat(info.format), info.width, 0, gl_parToGLPixelFormat(info.format), gl_parToGLFormatType(info.format), info.data);
            }
            else if(type == PAR_TEXTURE_2D)
            {
                glTexImage2D(gltype, 0, gl_parToGLInternalFormat(info.format), info.width, info.height, 0, gl_parToGLPixelFormat(info.format), gl_parToGLFormatType(info.format), info.data);
            }
            else if(type == PAR_TEXTURE_3D)
            {
                glTexImage3D(gltype, 0, gl_parToGLInternalFormat(info.format), info.width, info.height, info.depth, 0, gl_parToGLPixelFormat(info.format), gl_parToGLFormatType(info.format), info.data);
            }

            #ifdef PAR_GL3_IMPLEMENTATION
                glEnable(gltype);
                glGenerateMipmap(gltype);
            #endif

            tex->target = gltype;

            return tex;
		}
		void parBindTexture(PARContext* ctx, PARTexture* tex, int unit)
        {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(tex->target, tex ? tex->id : 0);
        }

		void parDeleteTexture(PARContext* ctx, PARTexture* tex)
        {
            glBindTexture(tex->target, 0);
            glDeleteTextures(1, &tex->id);
        }
    #endif

    #ifdef PAR_D3D11_IMPLEMENTATION
        struct PARVertexBufferImplData
        {
            ID3D10Buffer* vbo;
        };
        PARVertexBuffer* parCreateVertexBuffer(PARContext* ctx, PARVertexBufferType type, void* data, int data_size)
        {
        }
    #endif
#endif
