# Surface.DrawGlyphTransform Method 
Back to <a href="Home.md">Home page</a> 

Draw glyph on surface

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public void DrawGlyphTransform(
	Glyph glyph,
	Color color,
	Transform transform
)
```

**VB**<br />
``` VB
Public Sub DrawGlyphTransform ( 
	glyph As Glyph,
	color As Color,
	transform As Transform
)
```

**F#**<br />
``` F#
member DrawGlyphTransform : 
        glyph : Glyph * 
        color : Color * 
        transform : Transform -> unit 

```


#### Parameters
&nbsp;<dl><dt>glyph</dt><dd>Type: <a href="T_VGlyph_Glyph.md">VGlyph.Glyph</a><br />Draw <a href="T_VGlyph_Glyph.md">Glyph</a></dd><dt>color</dt><dd>Type: <a href="T_VGlyph_Color.md">VGlyph.Color</a><br /><a href="T_VGlyph_Color.md">Color</a> of <a href="T_VGlyph_Glyph.md">Glyph</a></dd><dt>transform</dt><dd>Type: <a href="T_VGlyph_Transform.md">VGlyph.Transform</a><br /><a href="T_VGlyph_Transform.md">Transform</a> on <a href="T_VGlyph_Glyph.md">Glyph</a></dd></dl>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/27426hcy" target="_blank">ArgumentNullException</a></td><td>parameter is null</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/3w1b3114" target="_blank">ArgumentException</a></td><td>glyph and/or transform handle is invalid</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Surface.md">Surface Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />