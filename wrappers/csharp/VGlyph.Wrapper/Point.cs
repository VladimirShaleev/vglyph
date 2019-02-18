using System;

namespace VGlyph
{
    /// <summary>
    /// Coordinate
    /// </summary>
    [Serializable]
    public struct Point
    {
        [Explicit] private float _x;
        [Explicit] private float _y;

        /// <summary>
        /// Coordinate X
        /// </summary>
        public float X
        {
            get => _x;
            set => _x = value;
        }

        /// <summary>
        /// Coordinate Y
        /// </summary>
        public float Y
        {
            get => _y;
            set => _y = value;
        }

        /// <summary>
        /// Initialize <see cref="Point"/>
        /// </summary>
        /// <param name="x">X coordinate</param>
        /// <param name="y">Y coordinate</param>
        public Point(float x, float y)
        {
            _x = x;
            _y = y;
        }
    }
}
