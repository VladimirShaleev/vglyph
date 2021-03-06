using System;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using VGlyph;
using VGlyph.Import;
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
            
            var handle = new ObjectHandle();
            var data = Marshal.AllocHGlobal(size);

            for (var i = 0; i < size; ++i)
                Marshal.WriteByte(data, i, 0);

            fieldPtr.SetValue(SurfaceStream, data);
            fieldLength.SetValue(SurfaceStream, size);
            fieldSurface.SetValue(SurfaceStream, handle);
        }

        public void Dispose()
        {
            if (SurfaceStream != null)
            {
                var fieldPtr = SurfaceStream.GetType().GetField("_ptr", BindingFlags.Instance | BindingFlags.NonPublic);
                var fieldLength = SurfaceStream.GetType().GetField("_length", BindingFlags.Instance | BindingFlags.NonPublic);
                var fieldSurface = SurfaceStream.GetType().GetField("_surface", BindingFlags.Instance | BindingFlags.NonPublic);

                (fieldSurface.GetValue(SurfaceStream) as ObjectHandle)?.Dispose();

                var data = (IntPtr)fieldPtr.GetValue(SurfaceStream);

                if (data != IntPtr.Zero)
                    Marshal.FreeHGlobal(data);

                fieldSurface.SetValue(SurfaceStream, null);
                fieldLength.SetValue(SurfaceStream, 0);
                fieldPtr.SetValue(SurfaceStream, IntPtr.Zero);

                SurfaceStream = null;
            }
        }

        [Fact]
        public void ReadWrite()
        {
            var buffer = Enumerable.Range(1, 20).Select(i => (byte)i).ToArray();
            var size = (int)SurfaceStream.Length;

            Assert.Equal(0, SurfaceStream.Position);

            SurfaceStream.WriteByte(5);
            Assert.Equal(1, SurfaceStream.Position);

            SurfaceStream.Seek(2, SeekOrigin.Begin);
            Assert.Equal(2, SurfaceStream.Position);

            SurfaceStream.Write(buffer, 4, 5);
            Assert.Equal(7, SurfaceStream.Position);

            SurfaceStream.Seek(0, SeekOrigin.End);
            Assert.Equal(size, SurfaceStream.Position);

            SurfaceStream.Seek(-10, SeekOrigin.Current);
            Assert.Equal(size - 10, SurfaceStream.Position);

            SurfaceStream.Write(buffer, 10, 10);
            Assert.Equal(size, SurfaceStream.Position);

            SurfaceStream.Position = 0;

            var readBuffer = new byte[size];
            var testBuffer = new byte[]
            {
                5, 0, 5, 6, 7, 8, 9, 0, 0,
                0, 0, 0, 0, 0, 11, 12, 13,
                14, 15, 16, 17, 18, 19, 20
            };

            Assert.Equal(size, SurfaceStream.Read(readBuffer, 0, size));
            Assert.Equal(size, SurfaceStream.Position);
            Assert.Equal(testBuffer, readBuffer);
        }

        [Fact]
        public void SeekArgumentOutOfRangeException()
        {
            var exception = Assert.Throws<ArgumentOutOfRangeException>(()
                => SurfaceStream.Seek(SurfaceStream.Length + 1, SeekOrigin.Begin));

            Assert.Equal("offset", exception.ParamName);
        }

        [Fact]
        public void SeekIOException()
        {
            Assert.Throws<IOException>(() => SurfaceStream.Seek(-1, SeekOrigin.Begin));
            Assert.Throws<IOException>(() => SurfaceStream.Seek(1, SeekOrigin.End));

            SurfaceStream.Seek(SurfaceStream.Length / 2, SeekOrigin.Begin);
            Assert.Throws<IOException>(() => SurfaceStream.Seek(SurfaceStream.Length, SeekOrigin.Current));
            Assert.Throws<IOException>(() => SurfaceStream.Seek(-SurfaceStream.Length, SeekOrigin.Current));
        }

        [Fact]
        public void ReadWriteArgumentNullException()
        {
            Assert.Throws<ArgumentNullException>(() => SurfaceStream.Read(null, 0, 0));
            Assert.Throws<ArgumentNullException>(() => SurfaceStream.Write(null, 0, 0));
        }

        [Fact]
        public void ReadWriteArgumentOutOfRangeException()
        {
            var buffer = new byte[] { 1 };

            Assert.Throws<ArgumentOutOfRangeException>(() => SurfaceStream.Read(buffer, -1, 0));
            Assert.Throws<ArgumentOutOfRangeException>(() => SurfaceStream.Read(buffer, 0, -1));
            Assert.Throws<ArgumentOutOfRangeException>(() => SurfaceStream.Write(buffer, -1, 0));
            Assert.Throws<ArgumentOutOfRangeException>(() => SurfaceStream.Write(buffer, 0, -1));
        }

        [Fact]
        public void ReadWriteArgumentException()
        {
            var buffer = new byte[] { 5 };
            Assert.Throws<ArgumentException>(() => SurfaceStream.Read(buffer, 0, 6));
            Assert.Throws<ArgumentException>(() => SurfaceStream.Read(buffer, 3, 3));
            Assert.Throws<ArgumentException>(() => SurfaceStream.Write(buffer, 0, 6));
            Assert.Throws<ArgumentException>(() => SurfaceStream.Write(buffer, 3, 3));
        }

        [Fact]
        public void WriteIOException()
        {
            var buffer = new byte[] { 1, 2, 3, 4, 5 };

            SurfaceStream.Seek(-4, SeekOrigin.End);
            Assert.Throws<IOException>(() => SurfaceStream.Write(buffer, 0, buffer.Length));
        }

        [Fact]
        public void ReadEnd()
        {
            var testBuffer = new byte[] { 4, 5 };

            var writeBuffer = new byte[] { 1, 2, 3, 4, 5 };
            var readBuffer = new byte[5];

            SurfaceStream.Seek(-5, SeekOrigin.End);
            SurfaceStream.Write(writeBuffer, 0, writeBuffer.Length);

            SurfaceStream.Seek(-2, SeekOrigin.End);
            Assert.Equal(2, SurfaceStream.Read(readBuffer, 0, readBuffer.Length));
            Assert.Equal(testBuffer, readBuffer.Take(2));
            Assert.Equal(0, SurfaceStream.Read(readBuffer, 0, readBuffer.Length));
        }

        [Fact]
        public void SetLength()
        {
            var length = SurfaceStream.Length;

            SurfaceStream.SetLength(length);
            Assert.Equal(length, SurfaceStream.Length);
        }

        [Fact]
        public void SetLengthArgumentOutOfRangeException()
        {
            var exception = Assert.Throws<ArgumentOutOfRangeException>(() => SurfaceStream.SetLength(SurfaceStream.Length * 2));
            Assert.Equal("value", exception.ParamName);
        }
    }
}
