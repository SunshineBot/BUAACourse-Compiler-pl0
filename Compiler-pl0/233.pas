const   num = 10,
        did = -1,
        ch = 'a',
        ch1 = '1';
var     n : integer;
        chvar : char;
        a,b : array[5] of integer;
procedure  rank(k :integer);
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
                                rank(k+1);
                                b[i] := 0
                         end
        end; 

function add(x,y:integer):integer;
begin
        add := x+y
end;
begin
        for n := 0 to 4 by 1 do
        begin
                a[n] := 0;
                b[n] := 0
        end;
        read(n);
        rank(0);
        write("let calculate:1 minus 2 : ", add(1,-2));
        read(n)
end.