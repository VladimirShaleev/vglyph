# Transform.Multiply Operator (Transform, Point)
Back to <a href="Home.md">Home page</a> 

Transform point

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public static Point operator *(
	Transform transform,
	Point point
)
```

**VB**<br />
``` VB
Public Shared Operator * ( 
	transform As Transform,
	point As Point
) As Point
```

**F#**<br />
``` F#
static let inline (*)
        transform : Transform * 
        point : Point  : Point
```


#### Parameters
&nbsp;<dl><dt>transform</dt><dd>Type: <a href="T_VGlyph_Transform.md">VGlyph.Transform</a><br />Matrix</dd><dt>point</dt><dd>Type: <a href="T_VGlyph_Point.md">VGlyph.Point</a><br />transform <a href="T_VGlyph_Point.md">Point</a></dd></dl>

#### Return Value
Type: <a href="T_VGlyph_Point.md">Point</a><br />Result transform of *point*

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/27426hcy" target="_blank">ArgumentNullException</a></td><td>transform is null</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/3w1b3114" target="_blank">ArgumentException</a></td><td>transform is invalid</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Transform.md">Transform Class</a><br /><a href="Overload_VGlyph_Transform_op_Multiply.md">Multiply Overload</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />