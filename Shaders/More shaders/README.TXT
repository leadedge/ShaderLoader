Changes made to ShaderLoader now allow these shaders to work.

1) Texture wrap mode is set to GL_REPEAT instead of GL_CLAMP.
This allows use of cordinates from -1.0 to +1.0, otherwise 
texture data will be retrieved only in the range 0.0 - 1.0.

2) Individual ShaderToy channel resolutions are now supported
instead of just the global resolution. This means that any shader
using iChannelResolution will now work.

Many shaders require a noise image to create noise data and 
some require specific images to work. This is annotated in the 
shader code where possible. Otherwise check what is being used.

Take note of the License terms for use of these shaders.
LICENSE.TXT in the "Shaders" root folder.
