# Transform.Multiply Operator (Transform, Transform)
Back to <a href="Home.md">Home page</a> 

Multiply of two matrices

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public static Transform operator *(
	Transform value1,
	Transform value2
)
```

**VB**<br />
``` VB
Public Shared Operator * ( 
	value1 As Transform,
	value2 As Transform
) As Transform
```

**F#**<br />
``` F#
static let inline (*)
        value1 : Transform * 
        value2 : Transform  : Transform
```


#### Parameters
&nbsp;<dl><dt>value1</dt><dd>Type: <a href="T_VGlyph_Transform.md">VGlyph.Transform</a><br />Matrix 1</dd><dt>value2</dt><dd>Type: <a href="T_VGlyph_Transform.md">VGlyph.Transform</a><br />Matrix 2</dd></dl>

#### Return Value
Type: <a href="T_VGlyph_Transform.md">Transform</a><br />Result matrix

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/27426hcy" target="_blank">ArgumentNullException</a></td><td>value1 or value2 is null</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/3w1b3114" target="_blank">ArgumentException</a></td><td>value1 or value2 is invalid</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Transform.md">Transform Class</a><br /><a href="Overload_VGlyph_Transform_op_Multiply.md">Multiply Overload</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />