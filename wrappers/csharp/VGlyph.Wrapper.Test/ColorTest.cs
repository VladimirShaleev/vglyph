using System;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using VGlyph;
using Xunit;

public class ColorTest
{
    public class Cctor
    {
        [Fact]
        public void NoParams()
        {
            var color = new Color();

            Assert.Equal(0.0, color.Red);
            Assert.Equal(0.0, color.Green);
            Assert.Equal(0.0, color.Blue);
            Assert.Equal(1.0, color.Alpha);
        }

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
    
    public class Properties
    {
        [Theory]
        [InlineData(-0.2, 0.0, 0.0, 2.0)]
        [InlineData(0.0, 0.0, 0.0, 0.0)]
        [InlineData(0.4, 0.1, 0.5, -0.4)]
        [InlineData(0.8, 0.0, 0.5, 0.7)]
        [InlineData(1.0, 0.0, 0.0, 1.0)]
        [InlineData(1.5, 1.0, 1.0, 0.5)]
        public void Setters(double red, double green, double blue, double alpha)
        {
            var color = new Color
            {
                Red = red,
                Green = green,
                Blue = blue,
                Alpha = alpha
            };

            Assert.Equal(red, color.Red);
            Assert.Equal(green, color.Green);
            Assert.Equal(blue, color.Blue);
            Assert.Equal(alpha, color.Alpha);
        }
    }

    public class Cloneable
    {
        [Theory]
        [InlineData(-0.2, 0.0, 0.0, 2.0)]
        [InlineData(0.0, 0.0, 0.0, 0.0)]
        [InlineData(0.4, 0.1, 0.5, -0.4)]
        [InlineData(0.8, 0.0, 0.5, 0.7)]
        [InlineData(1.0, 0.0, 0.0, 1.0)]
        [InlineData(1.5, 1.0, 1.0, 0.5)]
        public void Clone(double red, double green, double blue, double alpha)
        {
            var color = new Color(red, green, blue, alpha);

            var cloneColor = color.Clone() as Color;

            Assert.Equal(color.Red, cloneColor.Red);
            Assert.Equal(color.Green, cloneColor.Green);
            Assert.Equal(color.Blue, cloneColor.Blue);
            Assert.Equal(color.Alpha, cloneColor.Alpha);
        }
    }

    public class Comparator
    {
        [Theory]
        [InlineData(true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)]
        [InlineData(true, 1.0, 0.5, 2.0, 0.2, 1.0, 0.5, 2.0, 0.2)]
        [InlineData(false, 1.0, 0.7, 2.0, 0.2, 1.0, 0.5, 2.0, 0.2)]
        [InlineData(false, 1.0, 0.5, 2.0, 0.2, 0.0, 0.5, 2.0, 0.2)]
        [InlineData(false, 1.0, 0.5, 2.0, 0.2, 1.0, 0.0, 2.0, 0.2)]
        [InlineData(false, 1.0, 0.5, 2.0, 0.2, 1.0, 0.5, 0.0, 0.2)]
        [InlineData(false, 1.0, 0.5, 2.0, 0.2, 1.0, 0.5, 2.0, 0.0)]
        public void EqualsObject(bool equal, double red1, double green1, double blue1, double alpha1, double red2, double green2, double blue2, double alpha2)
        {
            var color1 = new Color(red1, green1, blue1, alpha1) as object;
            var color2 = new Color(red2, green2, blue2, alpha2);

            var result = color1.Equals(color2);

            Assert.Equal(equal, result);
        }

        [Theory]
        [InlineData(0.0, 0.0, 0.0, 0.0)]
        [InlineData(1.0, 0.0, 0.5, 0.0)]
        [InlineData(0.0, 0.2, 0.0, 0.8)]
        public void EqualsObjectTwoParamIsNull(double red, double green, double blue, double alpha)
        {
            var color = new Color(red, green, blue, alpha) as object;

            var result = color.Equals(null);

            Assert.False(result);
        }

