#pragma once
/*
Most of the code is taken from litehtml\containers\linux
For all platforms need defined LITEHTML_UTF8 for litehtml and satellite projects
Vladislav Hohryakov 03.2019
*/
#include <litehtml.h>
#include <cairo.h>
#include <cairo-ft.h>

class cario_image
{
	cairo_surface_t* m_image_surface;
	int m_width;
	int m_height;
public:
	cario_image(cairo_surface_t* image_surface) : m_image_surface(image_surface)
	{
		m_width = cairo_image_surface_get_width(m_image_surface);
		m_height = cairo_image_surface_get_height(m_image_surface);
	}

	~cario_image()
	{
		cairo_surface_destroy(m_image_surface);
	}

	int get_width() const
	{
		return m_width;
	}

	int get_height() const
	{
		return m_height;
	}

	cairo_surface_t* surface() const {
		return m_image_surface;
	}
};

struct cairo_clip_box
{
	typedef std::vector<cairo_clip_box> vector;
	litehtml::position	box;
	litehtml::border_radiuses radius;

	cairo_clip_box(const litehtml::position& vBox, litehtml::border_radiuses vRad)
	{
		box = vBox;
		radius = vRad;
	}

	cairo_clip_box(const cairo_clip_box& val)
	{
		box = val.box;
		radius = val.radius;
	}
	cairo_clip_box& operator=(const cairo_clip_box& val)
	{
		box = val.box;
		radius = val.radius;
		return *this;
	}
};


struct cairo_font
{
	cairo_font_face_t*	font;
	int					size;
	bool				underline;
	bool				strikeout;
};

class container_cairo_ft :	public litehtml::document_container
{
	cairo_surface_t*			m_temp_surface;
	cairo_t*					m_temp_cr;
    cairo_clip_box::vector		m_clips;
protected:
	typedef lhmemory::shared_ptr<cario_image> image_ptr;
	typedef std::map<litehtml::tstring, image_ptr >	images_map;
	images_map					m_images;
	FT_Library					m_ft_library;
	bool ft_library_available() const;
	virtual	void make_url(const litehtml::tchar_t* url, const litehtml::tchar_t* basepath, litehtml::tstring& out) = 0;
public:
	container_cairo_ft();
	virtual ~container_cairo_ft(void);
	/* from https://github.com/litehtml/litehtml/wiki/document_container
	faceName - the face name for the font. Note: faceName can contain some fonts as described in CSS specifications. You have to select the proper font.
	size - font size in pixels.
	weight - Defines from thin to thick characters. 400 is the same as normal, and 700 is the same as bold.
	decoration - one or more flags: 
	const unsigned int font_decoration_none=0x00;
	const unsigned int font_decoration_underline=0x01;
	const unsigned int font_decoration_linethrough=0x02;
	const unsigned int font_decoration_overline=0x04;
	fm - you have to fill this structure with the font metrics: 
	height - the recommended vertical distance between baselines when setting consecutive lines of text with the font. This is greater than ascent+descent by a quantity known as the line spacing or external leading. When space is at a premium, most fonts can be set with only a distance of ascent+descent between lines.
	ascent - the distance that the font extends above the baseline. Note that this is not always exactly equal to the maximum of the extents of all the glyphs in the font, but rather is picked to express the font designer's intent as to how the font should align with elements above it.
	descent - the distance that the font extends below the baseline. This value is positive for typical fonts that include portions below the baseline. Note that this is not always exactly equal to the maximum of the extents of all the glyphs in the font, but rather is picked to express the font designer's intent as to how the font should align with elements below it.
	x_height - height of the 'x' char (used for internal calculations).
	*/
	virtual litehtml::uint_ptr			create_font(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm) override;
	virtual void						delete_font(litehtml::uint_ptr hFont) override;
	virtual int						text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont) override;
	virtual void						draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos) override;
	virtual int						pt_to_px(int pt) override;
	virtual int						get_default_font_size() const override;
	virtual const litehtml::tchar_t*	get_default_font_name() const override;
	virtual void 						load_image(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready) override;
	virtual void						get_image_size(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz) override;
	virtual void						draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg) override;
	virtual void						draw_borders(litehtml::uint_ptr hdc, const litehtml::borders& borders, const litehtml::position& draw_pos, bool root) override;
	virtual void 						draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker) override;
	virtual lhmemory::shared_ptr<litehtml::element>	create_element(const litehtml::tchar_t *tag_name,
																 const litehtml::string_map &attributes,
																 const lhmemory::shared_ptr<litehtml::document> &doc) override;
	virtual void						get_language(litehtml::tstring& language, litehtml::tstring & culture) const override;
	virtual void 						link(const lhmemory::shared_ptr<litehtml::document> &ptr, const litehtml::element::ptr& el) override;

	virtual	void						transform_text(litehtml::tstring& text, litehtml::text_transform tt) override;
	virtual void						set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y) override;
	virtual void						del_clip() override;

	virtual image_ptr					get_image(const litehtml::tchar_t* url, bool redraw_on_ready);

	void								clear_images();

protected:
	virtual void						draw_ellipse(cairo_t* cr, int x, int y, int width, int height, const litehtml::web_color& color, int line_width);
	virtual void						fill_ellipse(cairo_t* cr, int x, int y, int width, int height, const litehtml::web_color& color);
	virtual void						rounded_rectangle( cairo_t* cr, const litehtml::position &pos, const litehtml::border_radiuses &radius );

private:
	void								apply_clip(cairo_t* cr);
	void								add_path_arc(cairo_t* cr, double x, double y, double rx, double ry, double a1, double a2, bool neg);
	void								set_color(cairo_t* cr, litehtml::web_color color)	{ cairo_set_source_rgba(cr, color.red / 255.0, color.green / 255.0, color.blue / 255.0, color.alpha / 255.0); }
};
