# Figure.DrawCurvetoQuadraticSmooth Method 
Back to <a href="Home.md">Home page</a> 

Draw quadratic smooth

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public void DrawCurvetoQuadraticSmooth(
	Coordinate coordinate,
	Point point
)
```

**VB**<br />
``` VB
Public Sub DrawCurvetoQuadraticSmooth ( 
	coordinate As Coordinate,
	point As Point
)
```

**F#**<br />
``` F#
member DrawCurvetoQuadraticSmooth : 
        coordinate : Coordinate * 
        point : Point -> unit 

```


#### Parameters
&nbsp;<dl><dt>coordinate</dt><dd>Type: <a href="T_VGlyph_Coordinate.md">VGlyph.Coordinate</a><br />Specifies how to shift *point* from the previous point</dd><dt>point</dt><dd>Type: <a href="T_VGlyph_Point.md">VGlyph.Point</a><br />New current point</dd></dl>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Figure.md">Figure Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />