# Figure.DrawCurvetoCubic Method 
Back to <a href="Home.md">Home page</a> 

Draw curve cubic

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public void DrawCurvetoCubic(
	Coordinate coordinate,
	Point point,
	Point point1,
	Point point2
)
```

**VB**<br />
``` VB
Public Sub DrawCurvetoCubic ( 
	coordinate As Coordinate,
	point As Point,
	point1 As Point,
	point2 As Point
)
```

**F#**<br />
``` F#
member DrawCurvetoCubic : 
        coordinate : Coordinate * 
        point : Point * 
        point1 : Point * 
        point2 : Point -> unit 

```


#### Parameters
&nbsp;<dl><dt>coordinate</dt><dd>Type: <a href="T_VGlyph_Coordinate.md">VGlyph.Coordinate</a><br />Specifies how to shift *point* from the previous point</dd><dt>point</dt><dd>Type: <a href="T_VGlyph_Point.md">VGlyph.Point</a><br />New current point</dd><dt>point1</dt><dd>Type: <a href="T_VGlyph_Point.md">VGlyph.Point</a><br />Control point at the beginning of the curve</dd><dt>point2</dt><dd>Type: <a href="T_VGlyph_Point.md">VGlyph.Point</a><br />Control point at the end of the curve.</dd></dl>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Figure.md">Figure Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />