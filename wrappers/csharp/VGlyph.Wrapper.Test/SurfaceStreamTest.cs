using System;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using VGlyph;
using Xunit;

public class SurfaceStreamTest
{
    public class Cctor
    {
        [Fact]
        public void SurfaceNull()
        {
            var exception = Assert.Throws<ArgumentNullException>(() => new SurfaceStream(null, (IntPtr)1));
            Assert.Equal("surface", exception.ParamName);
        }

        [Fact]
        public void PtrNull()
        {
            using (var surface = FormatterServices.GetUninitializedObject(typeof(Surface)) as Surface)
            {
                var exception = Assert.Throws<ArgumentNullException>(() => new SurfaceStream(surface, IntPtr.Zero));
                Assert.Equal("ptr", exception.ParamName);
            }
        }
    }

    public class Disposed
    {
        [Fact]
        public void CheckDisposed()
        {
            var stream = FormatterServices.GetUninitializedObject(typeof(SurfaceStream)) as SurfaceStream;
            stream.Dispose();

            Assert.False(stream.CanRead);
            Assert.False(stream.CanSeek);
            Assert.False(stream.CanWrite);
            Assert.Equal(0, stream.Length);
            Assert.Equal(0, stream.Position);
            Assert.Throws<ObjectDisposedException>(() => stream.Flush());
            Assert.Throws<ObjectDisposedException>(() => stream.Read(null, 0, 0));
            Assert.Throws<ObjectDisposedException>(() => stream.Write(null, 0, 0));
            Assert.Throws<ObjectDisposedException>(() => stream.Seek(0, SeekOrigin.Begin));
            Assert.Throws<ObjectDisposedException>(() => stream.SetLength(0));
        }
    }

    public class Stream : IDisposable
    {
        private System.IO.Stream SurfaceStream { get; set; }

        public Stream()
        {
            var pitch = 12;
            var height = 2;
            var size = pitch * height;

            SurfaceStream = FormatterServices.GetUninitializedObject(typeof(SurfaceStream)) as SurfaceStream;
            var fieldPtr = SurfaceStream.GetType().GetField("_ptr", BindingFlags.Instance | BindingFlags.NonPublic);
            var fieldLength = SurfaceStream.GetType().GetField("_length", BindingFlags.Instance | BindingFlags.NonPublic);
            var fieldSurface = SurfaceStream.GetType().GetField("_surface", BindingFlags.Instance | BindingFlags.NonPublic);

            var surface = FormatterServices.GetUninitializedObject(typeof(Surface)) as Surface;
            var data = Marshal.AllocHGlobal(size);

            for (var i = 0; i < size; ++i)
                Marshal.WriteByte(data, i, 0);

            fieldPtr.SetValue(SurfaceStream, data);
            fieldLength.SetValue(SurfaceStream, size);
            fieldSurface.SetValue(SurfaceStream, surface);
        }

        public void Dispose()
        {
            if (SurfaceStream != null)
            {
                var fieldPtr = SurfaceStream.GetType().GetField("_ptr", BindingFlags.Instance | BindingFlags.NonPublic);
                var fieldLength = SurfaceStream.GetType().GetField("_length", BindingFlags.Instance | BindingFlags.NonPublic);
                var fieldSurface = SurfaceStream.GetType().GetField("_surface", BindingFlags.Instance | BindingFlags.NonPublic);

                (fieldSurface.GetValue(SurfaceStream) as Surface)?.Dispose();

                var data = (IntPtr)fieldPtr.GetValue(SurfaceStream);

                if (data != IntPtr.Zero)
                    Marshal.FreeHGlobal(data);

                fieldSurface.SetValue(SurfaceStream, null);
                fieldLength?.SetValue(SurfaceStream, 0);
                fieldPtr?.SetValue(SurfaceStream, IntPtr.Zero);

                SurfaceStream = null;
            }
        }

        [Fact]
        public void ReadWrite()
        {
        }
    }
}
