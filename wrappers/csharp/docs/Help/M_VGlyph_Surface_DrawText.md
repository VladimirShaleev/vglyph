# Surface.DrawText Method 
Back to <a href="Home.md">Home page</a> 

Draw text on surface

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public void DrawText(
	Face face,
	float pt,
	string text,
	Color color,
	Point position,
	Point origin,
	Point scale,
	float angle,
	bool verticalLayout
)
```

**VB**<br />
``` VB
Public Sub DrawText ( 
	face As Face,
	pt As Single,
	text As String,
	color As Color,
	position As Point,
	origin As Point,
	scale As Point,
	angle As Single,
	verticalLayout As Boolean
)
```

**F#**<br />
``` F#
member DrawText : 
        face : Face * 
        pt : float32 * 
        text : string * 
        color : Color * 
        position : Point * 
        origin : Point * 
        scale : Point * 
        angle : float32 * 
        verticalLayout : bool -> unit 

```


#### Parameters
&nbsp;<dl><dt>face</dt><dd>Type: <a href="T_VGlyph_Face.md">VGlyph.Face</a><br />Draw glyphs in <a href="T_VGlyph_Face.md">Face</a></dd><dt>pt</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/3www918f" target="_blank">System.Single</a><br />Size glyph in punkt</dd><dt>text</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/s1wwdcbf" target="_blank">System.String</a><br />Text for drawing</dd><dt>color</dt><dd>Type: <a href="T_VGlyph_Color.md">VGlyph.Color</a><br /><a href="T_VGlyph_Color.md">Color</a> of <a href="T_VGlyph_Glyph.md">Glyph</a></dd><dt>position</dt><dd>Type: <a href="T_VGlyph_Point.md">VGlyph.Point</a><br />Position to draw on <a href="T_VGlyph_Surface.md">Surface</a></dd><dt>origin</dt><dd>Type: <a href="T_VGlyph_Point.md">VGlyph.Point</a><br />Origin of <a href="T_VGlyph_Glyph.md">Glyph</a></dd><dt>scale</dt><dd>Type: <a href="T_VGlyph_Point.md">VGlyph.Point</a><br />Scale of <a href="T_VGlyph_Glyph.md">Glyph</a></dd><dt>angle</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/3www918f" target="_blank">System.Single</a><br />Rotation of <a href="T_VGlyph_Glyph.md">Glyph</a></dd><dt>verticalLayout</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/a28wyd50" target="_blank">System.Boolean</a><br /><a href="T_VGlyph_Glyph.md">Glyph</a> orientation</dd></dl>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/27426hcy" target="_blank">ArgumentNullException</a></td><td>parameter is null</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/3w1b3114" target="_blank">ArgumentException</a></td><td><a href="T_VGlyph_Face.md">Face</a> handle is invalid</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Surface.md">Surface Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />