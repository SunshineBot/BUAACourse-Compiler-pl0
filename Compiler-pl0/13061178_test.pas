const MAX=100;
var fu:array[3] of interger;
    x,y,z:interger;
    test1:char;

procedure rep(var op:interger);
begin
    if op>MAX then
        op:=op
    else
        while(op<=MAX)
        op:=op+1
end;

begin
    
test1:=50;
read(x,y,z);
write("math:",2*x+3*y+z+10.10); 
fu[0]:=x;
fu[1]:=y;
fu[2]:=z;
write(fu[0]);
write(fu[1]);
write(fu[2]);
    if x<y then        
        write("x<y");
    if x<=y then
        write("x<=y");
    if x>y then
        write("x>y");
    if x>=y then
        write("x>=y");
    if x=y then
        write("x=y");
    if x<>y then
        write( "x<>y");
    rep(x);            
    write("after rep x is ",x);
    rep(y);
    write("after rep y is ",y)
end.
