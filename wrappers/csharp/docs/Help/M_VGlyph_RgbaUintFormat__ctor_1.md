# RgbaUintFormat Constructor (PackagingBytes, RgbaComponents, RgbaUintBitCount)
Back to <a href="Home.md">Home page</a> 

Constructs new object <a href="T_VGlyph_RgbaUintFormat.md">RgbaUintFormat</a>

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public RgbaUintFormat(
	PackagingBytes packagingBytes,
	RgbaComponents components,
	RgbaUintBitCount bitCount
)
```

**VB**<br />
``` VB
Public Sub New ( 
	packagingBytes As PackagingBytes,
	components As RgbaComponents,
	bitCount As RgbaUintBitCount
)
```

**F#**<br />
``` F#
new : 
        packagingBytes : PackagingBytes * 
        components : RgbaComponents * 
        bitCount : RgbaUintBitCount -> RgbaUintFormat
```


#### Parameters
&nbsp;<dl><dt>packagingBytes</dt><dd>Type: <a href="T_VGlyph_PackagingBytes.md">VGlyph.PackagingBytes</a><br />Packaging bytes</dd><dt>components</dt><dd>Type: <a href="T_VGlyph_RgbaComponents.md">VGlyph.RgbaComponents</a><br />Map RGB channels</dd><dt>bitCount</dt><dd>Type: <a href="T_VGlyph_RgbaUintBitCount.md">VGlyph.RgbaUintBitCount</a><br />Bits per channel</dd></dl>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/27426hcy" target="_blank">ArgumentNullException</a></td><td>one or some arguments is null</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_RgbaUintFormat.md">RgbaUintFormat Class</a><br /><a href="Overload_VGlyph_RgbaUintFormat__ctor.md">RgbaUintFormat Overload</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />