# Figure.DrawLinetoHorizontal Method 
Back to <a href="Home.md">Home page</a> 

Draw horizontal line from prev point

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public void DrawLinetoHorizontal(
	Coordinate coordinate,
	float x
)
```

**VB**<br />
``` VB
Public Sub DrawLinetoHorizontal ( 
	coordinate As Coordinate,
	x As Single
)
```

**F#**<br />
``` F#
member DrawLinetoHorizontal : 
        coordinate : Coordinate * 
        x : float32 -> unit 

```


#### Parameters
&nbsp;<dl><dt>coordinate</dt><dd>Type: <a href="T_VGlyph_Coordinate.md">VGlyph.Coordinate</a><br />Specifies how to shift *x* from the previous point</dd><dt>x</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/3www918f" target="_blank">System.Single</a><br />New position</dd></dl>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Figure.md">Figure Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />