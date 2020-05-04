#ifndef PAR_H_
    #define PAR_H_

    #ifndef PAR_API
        #define PAR_API extern
    #endif

    #ifdef _cplusplus
        extern "C"
        {
    #endif

        typedef enum PARDataType
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

        typedef enum PARBufferType
        {
            PAR_VERTEX_BUFFER,
            PAR_INDEX_BUFFER
        } PARBufferType;

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

        typedef enum PARBufferStorageType
        {
            PAR_STATIC,
            PAR_DYNAMIC
        } PARBufferStorageType;

        typedef enum PARShaderType
        {
            PAR_VERTEX_SHADER,
            PAR_FRAGMENT_SHADER,
            PAR_GEOMETRY_SHADER
        } PARShaderType;

        typedef struct PARVertexAttrib
        {
            char *name;
            int buffer, offset;
            PARDataType format;
        } PARVertexAttrib;
    
        typedef struct PARBuffer PARBuffer;

        struct PARUniform
        {
            int location;
            int offset;
            PARDataType type;
        };
        typedef unsigned int PARShader;
        typedef struct PARShaderProgram
        {
            unsigned int id;
            struct PARUniform* uniforms;
        } PARShaderProgram;

        typedef struct PARTexture {unsigned int id; int target;} PARTexture;

        /*
        * Initialisation parameters 
        */
        typedef struct PARInitParams
        {
            void *d3d11_device;
            void *d3d11_device_context;
            void *(*PARGLProcLoader)(const char *name);
        } PARParams;

        typedef struct PARTextureParamsPair
        {
            PARTextureParameter param;
            PARTextureParamValue value;
        } PARTextureParamsPair;

        typedef struct PARTextureInfo
        {
            void *data;
            PARTextureFormat format;
            int width, height, depth;
            PARTextureParamsPair params[PAR_TEXTURE_PARAMETER_COUNT];
            int params_count;
        } PARTextureInfo;

        typedef struct PARFramebuffer
        {

        } PARFramebuffer;

        typedef struct PARPipelineParams 
        {
            PARVertexAttrib *attributes;
            int attributes_count;
            PARShaderProgram *shader;
        } PARPipelineParams;

        typedef struct PARPipeline PARPipeline;

        /**************************
         * FUNCTIONS              *
         **************************/

        PAR_API int parInit(PARParams params);
        PAR_API void parShutdown();

        PAR_API void parDraw(int start, int count);

        PAR_API PARPipeline *parCreatePipeline(PARPipelineParams params);
        PAR_API void parBindPipeline(PARPipeline *p);
        PAR_API void parSetVertexBuffer(PARBuffer* vbs[16], int count, int offset, int stride);
        PAR_API void parSetIndexBuffer(PARBuffer* ibs, PARDataType type);
        PAR_API void parUnbindPipeline();

        PAR_API PARBuffer *parCreateBuffer(PARBufferType type, PARBufferStorageType s_type, void* data, int data_size);
        PAR_API void parUpdateBuffer(PARBuffer* b, void* data, int offset, int size);
        PAR_API void parAppendBuffer(PARBuffer* b, void* data, int size);
        PAR_API void parDeleteVertexBuffer(PARBuffer* b);

        PAR_API PARShader *parCreateShader(PARShaderType type, const char** strings, const int* length, int count);
        PAR_API void parDeleteShader(PARShader* shader);
        PAR_API PARShaderProgram* parCreateShaderProgram(PARShader** shaders, int count);
        PAR_API void parSetUniform(PARShaderProgram* prog, const char* name, void* data, int size, char type);
        PAR_API void parDeleteShaderProgram(PARShaderProgram* prog);

    	PAR_API PARTexture* parCreateTexture(PARTextureInfo info, PARTextureType type);
    	PAR_API void parBindTexture(PARTexture* tex, int unit);
    	PAR_API void parDeleteTexture(PARTexture* tex);
    #ifdef _cplusplus
        }
    #endif

#endif //PAR_H_

