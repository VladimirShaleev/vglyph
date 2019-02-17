# Figure.DrawArc Method 
Back to <a href="Home.md">Home page</a> 

Draw arc

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public void DrawArc(
	Coordinate coordinate,
	Point point,
	Point radius,
	float angle,
	bool largeArcFlag,
	bool sweepFlag
)
```

**VB**<br />
``` VB
Public Sub DrawArc ( 
	coordinate As Coordinate,
	point As Point,
	radius As Point,
	angle As Single,
	largeArcFlag As Boolean,
	sweepFlag As Boolean
)
```

**F#**<br />
``` F#
member DrawArc : 
        coordinate : Coordinate * 
        point : Point * 
        radius : Point * 
        angle : float32 * 
        largeArcFlag : bool * 
        sweepFlag : bool -> unit 

```


#### Parameters
&nbsp;<dl><dt>coordinate</dt><dd>Type: <a href="T_VGlyph_Coordinate.md">VGlyph.Coordinate</a><br />Specifies how to shift *point* from the previous point</dd><dt>point</dt><dd>Type: <a href="T_VGlyph_Point.md">VGlyph.Point</a><br />New current point</dd><dt>radius</dt><dd>Type: <a href="T_VGlyph_Point.md">VGlyph.Point</a><br />Define the size and orientation of the ellipse</dd><dt>angle</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/3www918f" target="_blank">System.Single</a><br />Rotated in degrees relative to the current coordinate system</dd><dt>largeArcFlag</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/a28wyd50" target="_blank">System.Boolean</a><br />Of the four candidate arc sweeps, two will represent an arc sweep of greater than or equal to 180 degrees (the "large-arc"), and two will represent an arc sweep of less than or equal to 180 degrees (the "small-arc"). If *largeArcFlag* is true, then one of the two larger arc sweeps will be chosen; otherwise, if *largeArcFlag* is false, one of the smaller arc sweeps will be chosen</dd><dt>sweepFlag</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/a28wyd50" target="_blank">System.Boolean</a><br />If *sweepFlag* is true, then the arc will be drawn in a "positive-angle" direction (i.e., the ellipse formula x=cx+rx*cos(theta) and y=cy+ry*sin(theta) is evaluated such that theta starts at an angle corresponding to the current point and increases positively until the arc reaches (x,y)). A value of 0 causes the arc to be drawn in a "negative-angle" direction (i.e., theta starts at an angle value corresponding to the current point and decreases until the arc reaches (x,y)).</dd></dl>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Figure.md">Figure Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />