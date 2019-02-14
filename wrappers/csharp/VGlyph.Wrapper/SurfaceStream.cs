using System;
using System.IO;
using System.Runtime.InteropServices;
using VGlyph.Import;

namespace VGlyph
{
    internal class SurfaceStream : Stream
    {
        private Surface _surface;
        private IntPtr _ptr;
        private int _position;
        private int _length;

        public override bool CanRead => !IsDisposed;

        public override bool CanSeek => !IsDisposed;

        public override bool CanWrite => !IsDisposed;

        public override long Length => _length;

        public override long Position
        {
            get => _position;
            set => _position = (int)value;
        }

        public SurfaceStream(Surface surface, IntPtr ptr)
        {
            if (ptr == IntPtr.Zero)
                throw new ArgumentNullException(nameof(ptr), "Pointer to data is null");

            _surface = surface ?? throw new ArgumentNullException(nameof(surface), "Surface is null");

            _ptr = ptr;
            _length = surface.Pitch * surface.Height;
        }

        public override void Flush()
        {
            CheckDisposed();
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            CheckDisposed();
            CheckBuffer(buffer, offset, count);

            var bytes = _length - _position;

            if (bytes > count)
                bytes = count;

            if (bytes <= 0)
                return 0;

            Marshal.Copy(_ptr + _position, buffer, offset, bytes);
            _position += bytes;

            return bytes;
        }

        public override void Write(byte[] buffer, int offset, int count)
        {
            CheckDisposed();
            CheckBuffer(buffer, offset, count);

            var i = _position + count;

            if (i < 0)
                throw new IOException();

            if (i > _length)
                throw new IOException();

            Marshal.Copy(buffer, offset, _ptr + _position, count);
            _position = i;
        }

        public override long Seek(long offset, SeekOrigin origin)
        {
            CheckDisposed();

            if (offset > Length)
                throw new ArgumentOutOfRangeException(nameof(offset));

            var newPosition = 0L;

            switch (origin)
            {
                case SeekOrigin.Begin:
                    newPosition = offset;
                    break;

                case SeekOrigin.Current:
                    newPosition = Position + offset;
                    break;

                case SeekOrigin.End:
                    newPosition = Length;
                    break;
            }

            if (newPosition < 0 || newPosition > Length)
                throw new IOException("Seek out of range");

            Position = newPosition;
            return Position;
        }

        public override void SetLength(long value)
        {
            CheckDisposed();

            if (value != Length)
                throw new ArgumentOutOfRangeException(nameof(value));
        }

        protected override void Dispose(bool disposing)
        {
            if (_ptr != IntPtr.Zero)
            {
                Api.SurfaceUnlock(_surface.Object);

                _surface = null;
                _ptr = IntPtr.Zero;
                _position = 0;
                _length = 0;
            }

            base.Dispose(disposing);
        }

        private bool IsDisposed
            => _surface == null;

        private void CheckBuffer(byte[] buffer, int offset, int count)
        {
            if (buffer == null)
                throw new ArgumentNullException(nameof(buffer), "buffer for data is null");

            if (offset < 0)
                throw new ArgumentOutOfRangeException(nameof(offset), "The offset must not be less than zero");

            if (count < 0)
                throw new ArgumentOutOfRangeException(nameof(count), "The count must not be less than zero");

            if (buffer.Length - offset < count)
                throw new ArgumentException("Parameters is out of range the buffer");
        }

        private void CheckDisposed()
        {
            if (IsDisposed)
                throw new ObjectDisposedException(nameof(Stream));
        }
    }
}
