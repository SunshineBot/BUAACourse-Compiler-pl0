const   num = 10,
    did = -1,
    ch = 'a',
    ch1 = '1';
var     n,m: integer;
    chvar : char;
    a,b : array[5] of integer;
procedure  rank(var k :integer);
    var i :integer;
    begin
        if k = n then
        begin
             i := 0;
             while i<n do
             begin
             write(a[i]);
             i := i+1
             end
        end
        else
             for i := 0 to n-1 by 1 do
             if b[i] = 0 then
             begin
                b[i] := 1;
                a[k] := i+1;
                k := k+1;
                rank(k);
                k := k-1;
                b[i] := 0
             end
    end; 

function add(x,y:integer):integer;
begin
    add := x+y
end;

begin
    m := 0;
    read(n);
    rank(m);
    read(n);
    write("let calculate:1.0 minus 2.0");
    write("answer:",add(48,-2));
    read(n);
    read(n)
end.
