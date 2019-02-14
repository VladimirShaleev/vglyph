﻿using System;
using System.Runtime.InteropServices;

namespace VGlyph.Import
{
    internal static partial class Api
    {
        [DllImport(_library, EntryPoint = "vglyph_version", CallingConvention = _callingConvention)]
        public static extern uint Version();

        [DllImport(_library, EntryPoint = "vglyph_is_version_compatible", CallingConvention = _callingConvention)]
        public static extern bool IsVersionCompatible(uint compileVersion);

        [DllImport(_library, EntryPoint = "vglyph_state_to_string", CallingConvention = _callingConvention)]
        public static extern StringHandle StateToString(State state);

        [DllImport(_library, EntryPoint = "vglyph_get_object_type", CallingConvention = _callingConvention)]
        public static extern ObjectHandle GetObjectType();

        [DllImport(_library, EntryPoint = "vglyph_get_type_type", CallingConvention = _callingConvention)]
        public static extern ObjectHandle GetTypeType();

        [DllImport(_library, EntryPoint = "vglyph_get_figure_type", CallingConvention = _callingConvention)]
        public static extern ObjectHandle GetFigureType();

        [DllImport(_library, EntryPoint = "vglyph_get_glyph_type", CallingConvention = _callingConvention)]
        public static extern ObjectHandle GetGlyphType();

        [DllImport(_library, EntryPoint = "vglyph_get_face_type", CallingConvention = _callingConvention)]
        public static extern ObjectHandle GetFaceType();

        [DllImport(_library, EntryPoint = "vglyph_get_format_type", CallingConvention = _callingConvention)]
        public static extern ObjectHandle GetFormatType();

        [DllImport(_library, EntryPoint = "vglyph_get_rgba_uint_format_type", CallingConvention = _callingConvention)]
        public static extern ObjectHandle GetRgbaUintFormatType();

        [DllImport(_library, EntryPoint = "vglyph_get_rgba_float_format_type", CallingConvention = _callingConvention)]
        public static extern ObjectHandle GetRgbaFloatFormatType();

        [DllImport(_library, EntryPoint = "vglyph_get_transform_type", CallingConvention = _callingConvention)]
        public static extern ObjectHandle GetTransformType();

        [DllImport(_library, EntryPoint = "vglyph_get_surface_type", CallingConvention = _callingConvention)]
        public static extern ObjectHandle GetSurfaceType();

        [DllImport(_library, EntryPoint = "vglyph_object_reference", CallingConvention = _callingConvention)]
        public static extern ObjectHandle ObjectReference(ObjectHandle obj);

        [DllImport(_library, EntryPoint = "vglyph_object_destroy", CallingConvention = _callingConvention)]
        public static extern void ObjectDestroy(IntPtr obj);

        [DllImport(_library, EntryPoint = "vglyph_object_get_reference_count", CallingConvention = _callingConvention)]
        public static extern int ObjectGetReferenceCount(ObjectHandle obj);

        [DllImport(_library, EntryPoint = "vglyph_object_get_state", CallingConvention = _callingConvention)]
        public static extern State ObjectGetState(ObjectHandle obj);

        [DllImport(_library, EntryPoint = "vglyph_object_reset_state", CallingConvention = _callingConvention)]
        public static extern void ObjectResetState(ObjectHandle obj);

        [DllImport(_library, EntryPoint = "vglyph_object_get_type", CallingConvention = _callingConvention)]
        public static extern ObjectHandle ObjectGetType(ObjectHandle obj);

        [DllImport(_library, EntryPoint = "vglyph_object_is_cast", CallingConvention = _callingConvention)]
        public static extern bool ObjectIsCast(ObjectHandle obj, ObjectHandle type);

        [DllImport(_library, EntryPoint = "vglyph_type_is_type", CallingConvention = _callingConvention)]
        public static extern bool TypeIsType(ObjectHandle type, ObjectHandle equalType);

        [DllImport(_library, EntryPoint = "vglyph_figure_create", CallingConvention = _callingConvention)]
        public static extern ObjectHandle FigureCreate();

        [DllImport(_library, EntryPoint = "vglyph_figure_draw_clear", CallingConvention = _callingConvention)]
        public static extern bool FigureDrawClear(ObjectHandle figure);

