# Surface.DrawGlyphViewport Method 
Back to <a href="Home.md">Home page</a> 

Draw glyph on surface to viewport

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public void DrawGlyphViewport(
	Glyph glyph,
	Color color,
	Point position,
	Point viewport,
	Point origin,
	float angle,
	bool fitToViewport
)
```

**VB**<br />
``` VB
Public Sub DrawGlyphViewport ( 
	glyph As Glyph,
	color As Color,
	position As Point,
	viewport As Point,
	origin As Point,
	angle As Single,
	fitToViewport As Boolean
)
```

**F#**<br />
``` F#
member DrawGlyphViewport : 
        glyph : Glyph * 
        color : Color * 
        position : Point * 
        viewport : Point * 
        origin : Point * 
        angle : float32 * 
        fitToViewport : bool -> unit 

```


#### Parameters
&nbsp;<dl><dt>glyph</dt><dd>Type: <a href="T_VGlyph_Glyph.md">VGlyph.Glyph</a><br />Draw <a href="T_VGlyph_Glyph.md">Glyph</a></dd><dt>color</dt><dd>Type: <a href="T_VGlyph_Color.md">VGlyph.Color</a><br /><a href="T_VGlyph_Color.md">Color</a> of <a href="T_VGlyph_Glyph.md">Glyph</a></dd><dt>position</dt><dd>Type: <a href="T_VGlyph_Point.md">VGlyph.Point</a><br />Position to draw on <a href="T_VGlyph_Surface.md">Surface</a></dd><dt>viewport</dt><dd>Type: <a href="T_VGlyph_Point.md">VGlyph.Point</a><br />Viewport for glyph</dd><dt>origin</dt><dd>Type: <a href="T_VGlyph_Point.md">VGlyph.Point</a><br />Origin of <a href="T_VGlyph_Glyph.md">Glyph</a></dd><dt>angle</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/3www918f" target="_blank">System.Single</a><br />Rotation of <a href="T_VGlyph_Glyph.md">Glyph</a></dd><dt>fitToViewport</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/a28wyd50" target="_blank">System.Boolean</a><br />Fit glyph to viewport without bearing</dd></dl>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/27426hcy" target="_blank">ArgumentNullException</a></td><td>parameter is null</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/3w1b3114" target="_blank">ArgumentException</a></td><td>glyph handle is invalid</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Surface.md">Surface Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />