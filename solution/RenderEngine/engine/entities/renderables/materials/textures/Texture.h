#ifndef _TEXTURE_H_
#define _TEXTURE_H_

class Texture
{
	public:
        enum Type
        {
            DIFFUSE,
            SPECULAR,
            NORMAL
        } type;

		unsigned int id;
		unsigned int width;
		unsigned int height;

        Texture(unsigned int id, unsigned int width, unsigned int height, Type type = DIFFUSE);
};

#endif