        [DllImport(_library, EntryPoint = "vglyph_figure_draw_closepath", CallingConvention = _callingConvention)]
        public static extern bool FigureDrawClosepath(ObjectHandle figure);

        [DllImport(_library, EntryPoint = "vglyph_figure_draw_moveto", CallingConvention = _callingConvention)]
        public static extern bool FigureDrawMoveto(ObjectHandle figure, Coordinate coordinate, ref Point point);

        [DllImport(_library, EntryPoint = "vglyph_figure_draw_lineto", CallingConvention = _callingConvention)]
        public static extern bool FigureDrawLineto(ObjectHandle figure, Coordinate coordinate, ref Point point);

        [DllImport(_library, EntryPoint = "vglyph_figure_draw_curveto_cubic", CallingConvention = _callingConvention)]
        public static extern bool FigureDrawCurvetoCubic(ObjectHandle figure, Coordinate coordinate, ref Point point, ref Point point1, ref Point point2);

        [DllImport(_library, EntryPoint = "vglyph_figure_draw_curveto_quadratic", CallingConvention = _callingConvention)]
        public static extern bool FigureDrawCurvetoQuadratic(ObjectHandle figure, Coordinate coordinate, ref Point point, ref Point point1);

        [DllImport(_library, EntryPoint = "vglyph_figure_draw_arc", CallingConvention = _callingConvention)]
        public static extern bool FigureDrawArc(ObjectHandle figure, Coordinate coordinate, ref Point point, ref Point radius, float angle, bool largeArcFlag, bool sweepFlag);

        [DllImport(_library, EntryPoint = "vglyph_figure_draw_lineto_horizontal", CallingConvention = _callingConvention)]
        public static extern bool FigureDrawLinetoHorizontal(ObjectHandle figure, Coordinate coordinate, float x);

        [DllImport(_library, EntryPoint = "vglyph_figure_draw_lineto_vertical", CallingConvention = _callingConvention)]
        public static extern bool FigureDrawLinetoVertical(ObjectHandle figure, Coordinate coordinate, float y);

        [DllImport(_library, EntryPoint = "vglyph_figure_draw_curveto_cubic_smooth", CallingConvention = _callingConvention)]
        public static extern bool FigureDrawCurvetoCubicSmooth(ObjectHandle figure, Coordinate coordinate, ref Point point, ref Point point2);

        [DllImport(_library, EntryPoint = "vglyph_figure_draw_curveto_quadratic_smooth", CallingConvention = _callingConvention)]
        public static extern bool FigureDrawCurvetoQuadraticSmooth(ObjectHandle figure, Coordinate coordinate, ref Point point);

        [DllImport(_library, EntryPoint = "vglyph_glyph_create", CallingConvention = _callingConvention)]
        public static extern ObjectHandle GlyphCreate(ObjectHandle figure);

        [DllImport(_library, EntryPoint = "vglyph_glyph_get_figure", CallingConvention = _callingConvention)]
        public static extern ObjectHandle GlyphGetFigure(ObjectHandle glyph);

        [DllImport(_library, EntryPoint = "vglyph_glyph_get_width", CallingConvention = _callingConvention)]
        public static extern float GlyphGetWidth(ObjectHandle glyph);

        [DllImport(_library, EntryPoint = "vglyph_glyph_get_height", CallingConvention = _callingConvention)]
        public static extern float GlyphGetHeight(ObjectHandle glyph);

        [DllImport(_library, EntryPoint = "vglyph_glyph_get_horizontal_bearing_x", CallingConvention = _callingConvention)]
        public static extern float GlyphGetHorizontalBearingX(ObjectHandle glyph);

        [DllImport(_library, EntryPoint = "vglyph_glyph_set_horizontal_bearing_x", CallingConvention = _callingConvention)]
        public static extern void GlyphSetHorizontalBearingX(ObjectHandle glyph, float bearingX);

        [DllImport(_library, EntryPoint = "vglyph_glyph_get_horizontal_bearing_y", CallingConvention = _callingConvention)]
        public static extern float GlyphGetHorizontalBearingY(ObjectHandle glyph);

        [DllImport(_library, EntryPoint = "vglyph_glyph_set_horizontal_bearing_y", CallingConvention = _callingConvention)]
        public static extern void GlyphSetHorizontalBearingY(ObjectHandle glyph, float bearingY);

