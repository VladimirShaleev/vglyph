using System;
using System.Runtime.InteropServices;

namespace VGlyph
{
    enum State
    {
        Success = 0,
        OutOfMemory = 1,
        InvalidCast = 2,
        InvalidFormat = 3
    }

    internal static partial class Import
    {
        [DllImport(_library, EntryPoint = "vglyph_version")]
        public static extern uint Version();

        [DllImport(_library, EntryPoint = "vglyph_is_version_compatible")]
        public static extern bool IsVersionCompatible(uint compileVersion);

        [DllImport(_library, EntryPoint = "vglyph_state_to_string")]
        public static extern StringHandle StateToString(State state);
        
        [DllImport(_library, EntryPoint = "vglyph_get_object_type")]
        public static extern ObjectHandle GetObjectType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_type_type")]
        public static extern ObjectHandle GetTypeType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_figure_type")]
        public static extern ObjectHandle GetFigureType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_glyph_type")]
        public static extern ObjectHandle GetGlyphType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_face_type")]
        public static extern ObjectHandle GetFaceType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_format_type")]
        public static extern ObjectHandle GetFormatType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_rgba_uint_format_type")]
        public static extern ObjectHandle GetRgbaUintFormatType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_rgba_float_format_type")]
        public static extern ObjectHandle GetRgbaFloatFormatType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_transform_type")]
        public static extern ObjectHandle GetTransformType();
        
        [DllImport(_library, EntryPoint = "vglyph_get_surface_type")]
        public static extern ObjectHandle GetSurfaceType();
        
        [DllImport(_library, EntryPoint = "vglyph_object_reference")]
        public static extern ObjectHandle ObjectReference(ObjectHandle obj);

        [DllImport(_library, EntryPoint = "vglyph_object_destroy")]
        public static extern void ObjectDestroy(IntPtr obj);
        
        [DllImport(_library, EntryPoint = "vglyph_object_get_reference_count")]
        public static extern int ObjectGetReferenceCount(ObjectHandle obj);
        
        [DllImport(_library, EntryPoint = "vglyph_object_get_state")]
        public static extern State ObjectGetState(ObjectHandle obj);
        
        [DllImport(_library, EntryPoint = "vglyph_object_reset_state")]
        public static extern void ObjectResetState(ObjectHandle obj);
        
        [DllImport(_library, EntryPoint = "vglyph_object_get_type")]
        public static extern ObjectHandle ObjectGetType(ObjectHandle obj);

        [DllImport(_library, EntryPoint = "vglyph_object_is_cast")]
        public static extern void ObjectIsCast(ObjectHandle obj, ObjectHandle type);

        [DllImport(_library, EntryPoint = "vglyph_type_is_type")]
        public static extern bool TypeIsType(ObjectHandle type, ObjectHandle equalType);
        
        private const string _library =
#if (WIN || WIN_X64 || WIN_X86)
            "vglyph.dll";
#else
            " ";
#endif
    }
}
