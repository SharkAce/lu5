#include "lu5_font.h"

#include "lu5_logger.h"

#include "lu5_state.h"

void lu5_init_freetype(lu5_State *l5) {
	if (FT_Init_FreeType(&(l5->ft)))
	{
		LU5_ERROR("Failed to initialize FreeType");
	}
}

int lu5_load_font(lu5_State *l5, const char *fontPath, int *fontId) {

	if (l5->font_count >= MAX_LOADED_FONTS) {
		return LOADFONT_MAX;
	} 

	lu5_font *font = (lu5_font*)malloc(sizeof(lu5_font));
	
	int error = FT_New_Face( 
		l5->ft,
		fontPath,
		0,
		&(font->face));

	if (error == FT_Err_Unknown_File_Format)
	{
		lu5_close_font(font);
		return LOADFONT_UNKNOWN_FORMAT;
	}
	else if (error)
	{
		lu5_close_font(font);
		return LOADFONT_UNKNOWN;
	}

	FT_Set_Pixel_Sizes(font->face, 0, 48); 

	for (unsigned char c = 32; c < 128; c++) {
		// Load character glyph into face->glyph
		if (FT_Load_Char(font->face, c, FT_LOAD_RENDER)) {
			LU5_WARN("Could not load character '%c'\n", c);
			continue;
		}

		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			font->face->glyph->bitmap.width,
			font->face->glyph->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			font->face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		font->textures[c] = texture;
	}

	if (fontId != NULL) *fontId = l5->font_count;
	
	l5->fonts[l5->font_count] = font;
	l5->font_count++;

	return 0;

}

void lu5_render_text(const char *text, float x, float y, float fontSize, lu5_font *font) {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(x, y, 0);
	
	// Use font ascender for uniform baseline alignment
	int ascender = font->face->size->metrics.ascender >> 6;
	
	// Iterate over string characters
	const char *p;
	for (p = text; *p; p++) {

		// Skip non-text
		if (*p < 32 || *p > 126)
		   continue;
		
		// Get texture
		GLuint texture = font->textures[(int)(*p)];
		
		// Load glyph from freetype, or skip if failed
		if(FT_Load_Char(font->face, *p, FT_LOAD_DEFAULT)) continue;
		
		// Adjust height
		float y_adjusted = y + ascender - font->face->glyph->bitmap_top;
		
		// Calculate the pen advances
		float x_advance = 
			(font->face->glyph->metrics.horiBearingX >> 6) + 
			(font->face->glyph->metrics.width >> 6);

		float y_advance = (font->face->glyph->advance.y >> 6);

		// Add space if space char found
		if (*p == 32) x_advance += fontSize/2.5;

		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0); glVertex2f(						0, y_adjusted						   );
			glTexCoord2f(1, 0); glVertex2f(font->face->glyph->bitmap.width, y_adjusted						   );
			glTexCoord2f(1, 1); glVertex2f(font->face->glyph->bitmap.width, y_adjusted + font->face->glyph->bitmap.rows);
			glTexCoord2f(0, 1); glVertex2f(						0, y_adjusted + font->face->glyph->bitmap.rows);
		}
		glEnd();

	   // Move to next glyph position
	   glTranslatef(x_advance, -y_advance, 0);
	}

	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}


void lu5_close_font(lu5_font *font) 
{
	for (int i = 0; i < 128; i++) {
		glDeleteTextures(1, &font->textures[i]);
	}
	FT_Done_Face(font->face);
}

void lu5_close_fonts(lu5_State *l5) 
{
	for (int i = 0; i < l5->font_count; i++) {
		if (l5->fonts[i] == NULL) continue;

		lu5_close_font(l5->fonts[i]); 
	}

	FT_Done_FreeType(l5->ft);
}