        [DllImport(_library, EntryPoint = "vglyph_glyph_get_horizontal_advance", CallingConvention = _callingConvention)]
        public static extern float GlyphGetHorizontalAdvance(ObjectHandle glyph);

        [DllImport(_library, EntryPoint = "vglyph_glyph_set_horizontal_advance", CallingConvention = _callingConvention)]
        public static extern void GlyphSetHorizontalAdvance(ObjectHandle glyph, float advance);

        [DllImport(_library, EntryPoint = "vglyph_glyph_get_vertical_bearing_x", CallingConvention = _callingConvention)]
        public static extern float GlyphGetVerticalBearingX(ObjectHandle glyph);

        [DllImport(_library, EntryPoint = "vglyph_glyph_set_vertical_bearing_x", CallingConvention = _callingConvention)]
        public static extern void GlyphSetVerticalBearingX(ObjectHandle glyph, float bearingX);

        [DllImport(_library, EntryPoint = "vglyph_glyph_get_vertical_bearing_y", CallingConvention = _callingConvention)]
        public static extern float GlyphGetVerticalBearingY(ObjectHandle glyph);

        [DllImport(_library, EntryPoint = "vglyph_glyph_set_vertical_bearing_y", CallingConvention = _callingConvention)]
        public static extern void GlyphSetVerticalBearingY(ObjectHandle glyph, float bearingY);

        [DllImport(_library, EntryPoint = "vglyph_glyph_get_vertical_advance", CallingConvention = _callingConvention)]
        public static extern float GlyphGetVerticalAdvance(ObjectHandle glyph);

        [DllImport(_library, EntryPoint = "vglyph_glyph_set_vertical_advance", CallingConvention = _callingConvention)]
        public static extern void GlyphSetVerticalAdvance(ObjectHandle glyph, float advance);

        [DllImport(_library, EntryPoint = "vglyph_format_get_bits_per_pixel", CallingConvention = _callingConvention)]
        public static extern uint FormatGetBitsPerPixel(ObjectHandle format);

        [DllImport(_library, EntryPoint = "vglyph_format_get_packaging_bytes", CallingConvention = _callingConvention)]
        public static extern void FormatGetPackagingBytes(ObjectHandle format, out PackagingBytes packagingBytes);

        [DllImport(_library, EntryPoint = "vglyph_rgba_uint_format_create", CallingConvention = _callingConvention)]
        public static extern ObjectHandle RgbaUintFormatCreate(ref PackagingBytes packagingBytes, ref RgbaComponents components, ref RgbaUintBitCount bitCount);

        [DllImport(_library, EntryPoint = "vglyph_rgba_uint_format_get_components", CallingConvention = _callingConvention)]
        public static extern void RgbaUintFormatGetComponents(ObjectHandle format, out RgbaComponents components);

        [DllImport(_library, EntryPoint = "vglyph_rgba_uint_format_get_bit_count", CallingConvention = _callingConvention)]
        public static extern void RgbaUintFormatGetBitCount(ObjectHandle format, out RgbaUintBitCount bitCount);

        //vglyph_public vglyph_transform_t*
        //vglyph_transform_create();

        //vglyph_public vglyph_transform_t*
        //vglyph_transform_create_copy(vglyph_transform_t* transform);

        //vglyph_public vglyph_object_t*
        //vglyph_transform_to_object(vglyph_transform_t* transform);

        //vglyph_public void
        //vglyph_transform_clear(vglyph_transform_t* transform);

        //vglyph_public void
        //vglyph_transform_combine(vglyph_transform_t* transform,
        //                         vglyph_transform_t* value);

        //vglyph_public void
        //vglyph_transform_translate(vglyph_transform_t* transform,
        //                           vglyph_float32_t x,
        //                           vglyph_float32_t y);

        //vglyph_public void
        //vglyph_transform_scale(vglyph_transform_t* transform,
        //                       vglyph_float32_t sx,
        //                       vglyph_float32_t sy);

        //vglyph_public void
        //vglyph_transform_rotate(vglyph_transform_t* transform,
        //                        vglyph_float32_t angle);

        //vglyph_public void
        //vglyph_transform_transform_point(vglyph_transform_t* transform,
        //                                 vglyph_point_t* point);