#if defined(PAR_OGL_IMPLEMENTATION) || defined(PAR_D3D10_IMPLEMENTATION)
    #if !defined(PAR_MALLOC) || !defined(PAR_FREE)
        #include <stdlib.h>
        #ifndef PAR_MALLOC
            #define PAR_MALLOC(s) malloc(s)
        #endif
        #ifndef PAR_FREE
            #define PAR_FREE(d) free(d)
        #endif
    #endif

    #ifndef PAR_ASSERT
        #include <assert.h>
        #define PAR_ASSERT(a) assert(a)
    #endif

    #ifndef PAR_LOG
        #ifdef PAR_DEBUG
            #include <stdio.h>
            #define PAR_LOG(m) puts(m)
        #else
            #define PAR_LOG(m)
        #endif
    #endif

    struct _PARContext
    {
        int initialised;

        int indexed;

        PARPipeline* pipeline;

        #ifdef PAR_D3D11_IMPLEMENTATION
            void *d3d11_device;
            void *d3d11_device_context;
        #endif
    };
    static struct _PARContext ctx = {0};
    
    struct _PARBufferCommon
    {
        PARBufferType type;
        PARBufferStorageType s_type;
        int size;
    };

    #ifdef PAR_OGL_IMPLEMENTATION

        struct PARBuffer {
            GLuint id;

            struct _PARBufferCommon common;
        }; 

        struct PARPipeline
        {
            PARVertexAttrib *attribs;
            int attribs_count;
            PARShaderProgram *shader;

            PARDataType idx_type;
        };

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

        static GLenum gl_parToGLBufferType(PARBufferType t)
        {
            switch(t)
            {
                case PAR_VERTEX_BUFFER: return GL_ARRAY_BUFFER;
                case PAR_INDEX_BUFFER: return GL_ELEMENT_ARRAY_BUFFER;
            }
        }

        static GLenum gl_parToGLPixelFormat(PARTextureFormat f)
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

        static GLenum gl_parToGLInternalFormat(PARTextureFormat f)
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

        static GLenum gl_parToGLFormatType(PARTextureFormat f)
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

        static GLenum gl_parToGLTexParam(PARTextureParameter p)
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

        static GLenum gl_parToGLTexParamValue(PARTextureParamValue p)
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

        int parInit(PARParams p)
        {
            if(ctx.initialised)
            {
                PAR_LOG("Already initialised");
                return 1;
            }

            ctx.initialised = 1;
            ctx.pipeline = 0;

            return 1;
        }

        void parShutdown()
        {
            if(!ctx.initialised)
            {
                PAR_LOG("Not initialised");
                return;
            }

            ctx.initialised = 0;
        }

        void parDraw(int start, int count)
        {
            if(ctx.pipeline->idx_type) glDrawElements(0, count, ctx.pipeline->idx_type, (void*)start);
            else glDrawArrays(0, start, count);
        }

        PARPipeline *parCreatePipeline(PARPipelineParams params)
        {
            PARPipeline *p = malloc(sizeof(PARPipeline));

            p->attribs = params.attributes;
            p->shader = params.shader;
            p->idx_type = 0;
        }

        void parBindPipeline(PARPipeline *p)
        {
            if(ctx.pipeline) PAR_LOG("Pipeline already bound");
            ctx.pipeline = p;
        }

        void parSetVertexBuffer(PARBuffer* vbs[16], int count, int *offsets, int *strides);
        {
            if(GL_ARB_vertex_attrib_binding)
            {

            }
            else
            {
                int stride = 0;
                int offset = 0;
                int current_b = -1;

                for(int i = 0; i < ctx.pipeline->attribs_count && ctx.pipeline->attribs_count < 16; i++)
                {
                    PARVertexAttrib att = ctx.pipeline->attribs[i];

                    if(current_b != att.buffer)
                    {
                        glBindBuffer(GL_ARRAY_BUFFER, vbs[att.buffer].id);
                        stride = strides[i];
                        offset = offsets[i];
                        current_b = att.buffer;
                    }

                    int loc = glGetAttribLocation(ctx.pipeline->shader.id, att.name);
                    glEnableVertexAttribArray(loc);
                    glVertexAttribPointer(loc, att.size, gl_parToGLType(att.type), GL_FALSE, stride, (void*)(offset + att.offset));
                }
            }
        }

        PAR_API void parSetIndexBuffer(PARBuffer* ibs, PARDataType type)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibs);
        }

        void parUnbindPipeline()
        {
            for(int i = 0; i < 16; i++)
            {
                int loc = glGetAttribLocation(ctx.pipeline.shader.id, att.name);
                glDisableVertexAttribArray(loc);
            }

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindTexture(0);

            ctx.pipeline = NULL;
        }

        PARBuffer* parCreateBuffer(PARBufferType type, PARBufferStorageType s_type, void* data, int data_size)
        {
            PARBuffer* vb = PAR_MALLOC(sizeof(PARBuffer));

            GLenum gltype = gl_parToGLBufferType(type);

            glGenBuffers(1, &vb->id);
            glBindBuffer(gltype, vb->id);

            if(s_type == PAR_STATIC)
            {
                glBufferData(gltype, data_size, data, GL_STATIC_DRAW);
            }
            else if(s_type == PAR_DYNAMIC)
            {
                glBufferData(gltype, data_size, data, GL_DYNAMIC_DRAW);
            }

            glBindBuffer(gltype, 0);

            vb->common.type = type;
            vb->common.s_type = s_type;
            vb->common.size = data_size;

            return vb;
        }

        void parUpdateBuffer(PARBuffer* b, void* data, int offset, int size)
        {
            if(b->common.s_type == PAR_DYNAMIC)
            {
                GLenum gltype = gl_parToGLBufferType(b->common.type);
                glBindBuffer(gltype, b->id);
                glBufferSubData(gltype, offset, size, data);
                glBindBuffer(gltype, 0);
            }

        }

        void parAppendBuffer(PARBuffer* b, void* data, int size)
        {
            if(b->common.s_type == PAR_DYNAMIC)
            {
                GLenum gltype = gl_parToGLBufferType(b->common.type);
                glBindBuffer(gltype, b->id);
                void* old_data;
                glGetBufferSubData(gltype, 0, b->common.size, old_data);
                glBufferData(gltype, b->common.size + size, old_data, GL_DYNAMIC_DRAW);
                glBufferSubData(gltype, b->common.size, size, data);
                glBindBuffer(gltype, 0);

                b->common.size += size;
            }
        }

        void parDeleteBuffer(PARBuffer* b)
        {
            glBindBuffer(gl_parToGLBufferType(b->common.type), 0);
            glDeleteBuffers(1, &b->id);

            PAR_FREE(b);
        }
    #endif

    #ifdef PAR_D3D11_IMPLEMENTATION
        struct PARVertexBufferImplData
        {
            ID3D10Buffer* vbo;
        };
        PARVertexBuffer* parCreateVertexBuffer(PARVertexBufferType type, void* data, int data_size)
        {
        }
    #endif
#endif