        [Fact]
        public void EqualsObjectIsNotColor()
        {
            var color = new Color() as object;

            var result = color.Equals(new object());

            Assert.False(result);
        }

        [Theory]
        [InlineData(true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)]
        [InlineData(true, 1.0, 0.5, 2.0, 0.2, 1.0, 0.5, 2.0, 0.2)]
        [InlineData(false, 1.0, 0.7, 2.0, 0.2, 1.0, 0.5, 2.0, 0.2)]
        [InlineData(false, 1.0, 0.5, 2.0, 0.2, 0.0, 0.5, 2.0, 0.2)]
        [InlineData(false, 1.0, 0.5, 2.0, 0.2, 1.0, 0.0, 2.0, 0.2)]
        [InlineData(false, 1.0, 0.5, 2.0, 0.2, 1.0, 0.5, 0.0, 0.2)]
        [InlineData(false, 1.0, 0.5, 2.0, 0.2, 1.0, 0.5, 2.0, 0.0)]
        public void Equal(bool equal, double red1, double green1, double blue1, double alpha1, double red2, double green2, double blue2, double alpha2)
        {
            var color1 = new Color(red1, green1, blue1, alpha1) as IEquatable<Color>;
            var color2 = new Color(red2, green2, blue2, alpha2);

            var result = color1.Equals(color2);

            Assert.Equal(equal, result);
        }

        [Theory]
        [InlineData(0.0, 0.0, 0.0, 0.0)]
        [InlineData(1.0, 0.0, 0.5, 0.0)]
        [InlineData(0.0, 0.2, 0.0, 0.8)]
        public void EqualsTwoParamIsNull(double red, double green, double blue, double alpha)
        {
            var color = new Color(red, green, blue, alpha) as IEquatable<Color>;

            var result = color.Equals(null);

            Assert.False(result);
        }

        [Fact]
        public void EqualsIsNotColor()
        {
            var color = new Color() as IEquatable<Color>;

            var result = color.Equals(new object());

            Assert.False(result);
        }
    }

    public class HashCode
    {
        [Fact]
        public void GetHash()
        {
            var color1 = new Color(1.0, 0.2, 0.8, 0.5);
            var color2 = new Color(1.0, 0.2, 0.8, 0.5);
            var color3 = new Color(1.0, 0.2, 0.7, 0.5);

            Assert.Equal(color1.GetHashCode(), color2.GetHashCode());
            Assert.NotEqual(color2.GetHashCode(), color3.GetHashCode());
        }
    }

    public class Stringize
    {
        [Theory]
        [InlineData("{0,0,0,0}", 0.0, 0.0, 0.0, 0.0)]
        [InlineData("{0.5,0.4,0.8,0.3}", 0.5, 0.4, 0.8, 0.3)]
        [InlineData("{1,1,1,1}", 1.0, 1.0, 1.0, 1.0)]
        public void GetString(string color, double red, double green, double blue, double alpha)
        {
            var c = new Color(red, green, blue, alpha).ToString();
            Assert.Equal(color, c);
        }
    }

    public class Serializable
    {
        [Theory]
        [InlineData(-0.2, 0.0, 0.0, 2.0)]
        [InlineData(0.0, 0.0, 0.0, 0.0)]
        [InlineData(0.4, 0.1, 0.5, -0.4)]
        [InlineData(0.8, 0.0, 0.5, 0.7)]
        [InlineData(1.0, 0.0, 0.0, 1.0)]
        [InlineData(1.5, 1.0, 1.0, 0.5)]
        public void SerializeDeserialize(double red, double green, double blue, double alpha)
        {
            var color1 = new Color(red, green, blue, alpha);
            var color2 = null as Color;

            using (var stream = new MemoryStream())
            {
                var formatter = new BinaryFormatter();
                formatter.Serialize(stream, color1);

                stream.Position = 0;
                color2 = (Color)formatter.Deserialize(stream);
            }

            Assert.True(color1.Equals(color2));
        }
    }
}