        [DllImport(_library, EntryPoint = "vglyph_surface_get_data_size", CallingConvention = _callingConvention)]
        public static extern uint SurfaceGetDataSize(ObjectHandle format, uint width, uint height, Alignment rowAlignment);

        [DllImport(_library, EntryPoint = "vglyph_surface_create", CallingConvention = _callingConvention)]
        public static extern ObjectHandle SurfaceCreate(ObjectHandle format, uint width, uint height, Alignment rowAlignment);

        //vglyph_public vglyph_surface_t*
        //vglyph_surface_create_for_data(vglyph_uint8_t* data,
        //                               vglyph_uint32_t data_size,
        //                               vglyph_format_t* format,
        //                               vglyph_uint32_t width,
        //                               vglyph_uint32_t height,
        //                               vglyph_alignment_t row_alignment);

        [DllImport(_library, EntryPoint = "vglyph_surface_get_format", CallingConvention = _callingConvention)]
        public static extern ObjectHandle SurfaceGetFormat(ObjectHandle surface);

        [DllImport(_library, EntryPoint = "vglyph_surface_get_width", CallingConvention = _callingConvention)]
        public static extern uint SurfaceGetWidth(ObjectHandle surface);

        [DllImport(_library, EntryPoint = "vglyph_surface_get_height", CallingConvention = _callingConvention)]
        public static extern uint SurfaceGetHeight(ObjectHandle surface);

        [DllImport(_library, EntryPoint = "vglyph_surface_get_pitch", CallingConvention = _callingConvention)]
        public static extern uint SurfaceGetPitch(ObjectHandle surface);

        [DllImport(_library, EntryPoint = "vglyph_surface_get_multisampling", CallingConvention = _callingConvention)]
        public static extern Multisampling SurfaceGetMultisampling(ObjectHandle surface);

        [DllImport(_library, EntryPoint = "vglyph_surface_set_multisampling", CallingConvention = _callingConvention)]
        public static extern void SurfaceSetMultisampling(ObjectHandle surface, Multisampling quality);
        
        [DllImport(_library, EntryPoint = "vglyph_surface_lock", CallingConvention = _callingConvention)]
        public static extern IntPtr SurfaceLock(ObjectHandle surface, uint x, uint y, uint width, uint height);

        [DllImport(_library, EntryPoint = "vglyph_surface_unlock", CallingConvention = _callingConvention)]
        public static extern void SurfaceUnlock(ObjectHandle surface);

        //vglyph_public void
        //vglyph_surface_fill(vglyph_surface_t* surface,
        //                    vglyph_uint32_t x,
        //                    vglyph_uint32_t y,
        //                    vglyph_uint32_t width,
        //                    vglyph_uint32_t height,
        //                    const vglyph_color_t* color);

        //vglyph_public void
        //vglyph_surface_get_pixel(vglyph_surface_t* surface,
        //                         vglyph_sint32_t x,
        //                         vglyph_sint32_t y,
        //                         vglyph_color_t* color);

        //vglyph_public void
        //vglyph_surface_set_pixel(vglyph_surface_t* surface,
        //                         vglyph_sint32_t x,
        //                         vglyph_sint32_t y,
        //                         const vglyph_color_t* color);

        //vglyph_public vglyph_bool_t
        //vglyph_surface_draw_glyph(vglyph_surface_t* surface,
        //                          vglyph_glyph_t* glyph,
        //                          vglyph_float32_t pt,
        //                          const vglyph_color_t* color,
        //                          const vglyph_point_t* position,
        //                          const vglyph_point_t* origin,
        //                          const vglyph_point_t* scale,
        //                          vglyph_float32_t angle,
        //                          vglyph_bool_t vertical_layout);

        //vglyph_public vglyph_bool_t
        //vglyph_surface_draw_glyph_viewport(vglyph_surface_t* surface,
        //                                   vglyph_glyph_t* glyph,
        //                                   const vglyph_color_t* color,
        //                                   const vglyph_point_t* position,
        //                                   const vglyph_point_t* viewport,
        //                                   const vglyph_point_t* origin,
        //                                   vglyph_float32_t angle,
        //                                   vglyph_bool_t fit_to_viewport);

        private const string _library =
#if (WIN || WIN_X64 || WIN_X86)
            "vglyph.dll";
#else
            " ";
#endif

        private const CallingConvention _callingConvention =
            CallingConvention.Cdecl;
    }
}