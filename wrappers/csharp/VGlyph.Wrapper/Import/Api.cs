using System;
using System.Runtime.InteropServices;

namespace VGlyph.Import
{
    internal static partial class Api
    {
        [DllImport(_library, EntryPoint = "vglyph_version", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint Version();

        [DllImport(_library, EntryPoint = "vglyph_is_version_compatible", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool IsVersionCompatible(uint compileVersion);

        [DllImport(_library, EntryPoint = "vglyph_state_to_string", CallingConvention = CallingConvention.Cdecl)]
        public static extern StringHandle StateToString(State state);
        
        [DllImport(_library, EntryPoint = "vglyph_get_object_type", CallingConvention = CallingConvention.Cdecl)]
        public static extern ObjectHandle GetObjectType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_type_type", CallingConvention = CallingConvention.Cdecl)]
        public static extern ObjectHandle GetTypeType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_figure_type", CallingConvention = CallingConvention.Cdecl)]
        public static extern ObjectHandle GetFigureType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_glyph_type", CallingConvention = CallingConvention.Cdecl)]
        public static extern ObjectHandle GetGlyphType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_face_type", CallingConvention = CallingConvention.Cdecl)]
        public static extern ObjectHandle GetFaceType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_format_type", CallingConvention = CallingConvention.Cdecl)]
        public static extern ObjectHandle GetFormatType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_rgba_uint_format_type", CallingConvention = CallingConvention.Cdecl)]
        public static extern ObjectHandle GetRgbaUintFormatType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_rgba_float_format_type", CallingConvention = CallingConvention.Cdecl)]
        public static extern ObjectHandle GetRgbaFloatFormatType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_transform_type", CallingConvention = CallingConvention.Cdecl)]
        public static extern ObjectHandle GetTransformType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_surface_type", CallingConvention = CallingConvention.Cdecl)]
        public static extern ObjectHandle GetSurfaceType();
        
        [DllImport(_library, EntryPoint = "vglyph_object_reference", CallingConvention = CallingConvention.Cdecl)]
        public static extern ObjectHandle ObjectReference(ObjectHandle obj);

        [DllImport(_library, EntryPoint = "vglyph_object_destroy", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ObjectDestroy(IntPtr obj);
        
        [DllImport(_library, EntryPoint = "vglyph_object_get_reference_count", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ObjectGetReferenceCount(ObjectHandle obj);
        
        [DllImport(_library, EntryPoint = "vglyph_object_get_state", CallingConvention = CallingConvention.Cdecl)]
        public static extern State ObjectGetState(ObjectHandle obj);
        
        [DllImport(_library, EntryPoint = "vglyph_object_reset_state", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ObjectResetState(ObjectHandle obj);
        
        [DllImport(_library, EntryPoint = "vglyph_object_get_type", CallingConvention = CallingConvention.Cdecl)]
        public static extern ObjectHandle ObjectGetType(ObjectHandle obj);

        [DllImport(_library, EntryPoint = "vglyph_object_is_cast", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ObjectIsCast(ObjectHandle obj, ObjectHandle type);

        [DllImport(_library, EntryPoint = "vglyph_type_is_type", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool TypeIsType(ObjectHandle type, ObjectHandle equalType);

        [DllImport(_library, EntryPoint = "vglyph_figure_create", CallingConvention = CallingConvention.Cdecl)]
        public static extern ObjectHandle FigureCreate();
        
        [DllImport(_library, EntryPoint = "vglyph_figure_draw_clear", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool FigureDrawClear(ObjectHandle figure);
        
        [DllImport(_library, EntryPoint = "vglyph_figure_draw_closepath", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool FigureDrawClosepath(ObjectHandle figure);

        private const string _library =
#if (WIN || WIN_X64 || WIN_X86)
            "vglyph.dll";
#else
            " ";
#endif
    }
}
