using VGlyph;
using Xunit;

public class ColorTest
{
    public class Cctor
    {
        [Theory]
        [InlineData(0)]
        [InlineData(128)]
        [InlineData(200)]
        [InlineData(byte.MaxValue)]
        public void GrayscaleByte(byte grayscale)
        {
            var normalizeGrayscale = grayscale / 255.0;

            var color = new Color(grayscale);

            Assert.Equal(normalizeGrayscale, color.Red);
            Assert.Equal(normalizeGrayscale, color.Green);
            Assert.Equal(normalizeGrayscale, color.Blue);
            Assert.Equal(1.0, color.Alpha);
        }

        [Theory]
        [InlineData(0, 0)]
        [InlineData(128, byte.MaxValue)]
        [InlineData(200, 100)]
        [InlineData(byte.MaxValue, 0)]
        public void GrayscaleAlphaByte(byte grayscale, byte alpha)
        {
            var normalizeGrayscale = grayscale / 255.0;
            var normalizeAlpha = alpha / 255.0;

            var color = new Color(grayscale, alpha);

            Assert.Equal(normalizeGrayscale, color.Red);
            Assert.Equal(normalizeGrayscale, color.Green);
            Assert.Equal(normalizeGrayscale, color.Blue);
            Assert.Equal(normalizeAlpha, color.Alpha);
        }

        [Theory]
        [InlineData(0, 0, 0)]
        [InlineData(128, 5, 200)]
        [InlineData(0, 240, 150)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void RgbByte(byte red, byte green, byte blue)
        {
            var color = new Color(red, green, blue);

            Assert.Equal(red / 255.0, color.Red);
            Assert.Equal(green / 255.0, color.Green);
            Assert.Equal(blue / 255.0, color.Blue);
            Assert.Equal(1.0, color.Alpha);
        }

        [Theory]
        [InlineData(0, 0, 0, 0)]
        [InlineData(128, 5, 200, byte.MaxValue)]
        [InlineData(0, 240, 150, 10)]
        [InlineData(byte.MaxValue, byte.MaxValue, byte.MaxValue, byte.MaxValue)]
        public void RgbAlphaByte(byte red, byte green, byte blue, byte alpha)
        {
            var color = new Color(red, green, blue, alpha);

            Assert.Equal(red / 255.0, color.Red);
            Assert.Equal(green / 255.0, color.Green);
            Assert.Equal(blue / 255.0, color.Blue);
            Assert.Equal(alpha / 255.0, color.Alpha);
        }
        
        [Theory]
        [InlineData(-0.2)]
        [InlineData(0.0)]
        [InlineData(0.4)]
        [InlineData(0.8)]
        [InlineData(1.0)]
        [InlineData(1.5)]
        public void GrayscaleDouble(double grayscale)
        {
            var color = new Color(grayscale);

            Assert.Equal(grayscale, color.Red);
            Assert.Equal(grayscale, color.Green);
            Assert.Equal(grayscale, color.Blue);
            Assert.Equal(1.0, color.Alpha);
        }

        [Theory]
        [InlineData(-0.2, 0.0)]
        [InlineData(0.0, 0.3)]
        [InlineData(0.4, 0.8)]
        [InlineData(0.8, 0.0)]
        [InlineData(1.0, 0.7)]
        [InlineData(1.5, 1.5)]
        public void GrayscaleAlphaDouble(double grayscale, double alpha)
        {
            var color = new Color(grayscale, alpha);

            Assert.Equal(grayscale, color.Red);
            Assert.Equal(grayscale, color.Green);
            Assert.Equal(grayscale, color.Blue);
            Assert.Equal(alpha, color.Alpha);
        }

        [Theory]
        [InlineData(-0.2, 0.0, 0.0)]
        [InlineData(0.0, 0.0, 0.0)]
        [InlineData(0.4, 0.1, 0.5)]
        [InlineData(0.8, 0.0, 0.5)]
        [InlineData(1.0, 0.0, 0.0)]
        [InlineData(1.5, 1.0, 1.0)]
        public void RgbDouble(double red, double green, double blue)
        {
            var color = new Color(red, green, blue);

            Assert.Equal(red, color.Red);
            Assert.Equal(green, color.Green);
            Assert.Equal(blue, color.Blue);
            Assert.Equal(1.0, color.Alpha);
        }

        [Theory]
        [InlineData(-0.2, 0.0, 0.0, 2.0)]
        [InlineData(0.0, 0.0, 0.0, 0.0)]
        [InlineData(0.4, 0.1, 0.5, -0.4)]
        [InlineData(0.8, 0.0, 0.5, 0.7)]
        [InlineData(1.0, 0.0, 0.0, 1.0)]
        [InlineData(1.5, 1.0, 1.0, 0.5)]
        public void RgbAlphaDouble(double red, double green, double blue, double alpha)
        {
            var color = new Color(red, green, blue, alpha);

            Assert.Equal(red, color.Red);
            Assert.Equal(green, color.Green);
            Assert.Equal(blue, color.Blue);
            Assert.Equal(alpha, color.Alpha);
        }
    }
}
